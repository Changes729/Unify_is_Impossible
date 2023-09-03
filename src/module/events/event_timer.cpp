/** See a brief introduction (right-hand button) */
#include "event_timer.h"
/* Private include -----------------------------------------------------------*/
#include <assert.h>

#include "timer_utils.h"
#include "log.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct _timer_record_t
{
  const timer_id_t    id;
  const unsigned long interval;
  timer_cb_t          cb;
  void*               user_data;

  unsigned long _trigger_interval;
  bool          _need_remove;

  _timer_record_t(unsigned long i, timer_cb_t c, void* u);
  inline bool operator==(const _timer_record_t& b) { return id == b.id; }

} _timer_record_t;

/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static TimerEventManager* _instance = nullptr;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static bool _timer_callback_helper(EventID_t, const void* data, void* user_data);
static bool _timer_once_callback_helper(EventID_t,
                                        const void* data,
                                        void*       user_data);

/* Private function ----------------------------------------------------------*/
_timer_record_t::_timer_record_t(unsigned long i, timer_cb_t c, void* u)
    : id{this}
    , interval{i}
    , cb{c}
    , user_data{u}
    , _trigger_interval{get_time() + i}
    , _need_remove{false} {};

static bool _timer_callback_helper(EventID_t   __NOTUSED__,
                                   const void* data,
                                   void*       user_data)
{
  assert(data == &TimerEventManager::instance());
  auto  curr_timestamp = get_time();
  auto& timer_record   = *static_cast<_timer_record_t*>(user_data);
  if(curr_timestamp >= timer_record._trigger_interval &&
     !timer_record._need_remove)
  {
    timer_record.cb(timer_record.user_data);
    timer_record._trigger_interval += timer_record.interval;
    if(curr_timestamp > timer_record._trigger_interval) {
      LOG_DEBUG("timer %p run overtime %u ms.",
               &timer_record,
               curr_timestamp - timer_record._trigger_interval);

      timer_record._trigger_interval = curr_timestamp + timer_record.interval;
    }
  }

  return false;
}

static bool _timer_once_callback_helper(EventID_t   __NOTUSED__,
                                        const void* data,
                                        void*       user_data)
{
  assert(data == &TimerEventManager::instance());
  auto  curr_timestamp = get_time();
  auto& timer_record   = *static_cast<_timer_record_t*>(user_data);
  if(curr_timestamp >= timer_record._trigger_interval &&
     !timer_record._need_remove)
  {
    timer_record.cb(timer_record.user_data);
    timer_record._trigger_interval += timer_record.interval;
    timer_record._need_remove = true;
    if(curr_timestamp > timer_record._trigger_interval) {
      LOG_DEBUG("timer %p run overtime %u ms.",
               &timer_record,
               curr_timestamp - timer_record._trigger_interval);
    }
  }

  return false;
}
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */

TimerEventManager& TimerEventManager::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

TimerEventManager* TimerEventManager::create()
{
  assert(_instance == nullptr);
  _instance = new TimerEventManager();
  return _instance;
}

void TimerEventManager::destroy()
{
  delete _instance;
  _instance = nullptr;
}

TimerEventManager::TimerEventManager() {}

TimerEventManager::~TimerEventManager()
{
  for(auto record: *this) {
    delete static_cast<_timer_record_t*>(record.user_data);
  }
}

timer_id_t TimerEventManager::once(unsigned long interval,
                                   timer_cb_t    cb,
                                   void*         user_data)
{
  auto new_record = new _timer_record_t{interval, cb, user_data};
  register_event(_timer_once_callback_helper, new_record);
  return new_record->id;
}

timer_id_t TimerEventManager::every(unsigned long interval,
                                    timer_cb_t    cb,
                                    void*         user_data)
{
  auto new_record = new _timer_record_t{interval, cb, user_data};
  register_event(_timer_callback_helper, new_record);
  return new_record->id;
}

void TimerEventManager::reset(timer_id_t id)
{
  for(auto record: *this) {
    auto timer_record = static_cast<_timer_record_t*>(record.user_data);
    if(timer_record->id == id) {
      timer_record->_trigger_interval = get_time() + timer_record->interval;
    }
  }
}

void TimerEventManager::cancel(timer_id_t id)
{
  for(auto record: *this) {
    auto timer_record = static_cast<_timer_record_t*>(record.user_data);
    if(timer_record->id == id) {
      timer_record->_need_remove = true;
    }
  }
}

void TimerEventManager::notify()
{
  EventSender::notify();

  erase(std::remove_if(this->begin(),
                       this->end(),
                       [](EventRecord_t record) {
                         auto timer_record =
                             static_cast<_timer_record_t*>(record.user_data);
                         bool need_remove = timer_record->_need_remove;

                         if(need_remove) {
                           delete timer_record;
                         }

                         return need_remove;
                       }),
        this->end());
}
