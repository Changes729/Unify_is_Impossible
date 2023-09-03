/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "event_manager.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
class IThread
{
public:
  virtual void _run() = 0;
  virtual void _end() = 0;
};

/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class ThreadPool
{
public:
  static ThreadPool& instance();
  static ThreadPool* create();
  static void        destroy();

public:
  void async();
  void add(IThread* task);

private:
  ThreadPool();
  ~ThreadPool();

  void _worker();

private:
  bool     _shutdown;
  IThread* _thread;

  std::queue<IThread*>     _tasks;
  std::queue<IThread*>     _tasks_complete;
  std::vector<std::thread> _threads;

  std::mutex              _pool_mutex;
  std::condition_variable _pool_cond;
};

#endif /* THREAD_POOL_H */
