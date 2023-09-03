/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef NORMAL_FLOW_H
#define NORMAL_FLOW_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <assert.h>

#include "SDL_Widget.h"
#include "windows_manager.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class NormalLayout: public SDLWidget
{
public:
  NormalLayout(SDLWidget& parent)
      : SDLWidget{parent}
  {
    set_style(&_style);
    _style.layout = Style::LAYOUT::NORMAL_FLOW;
  }

  void render(point_t pos_start, point_t size_) override final
  {
    for(auto& widget: *this) {
      widget->render(pos_start, size_);
      if(style() && style()->layout == Style::LAYOUT::NORMAL_FLOW) {
        pos_start.y += widget->size().y;
        size_.y -= widget->size().y;
      }
    }
  }

  point_t size() override final
  {
    point_t size;
    for(auto& widget: *this) {
      size.y += widget->size().y;
      size.x = std::max(size.x, widget->size().x);
    }

    return size;
  }

private:
  void resize(const point_t& size) override final {}

private:
  Style _style;
};

#endif /* NORMAL_FLOW_H */
