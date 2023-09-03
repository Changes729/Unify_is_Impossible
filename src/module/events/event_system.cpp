/** See a brief introduction (right-hand button) */
#include "event_system.h"
/* Private include -----------------------------------------------------------*/
#include "event_manager.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EventID_t IEventSender::_event_ids = 0;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
IEventSender::IEventSender()
    : _event_id{_event_ids++}
    , _event_flag{0}
    , _in_notify{false}
    , _register_queue{}
{}

void IEventSender::register_event(Event_Callback_t cb, void* user_data)
{
  _in_notify ? _register_queue.push({cb, user_data})
             : register_child({cb, user_data});
}

void IEventSender::unregister_event(Event_Callback_t cb, void* user_data)
{
  assert(!_in_notify);
  unregister_child({cb, user_data});
}

void IEventSender::notify()
{
  const auto HANDLED = true;

  _in_notify         = true;
  for(auto receiver: *this) {
    if(HANDLED == receiver.cb(id(), this, receiver.user_data)) {
      break;
    }
  }
  _in_notify = false;

  while(!_register_queue.empty()) {
    auto& new_reg = _register_queue.front();
    register_event(new_reg.cb, new_reg.user_data);
    _register_queue.pop();
  }
  clear_flag();
}
