/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TIMER_FEEDBACK_H
#define TIMER_FEEDBACK_H
#pragma once
/* Public include ------------------------------------------------------------*/
/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class TimerFeedback
{
public:
  TimerFeedback(unsigned _expect = 0);
  ~TimerFeedback();

private:
  unsigned      _expect;
  unsigned long _begin;
};

#endif /* TIMER_FEEDBACK_H */
