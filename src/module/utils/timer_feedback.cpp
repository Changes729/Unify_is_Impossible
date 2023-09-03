/** See a brief introduction (right-hand button) */
#include "timer_feedback.h"
/* Private include -----------------------------------------------------------*/
#include "log.h"
#include "timer_utils.h"

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
TimerFeedback::TimerFeedback(unsigned expect)
    : _expect{expect}
    , _begin{get_utime()}
{}

TimerFeedback::~TimerFeedback()
{
  auto escape = get_utime() - _begin;
  LOG_DEBUG("take time %u us", escape);
  if(_expect < escape) {
    if(_expect) assert(false);
  }
}
