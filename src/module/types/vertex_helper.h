/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VERTEX_HELPER_H
#define VERTEX_HELPER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "point_helper.h"
#include "color_helper.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
typedef struct
{
  point<float> pos;
  color_t color;
} vertex_t;

#endif /* VERTEX_HELPER_H */
