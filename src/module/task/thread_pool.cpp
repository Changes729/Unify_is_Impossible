/** See a brief introduction (right-hand button) */
#include "thread_pool.h"
/* Private include -----------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define THREAD_NUMS 2

/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const int   NUMBER    = 2;
static ThreadPool* _instance = nullptr;
/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
ThreadPool& ThreadPool::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

ThreadPool* ThreadPool::create()
{
  assert(_instance == nullptr);
  _instance = new ThreadPool();
  assert(_instance != nullptr);
  return _instance;
}

void ThreadPool::destroy()
{
  delete _instance;
  _instance = nullptr;
}

ThreadPool::ThreadPool()
    : _shutdown{false}
{
  _threads.resize(THREAD_NUMS);
  for(int i = 0; i < THREAD_NUMS; ++i) {
    _threads[i] = std::thread(&ThreadPool::_worker, this);
  }
}

ThreadPool::~ThreadPool()
{
  std::unique_lock<std::mutex> lock(_pool_mutex);
  _shutdown = true;
  lock.unlock();

  _pool_cond.notify_all();
  for(int i = 0; i < THREAD_NUMS; ++i) {
    if(_threads[i].joinable()) _threads[i].join();
  }
}

void ThreadPool::add(IThread* task)
{
  assert(task != nullptr);

  std::unique_lock<std::mutex> lock(_pool_mutex);
  _tasks.push(task);
  lock.unlock();

  _pool_cond.notify_all();
}

void ThreadPool::_worker()
{
  std::unique_lock<std::mutex> lock(_pool_mutex);

  do {
    if(!_tasks.empty()) {
      /** lock.lock(); */
      auto task = _tasks.front();
      _tasks.pop();
      lock.unlock();

      task->_run();

      lock.lock();
      _tasks_complete.push(task);
      /** lock.unlock(); */
    } else {
      /** lock.lock(); */
      _pool_cond.wait(lock);
    }
  } while(!_shutdown);

  lock.unlock();
}

void ThreadPool::async()
{
  std::queue<IThread*>         queue;
  std::unique_lock<std::mutex> lock{_pool_mutex};

  while(!_tasks_complete.empty()) {
    auto task = _tasks_complete.front();
    queue.push(task);
    _tasks_complete.pop();
  }

  lock.unlock();

  while(!queue.empty()) {
    auto task = queue.front();
    task->_end();
    queue.pop();
  }
}
