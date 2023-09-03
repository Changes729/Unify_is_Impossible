/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TEMP_CSTR_H
#define TEMP_CSTR_H
#pragma once
/* Public include ------------------------------------------------------------*/
/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
template<typename... __arg_pkg>
struct temp_cstr
{
  temp_cstr(const char* format, __arg_pkg... args)
      : _buffer{nullptr}
  {
    size_t size = snprintf(nullptr, 0, format, args...);
    _buffer     = new char[size + 1];

    assert(_buffer != nullptr);
    snprintf(_buffer, size + 1, format, args...);

    _buffer[size] = 0;
  }

  ~temp_cstr()
  {
    delete _buffer;
    _buffer = nullptr;
  }

  inline operator char*() const { return _buffer; }

private:
  char* _buffer;
};

#endif /* TEMP_CSTR_H */
