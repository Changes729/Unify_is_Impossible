/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WAV_PLAYER_H
#define WAV_PLAYER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include <string>

#include "audio_controller.h"
#include "audio_player.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class WavPlayer: public IAudioPlayer
{
public:
  WavPlayer(const std::string& file);
  virtual ~WavPlayer();

public:
  virtual void play() override;
  virtual void pause() override;
  virtual void stop() override;

  virtual bool is_pause() override;
  virtual bool is_play() override;
  virtual bool is_stop() override;

  virtual void loop_enable() override;
  virtual bool is_loop() override;

public:
  virtual void _audio_feed_cb(uint8_t* to_buffer,
                              size_t   allowed_size,
                              uint8_t  volume) override;

private:
  std::string _wav_name;
  uint8_t*    _wav_buffer;
  size_t      _wav_length;
  size_t      _wav_progress;

  bool _is_loop;
};

#endif /* WAV_PLAYER_H */
