/** See a brief introduction (right-hand button) */
#include "timer_utils.h"
/* Private include -----------------------------------------------------------*/
#include <sys/time.h>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
unsigned long get_time()
{
  struct timeval time_now;
  gettimeofday(&time_now, nullptr);

  return (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

unsigned long get_utime()
{
  struct timeval time_now;
  gettimeofday(&time_now, nullptr);

  return time_now.tv_usec;
}
