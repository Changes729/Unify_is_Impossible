/** See a brief introduction (right-hand button) */
#include "SDL_Event.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <assert.h>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static SDLEvent* _instance = nullptr;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
SDLEvent& SDLEvent::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

SDLEvent* SDLEvent::create()
{
  assert(_instance == nullptr);
  _instance = new SDLEvent();
  return _instance;
}

void SDLEvent::destroy()
{
  delete _instance;
  _instance = nullptr;
}

EventID_t SDLEvent::id() { return _instance->EventSender::id(); }

void SDLEvent::notify()
{
  SDL_Event sdl_event;
  SDL_WaitEventTimeout(&sdl_event, 0);

  /** let user use this value. */
  _sdl_event = &sdl_event;

  EventSender::notify();
}

void SDLEvent::notify_event(EventFlag_t mask, void* __UNUSED__)
{
  IEventSender::set_flag(mask);

  SDL_Event event;
  event.type = SDL_USEREVENT + mask - EVENT_SDL_USER_DEF;
  SDL_PushEvent(&event);
}
