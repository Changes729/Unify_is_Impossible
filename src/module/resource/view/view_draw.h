/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VIEW_DRAW_H
#define VIEW_DRAW_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <vector>

#include "color_helper.h"
#include "vertex_helper.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IViewDraw
{
public:
  virtual void clear(const color_t color)                               = 0;
  virtual void draw_geometry(const std::vector<vertex_t>& vertex_array) = 0;
};

#endif /* VIEW_DRAW_H */
