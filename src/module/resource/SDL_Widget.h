/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_WIDGET_H
#define SDL_WIDGET_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "SDL_Windows.h"
#include "render/SDL_renderer.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLWidget: public IWidget
{
public:
  SDLWidget(SDLRenderer& renderer, SDLWidget* parent = nullptr)
      : IWidget{renderer, parent}
      , _renderer{renderer}
      , _parent{nullptr}
  {}
  SDLWidget(SDLWidget& parent)
      : SDLWidget{parent.renderer(), &parent}
  {}

  SDLWidget*   parent() override final { return _parent; }
  SDLRenderer& renderer() override final { return _renderer; }

private:
  SDLRenderer& _renderer;
  SDLWidget*   _parent;
};

#endif /* SDL_WIDGET_H */
