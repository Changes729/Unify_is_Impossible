/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <vector>

#include "audio_controller.h"
#include "manager_interface.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class AudioManager: public IManager<IAudioStreamController*>
{
public:
  static AudioManager& instance();
  static AudioManager* create();
  static void          destroy();

public:
  inline const AudioSpec_t& get_audio_spec() { return _audio_spec; }
  inline bool               is_mute() { return _mute; }
  uint8_t                   max_volume() const;
  void                      set_sys_volume(int v);
  inline uint8_t get_sys_volume() { return is_mute() ? 0 : _sys_volume; }

  void _audio_feed_cb(uint8_t* stream, size_t need);

protected:
  AudioManager();
  virtual ~AudioManager();

private:
  AudioSpec_t _audio_spec;
  uint8_t     _sys_volume;
  bool        _mute;
};

#endif /* AUDIO_MANAGER_H */
