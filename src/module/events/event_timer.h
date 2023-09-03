/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EVENT_TIMER_H
#define EVENT_TIMER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "callback_helper.h"
#include "event_manager.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define TIMER_CALLBACK(func) CALLBACK_REVERSE_MAKE(timer_cb_t, func)

/* Public typedef ------------------------------------------------------------*/
using timer_id_t = void*;
using timer_cb_t = void (*)(void* user_data);

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class TimerEventManager final: protected EventSender
{
public:
  static TimerEventManager& instance();
  static TimerEventManager* create();
  static void               destroy();

public:
  timer_id_t once(unsigned long interval, timer_cb_t cb, void* user_data);
  timer_id_t every(unsigned long interval, timer_cb_t cb, void* user_data);

  void reset(timer_id_t id);
  void cancel(timer_id_t id);

  void notify() override final;

private:
  TimerEventManager();
  ~TimerEventManager();
  void notify_event(EventFlag_t, void* data = nullptr) override final {}
};

#endif /* EVENT_TIMER_H */
