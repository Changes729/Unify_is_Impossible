/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SIGNAL_SYSTEM_H
#define SIGNAL_SYSTEM_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stdint.h>

#include <utility>

#include "manager_interface.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define SIGNAL_CALLBACK(func) CALLBACK_MAKE(signal_cb_t, func)

/* Public typedef ------------------------------------------------------------*/
typedef uint32_t signal_t;
typedef void (*signal_cb_t)(void *user_data, signal_t, void *data);
typedef struct
{
  signal_cb_t callback;
  void       *user_data;
} signal_record_t;

inline bool operator==(const signal_record_t &a, const signal_record_t &b)
{
  return a.callback == b.callback && a.user_data == b.user_data;
}

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class ISignal: protected IManager<signal_record_t>
{
public:
  ISignal();

  inline signal_t id() { return _id; }

  virtual void notify(void *data = nullptr);

  virtual void connect(signal_cb_t, void *user_data);
  virtual void disconnect(signal_cb_t, void *user_data);

private:
  static signal_t _ids;
  const signal_t  _id;
};

#endif /* SIGNAL_SYSTEM_H */
