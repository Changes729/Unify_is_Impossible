/** See a brief introduction (right-hand button) */
#include "wav_player.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <audio_manager.h>

#include "log.h"

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
WavPlayer::WavPlayer(const std::string& file)
    : _wav_name(file)
    , _wav_buffer{nullptr}
    , _wav_length{0}
    , _wav_progress{0}
    , _is_loop{false}
{
  uint32_t      wav_length;
  SDL_AudioSpec audio_spec;

  auto ret = SDL_LoadWAV(file.c_str(), &audio_spec, &_wav_buffer, &wav_length);
  assert_ifn(ret == &audio_spec)
  {
    LOG_ERROR("could not get audio spec with %s", file.c_str());
  }
  else {
    _wav_length = wav_length;
    init(AudioSpec_t{
        .frequency = audio_spec.freq,
        .format    = audio_spec.format,
        .channels  = audio_spec.channels,
        .samples   = audio_spec.samples,
    });
  }
}

WavPlayer::~WavPlayer()
{
  SDL_FreeWAV(_wav_buffer);
  _wav_buffer = nullptr;
}

void WavPlayer::play() { open(); }

void WavPlayer::pause() { close(); }

void WavPlayer::stop()
{
  close();
  _wav_progress = 0;
}

bool WavPlayer::is_pause() { return !is_stream_open() && _wav_progress != 0; }

bool WavPlayer::is_play() { return is_stream_open(); }

bool WavPlayer::is_stop() { return !is_stream_open() && _wav_progress == 0; }

void WavPlayer::loop_enable() { _is_loop = true; }

bool WavPlayer::is_loop() { return _is_loop; }

void WavPlayer::_audio_feed_cb(uint8_t* stream, size_t need_feed, uint8_t volume)
{
  auto& audio_manager = AudioManager::instance();
  int   feed_size     = std::min(_wav_length - _wav_progress, need_feed);

  SDL_MixAudio(stream,
               _wav_buffer + _wav_progress,
               feed_size,
               SDL_MIX_MAXVOLUME * volume / audio_manager.max_volume());
  _wav_progress += feed_size;

  /** on audio end. */
  if(_wav_length == _wav_progress) {
    if(is_loop()) {
      _wav_progress = 0;
    } else {
      stop();
    }
  }
}
