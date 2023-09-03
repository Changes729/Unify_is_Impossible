/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LABEL_H
#define _LABEL_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <string>

#include "color_helper.h"
#include "font.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
template<typename Font = IFont>
class ILabel: public std::string
{
public:
  virtual void render(const Font& font, color_t _color = color_t{0xFFFFFFFF}) = 0;
};

#endif /* _LABEL_H */
