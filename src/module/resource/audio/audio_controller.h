/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

#include <functional>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/**
 *  \brief Audio format flags.
 *
 *  These are what the 16 bits in SDL_AudioFormat currently mean...
 *  (Unspecified bits are always zero).
 *
 *  \verbatim
    ++-----------------------sample is signed if set
    ||
    ||       ++-----------sample is bigendian if set
    ||       ||
    ||       ||          ++---sample is float if set
    ||       ||          ||
    ||       ||          || +---sample bit size---+
    ||       ||          || |                     |
    15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    \endverbatim
 *
 *  There are macros in SDL 2.0 and later to query these bits.
 */
typedef union {
  uint16_t mess;
  struct
  {
    uint16_t bit_size        : 8;
    uint16_t is_float        : 1;
    uint16_t __PLACE_HOLDER_ : 3;
    uint16_t is_bigendian    : 1;
    uint16_t __place_holder_ : 2;
    uint16_t is_signed       : 1;
  } info;
} AudioFormat_t;

/**
 *  The calculated values in this structure are calculated by SDL_OpenAudio().
 *
 *  For multi-channel audio, the default SDL channel mapping is:
 *  2:  FL  FR                          (stereo)
 *  3:  FL  FR LFE                      (2.1 surround)
 *  4:  FL  FR  BL  BR                  (quad)
 *  5:  FL  FR LFE  BL  BR              (4.1 surround)
 *  6:  FL  FR  FC LFE  SL  SR          (5.1 surround - last two can also be BL BR)
 *  7:  FL  FR  FC LFE  BC  SL  SR      (6.1 surround)
 *  8:  FL  FR  FC LFE  BL  BR  SL  SR  (7.1 surround)
 */
typedef struct
{
  int           frequency;
  AudioFormat_t format;
  uint8_t       channels;
  uint16_t      samples;
} AudioSpec_t;

inline bool operator==(const AudioSpec_t& a, const AudioSpec_t& b)
{
  return a.frequency == b.frequency && a.format.mess == b.format.mess &&
         a.channels == b.channels && a.samples == b.samples;
}

inline bool operator!=(const AudioSpec_t& a, const AudioSpec_t& b)
{
  return !(a == b);
}

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IAudioStreamController
{
public:
  IAudioStreamController();
  virtual ~IAudioStreamController();

  inline bool               is_stream_open() { return _is_open; }
  inline const AudioSpec_t& audio_spec() { return _audio_spec; }

  virtual void init(const AudioSpec_t&, bool auto_play = true);
  virtual void open();
  virtual void close();

  virtual void _audio_feed_cb(uint8_t* to_buffer,
                              size_t   allowed_size,
                              uint8_t  volume) = 0;

private:
  bool        _is_open;
  AudioSpec_t _audio_spec;
};

#endif /* AUDIO_PLAYER_H */