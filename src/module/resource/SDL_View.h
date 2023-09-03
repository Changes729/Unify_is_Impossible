/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VIEW_CORE_H
#define VIEW_CORE_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "SDL_Widget.h"
#include "SDL_Windows.h"
#include "view_draw.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLView
    : public SDLWidget
    , public IView
    , public IViewDraw
{
public:
  SDLView(SDLWindow&);
  virtual ~SDLView();

public:
  virtual void render() override
  {
    if(visible()) {
      this->render({0, 0}, size());
    }
  }
  virtual void render(point_t pos_start, point_t size) override;
  SDLWindow&   window() override final { return _sdl_window; };

public:
  void clear(const color_t color) final;
  void draw_geometry(const std::vector<vertex_t>& vertex_array) final;

private:
  SDLWindow& _sdl_window;
};

#endif /* VIEW_CORE_H */
