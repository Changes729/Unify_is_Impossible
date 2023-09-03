/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "SDL_Widget.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLImage: public SDLWidget
{
public:
  SDLImage(SDLWidget &parent, const std::string &image);
  virtual ~SDLImage();

  point_t      size() override final;
  virtual void render(point_t pos_start, point_t size) override;

  void load_img(const std::string &img);

  void zoom(float percent);
  void zoom(float w_percent, float h_percent);
  void zoom_to(point_t size);


protected:
  point_t _raw_size();
  void    resize(const point_t &size) override final{};

private:
  SDL_Surface *_sdl_surface;
  SDL_Texture *_sdl_texture;

  point_t     *_zoom_size;
  point_t      _cut_pixel;
  point<float> _zoom_percent;
};

#endif /* SDL_IMAGE_H */
