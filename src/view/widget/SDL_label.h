/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_TEXTVIEW_H
#define SDL_TEXTVIEW_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <string>

#include "SDL_View.h"
#include "SDL_Widget.h"
#include "point_helper.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
class SDLFont;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLLabel: public SDLWidget
{
public:
  static void init();

public:
  SDLLabel(SDLWidget& view);
  virtual ~SDLLabel();

  inline void            set_font(const SDLFont* font) { _sdl_font = font; }
  virtual const SDLFont* font();
  virtual const char*    label();
  virtual void           render(point_t pos_start, point_t size) override;

  inline void set_bg_color(color_t color) { _bg_color = color; }
  inline void set_label_color(color_t color) { _label_color = color; }
  void        update_text(const std::string& str);

  point_t size() override final;

protected:
  void resize(const point_t& size) override final {}

private:
  SDL_Texture* _sdl_texture;

  const SDLFont* _sdl_font;
  color_t        _bg_color;
  color_t        _label_color;

  point_t     _size;
  std::string _string;
};

#endif /* SDL_TEXTVIEW_H */
