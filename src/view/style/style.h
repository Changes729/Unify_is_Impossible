/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STYLE_H
#define STYLE_H
#pragma once
/* Public include ------------------------------------------------------------*/
/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
struct Style
{
public:
  Style()
      : layout{LAYOUT::NONE}
      , align{ALIGN::LEFT}
  {}

  enum LAYOUT { NONE, NORMAL_FLOW } layout;
  enum ALIGN { TOP, BOTTOM, LEFT, RIGHT } align;
};

#endif /* STYLE_H */
