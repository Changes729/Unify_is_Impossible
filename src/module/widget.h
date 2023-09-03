/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WIDGET_H
#define WIDGET_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "manager_interface.h"
#include "render/renderer.h"
#include "style/style.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IWidget: public IManager<IWidget*>
{
public:
  IWidget(IRenderer& renderer, IWidget* parent = nullptr);
  IWidget(IWidget& parent);
  virtual ~IWidget();

  virtual IWidget* parent() { return _parent; }

  /* PART Render ---------------------------------------------------*/
  inline void        set_visible(bool visible) { _visible = visible; }
  inline bool        is_visible() { return _visible; }
  virtual void       render(point_t pos_start, point_t size) = 0;
  virtual IRenderer& renderer() { return _renderer; }

  /* PART Physics --------------------------------------------------*/
  inline point_t start_at() { return _place; }
  virtual void   move(const point_t& offset) { _place += offset; }
  virtual void   move_to(const point_t& place) { _place = place; }

  virtual point_t size()                      = 0;
  virtual void    resize(const point_t& size) = 0;

  /* PART Style ----------------------------------------------------*/
  void           set_style(Style* style) { _style = style; }
  virtual Style* style()
  {
    return _style ? _style : (parent() ? parent()->style() : nullptr);
  }

private:
  IWidget*   _parent;
  IRenderer& _renderer;
  point_t    _place;
  Style*     _style;

  bool _visible;
};

#endif /* WIDGET_H */
