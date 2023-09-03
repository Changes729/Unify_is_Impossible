/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FONT_H
#define _FONT_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <string>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IFont
{
public:
  IFont(const std::string path, const std::string family, size_t);

protected:
  const std::string _font_family;
  const std::string _font_path;

  size_t _font_size;
};

#endif /* _FONT_H */
