/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include <queue>

#include "callback_helper.h"
#include "manager_interface.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define EVENT_CALLBACK(func) CALLBACK_REVERSE_MAKE(Event_Callback_t, func)

/* Public typedef ------------------------------------------------------------*/
using EventID_t        = uint32_t;
using EventFlag_t      = uint32_t;
using Event_Callback_t = bool (*)(EventID_t, const void* data, void* user_data);
using EventRecord_t    = struct
{
  Event_Callback_t cb;
  void*            user_data;
};

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
inline bool operator==(const EventRecord_t& a, const EventRecord_t& b)
{
  return a.cb == b.cb && a.user_data == b.user_data;
}

/* Public class --------------------------------------------------------------*/
class IEventSender: protected IManager<EventRecord_t>
{
public:
  IEventSender();

  virtual void register_event(Event_Callback_t cb, void* user_data);
  virtual void unregister_event(Event_Callback_t cb, void* user_data);

  inline void              set_flag(EventFlag_t flag) { _event_flag |= flag; }
  inline void              clear_flag() { _event_flag = 0; }
  inline const EventFlag_t flag() { return _event_flag; }

  inline const EventID_t id() { return _event_id; }

  virtual void notify();
  virtual void notify_event(EventFlag_t, void* data = nullptr) = 0;

private:
  static EventID_t _event_ids;
  const EventID_t  _event_id;
  EventFlag_t      _event_flag;

  /** [BUG] events in traversal couldn't add new event. */
  bool                      _in_notify;
  std::queue<EventRecord_t> _register_queue;
};

#endif /* EVENT_SYSTEM_H */
