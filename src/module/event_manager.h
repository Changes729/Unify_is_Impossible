/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stdint.h>

#include <list>
#include <map>

#include "event_system.h"
#include "manager_interface.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class EventManager: public IManager<IEventSender*>
{
public:
  static EventManager& instance();
  static EventManager* create();
  static void          destroy();

public:
  void notify_all();
};

class EventSender: public IEventSender
{
public:
  EventSender();
  virtual ~EventSender();
};

#endif /* EVENT_MANAGER_H */
