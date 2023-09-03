/** See a brief introduction (right-hand button) */
#include "signal_system.h"
/* Private include -----------------------------------------------------------*/
/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
signal_t ISignal::_ids = 0;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
ISignal::ISignal()
    : _id{_ids++}
{}

void ISignal::notify(void* data)
{
  for(auto record: *this) {
    record.callback(record.user_data, id(), data);
  }
}

void ISignal::connect(signal_cb_t cb, void* user_data)
{
  register_child({cb, user_data});
}

void ISignal::disconnect(signal_cb_t cb, void* user_data)
{
  unregister_child({cb, user_data});
}
