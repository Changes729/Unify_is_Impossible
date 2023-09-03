/** See a brief introduction (right-hand button) */
#include "SDL_Windows.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
SDLWindow::SDLWindow(std::string name)
    : _window_name{name}
    , _sdl_window{SDL_CreateWindow(_window_name.c_str(),
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   1280,
                                   800,
                                   SDL_WINDOW_RESIZABLE |
                                       SDL_WINDOW_FULLSCREEN_DESKTOP)}
    , _sdl_renderer{SDL_CreateRenderer(_sdl_window,
                                       -1,
                                       SDL_WINDOW_OPENGL |
                                           SDL_RENDERER_ACCELERATED |
                                           SDL_RENDERER_PRESENTVSYNC)}
{
  /** Blender mode could use alpha mix. */
  SDL_SetRenderDrawBlendMode(_sdl_renderer.renderer(), SDL_BLENDMODE_BLEND);
  /** speed up on render. */
  SDL_RenderSetVSync(_sdl_renderer.renderer(), 0);
}

SDLWindow::~SDLWindow()
{
  SDL_DestroyRenderer(_sdl_renderer.renderer());
  SDL_DestroyWindow(_sdl_window);
}

point_t SDLWindow::get_active_window_size()
{
  SDL_DisplayMode sdl_display_mode;
  SDL_GetCurrentDisplayMode(0, &sdl_display_mode);

  return {sdl_display_mode.w, sdl_display_mode.h};
}

void SDLWindow::render()
{
  SDL_SetRenderDrawColor(_sdl_renderer.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(_sdl_renderer.renderer());
  for(auto render: *this) {
    render->render();
  }
}

void SDLWindow::present() { SDL_RenderPresent(_sdl_renderer.renderer()); }

point_t SDLWindow::size()
{
  int x, y;
  SDL_GetWindowSize(_sdl_window, &x, &y);

  assert(x >= 0 && y >= 0);

  return point_t{x, y};
}