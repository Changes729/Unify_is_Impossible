/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_WINDOWS_H
#define SDL_WINDOWS_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <string>

#include "SDL_events.h"
#include "render/SDL_renderer.h"
#include "windows_manager.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
struct SDL_Window;
struct SDL_Texture;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLWindow final: public IWindow
{
public:
  SDLWindow(std::string name = "");
  ~SDLWindow();

  point_t      get_active_window_size();
  SDLRenderer& get_renderer() { return _sdl_renderer; }

  void render() override final;
  void present() override final;

  point_t size() override final;

private:
  std::string _window_name;
  SDL_Window* _sdl_window;
  SDLRenderer _sdl_renderer;
};

#endif /* SDL_WINDOWS_H */
