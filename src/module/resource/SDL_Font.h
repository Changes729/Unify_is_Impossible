/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDL_FONT_H
#define SDL_FONT_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <string>

#include "font.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
typedef struct _TTF_Font TTF_Font;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SDLFont: public IFont
{
public:
  static void init();

public:
  SDLFont(const std::string path, const std::string family, size_t size);
  virtual ~SDLFont();

  TTF_Font *get_font() const { return _font; }

private:
  TTF_Font *_font;
};

#endif /* SDL_FONT_H */
