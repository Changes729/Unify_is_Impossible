#include <curl/curl.h>
#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <tuple>

#include "SDL_Event.h"
#include "SDL_Font.h"
#include "SDL_View.h"
#include "SDL_Windows.h"
#include "audio_manager.h"
#include "event_manager.h"
#include "event_timer.h"
#include "log.h"
#include "signal_system.h"
#include "system_manager.h"
#include "thread_pool.h"
#include "unistd.h"
#include "video_player.h"
#include "wav_player.h"
#include "widget/SDL_label.h"
#include "windows_manager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

static bool is_running = true;

bool on_sys_event(EventID_t id, const void *e_data, void *user_data)
{
  assert(id == SDLEvent::id());
  assert(e_data == &SDLEvent::instance());
  SDL_Event *event = SDLEvent::instance().data();

  is_running = !(event->type == SDL_QUIT);
  if(event->type == SDL_KEYUP) {
    switch(event->key.keysym.scancode) {
      case SDL_SCANCODE_Q:
        is_running = false;
        break;
      case SDL_SCANCODE_0:
      {
        const char *id = "12345678";
      } break;
      case SDL_SCANCODE_1:
      {
        SystemManager::instance().resource_path() = "./resource";
        SystemManager::instance().url_host()      = "http://localhost";
        SystemManager::instance().device_id()     = "1234";
      } break;
      case SDL_SCANCODE_MINUS:
      {
        auto &audio_manager = AudioManager::instance();
        audio_manager.set_sys_volume(audio_manager.get_sys_volume() - 1);
      } break;
      case SDL_SCANCODE_EQUALS:
      {
        auto &audio_manager = AudioManager::instance();
        audio_manager.set_sys_volume(audio_manager.get_sys_volume() + 1);
      } break;
      default:
        LOG_DEBUG("press key %d", event->key.keysym.scancode);
        break;
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  SystemManager::create();
  WindowsManager::create();
  EventManager::create();
  AudioManager::create();
  TimerEventManager::create();
  SDLEvent::create();
  ThreadPool::create();

  SDLFont::init();


#if 0 //FIXME:
  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    LOG_ERROR("SDL_image could not initialize! SDL_image Error: %s\n",
              IMG_GetError());
  }
#endif

  auto &timer_event  = TimerEventManager::instance();
  void *thread_async = nullptr;
  void *sdl_render   = nullptr;

  thread_async = timer_event.every(50,
                                   TIMER_CALLBACK(&ThreadPool::async),
                                   &ThreadPool::instance());

  LOG_DEBUG("timer %s register in id 0x%X",
            TO_STR(ThreadPool::async),
            thread_async);

  SDLEvent::instance().register_event(on_sys_event, NULL);
  {
    SDLWindow window{};

    sdl_render = timer_event.every(1000 / 60, /** 60Hz */
                                   TIMER_CALLBACK(&WindowsManager::render),
                                   &WindowsManager::instance());
    LOG_DEBUG("timer %s register in id 0x%X",
              TO_STR(WindowsManager::render),
              sdl_render);

    while(is_running) {
      EventManager::instance().notify_all();
    }
  }
  SDLEvent::instance().unregister_event(on_sys_event, NULL);

  timer_event.cancel(sdl_render);
  timer_event.cancel(thread_async);

  SDLEvent::destroy();
  TimerEventManager::destroy();
  AudioManager::destroy();
  EventManager::destroy();
  WindowsManager::destroy();

  return 0;
}