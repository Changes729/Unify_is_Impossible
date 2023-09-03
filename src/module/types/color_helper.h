/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COLOR_HELPER_H
#define _COLOR_HELPER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stdint.h>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
union color_t {
  uint32_t rgba;
  struct /** !!! little end */
  {
    uint8_t a;
    uint8_t b;
    uint8_t g;
    uint8_t r;
  } arg;

  color_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
      : arg{a, b, g, r}
  {}
  color_t(uint32_t c)
      : rgba{c}
  {}
};

#endif /* _COLOR_HELPER_H */
