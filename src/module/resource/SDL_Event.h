/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_EVENT_H
#define SDL_EVENT_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "event_manager.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
union SDL_Event;
typedef enum {
  EVENT_SDL_NONE,
  EVENT_SDL_SYSTEM,
  EVENT_SDL_INPUT,

  EVENT_SDL_USER_DEF,
} EVENT_SDL_MASK;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLEvent: public EventSender
{
public:
  static SDLEvent& instance();
  static SDLEvent* create();
  static void      destroy();
  static EventID_t id();

public:
  void notify() override final;
  void notify_event(EventFlag_t mask, void* data = nullptr) override final;

  inline SDL_Event* data() { return _sdl_event; }

private:
  SDL_Event* _sdl_event;
};

#endif /* SDL_EVENT_H */
