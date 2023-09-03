/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef POINT_HELPER_H
#define POINT_HELPER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
template<typename BitSize>
struct point
{
  BitSize x;
  BitSize y;
  BitSize z;

  point()
      : point{0, 0} {};

  point(BitSize __x, BitSize __y, BitSize __z = 0)
      : x{__x}
      , y{__y}
      , z{__z} {};

  friend point& operator+=(point& self, const point& b)
  {
    self.x += b.x;
    self.y += b.y;
    self.z += b.z;

    return self;
  }

  friend point operator-(const point& a, const point& b)
  {
    return point{a.x - b.x, a.y - b.y, a.z - b.z};
  }

  friend point operator+(const point& a, const point& b)
  {
    return point{a.x + b.x, a.y + b.y, a.z + b.z};
  }

  friend bool operator==(const point& a, const point& b)
  {
    return memcmp(&a, &b, sizeof(point)) == 0;
  }

  template<typename T>
  friend point operator/(const point& a, T div)
  {
    return point{a.x / div, a.y / div, a.z / div};
  }

  template<typename T>
  friend point operator*(const point& a, T div)
  {
    return point{static_cast<BitSize>(div * a.x),
                 static_cast<BitSize>(div * a.y),
                 static_cast<BitSize>(div * a.z)};
  }

  template<typename T>
  friend point operator/(const point& a, const point<T>& b)
  {
    return point{a.x / b.x, a.y / b.y, a.z / b.z};
  }

  template<typename T>
  friend point operator*(const point& a, const point<T>& b)
  {
    return point{static_cast<BitSize>(a.x * b.x),
                 static_cast<BitSize>(a.y * b.y),
                 static_cast<BitSize>(a.z * b.z)};
  }
};

using point_t = point<int32_t>;

#endif /* POINT_HELPER_H */
