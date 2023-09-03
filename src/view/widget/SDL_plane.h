/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_PLANE_H
#define SDL_PLANE_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "SDL_View.h"
#include "SDL_Widget.h"
#include "color_helper.h"
#include "point_helper.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLPlane: public SDLWidget
{
public:
  SDLPlane(SDLWidget& view);
  virtual ~SDLPlane();

  inline void set_bg_color(color_t color) { _bg_color = color; }
  inline void set_bg_alpha(uint8_t alpha) { _bg_color.arg.a = alpha; }

  point_t size() override final;
  void    resize(const point_t& size) override final;

private:
  void render(point_t pos_start, point_t size) override final;

private:
  SDL_Texture* _sdl_texture;

  color_t _bg_color;
  point_t _size;
};

#endif /* SDL_PLANE_H */
