/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "audio_controller.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IAudioPlayer: public IAudioStreamController
{
public:
  virtual void play()  = 0;
  virtual void pause() = 0;
  virtual void stop()  = 0;

  virtual bool is_pause() = 0;
  virtual bool is_play()  = 0;
  virtual bool is_stop()  = 0;

  virtual void loop_enable() = 0;
  virtual bool is_loop()     = 0;
};

#endif /* AUDIO_CONTROLLER_H */