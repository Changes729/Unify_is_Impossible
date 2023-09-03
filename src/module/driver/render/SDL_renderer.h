/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <assert.h>

#include "render/renderer.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
struct SDL_Renderer;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLRenderer: public IRenderer
{
public:
  SDLRenderer(SDL_Renderer* renderer)
      : _sdl_renderer{renderer}
  {
    assert(_sdl_renderer != nullptr);
  };

  inline SDL_Renderer* renderer() { return _sdl_renderer; }

private:
  SDL_Renderer* _sdl_renderer;
};

#endif /* SDL_RENDERER_H */
