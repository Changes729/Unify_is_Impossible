/** See a brief introduction (right-hand button) */
#include "audio_manager.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <assert.h>

#include "log.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static AudioManager* _instance = nullptr;
static SDL_AudioSpec _sdl_audio_spec;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static SDL_AudioSpec convert(const AudioSpec_t&,
                             SDL_AudioCallback = nullptr,
                             void* userdata    = nullptr);
static void          _sdl_audio_cb(void* data, uint8_t* stream, int need);

/* Private function ----------------------------------------------------------*/
static SDL_AudioSpec convert(const AudioSpec_t& spec,
                             SDL_AudioCallback  cb,
                             void*              userdata)
{
  return SDL_AudioSpec{.freq     = spec.frequency,
                       .format   = spec.format.mess,
                       .channels = spec.channels,
                       .silence  = 0,
                       .samples  = spec.samples,
                       .padding  = 0,
                       .size     = 0,
                       .callback = cb,
                       .userdata = userdata};
}

static void _sdl_audio_cb(void* data, uint8_t* stream, int need)
{
  assert(data == _instance);
  AudioManager::instance()._audio_feed_cb(stream, need);
}

/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */

AudioManager& AudioManager::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

AudioManager* AudioManager::create()
{
  assert(_instance == nullptr);
  _instance = new AudioManager();
  return _instance;
}

void AudioManager::destroy()
{
  delete _instance;
  _instance = nullptr;
}

void AudioManager::_audio_feed_cb(uint8_t* stream, size_t need)
{
  uint8_t audio_source_count = size();
  uint8_t volume = get_sys_volume() / std::max(audio_source_count, (uint8_t)1);
  SDL_memset(stream, 0, need);
  for(auto& controller: *this) {
    if(controller->audio_spec() == _audio_spec) {
      controller->_audio_feed_cb(stream, need, volume);
    } else {
      LOG_ERROR("has error audio format.");
    }
  }
}

uint8_t AudioManager::max_volume() const { return 0x10; }

void AudioManager::set_sys_volume(int v)
{
  _sys_volume = v > max_volume() ? max_volume() : (v < 0 ? 0 : v);
}

AudioManager::AudioManager()
    : _audio_spec{
          .frequency = 44100,
          .format { /** pcm_s16le */
            .info {
              .bit_size        = 16,
              .is_float        = false,
              .__PLACE_HOLDER_ = 0,
              .is_bigendian    = false,
              .__place_holder_ = 0,
              .is_signed       = true,
            }
          },
          .channels = 2,
          .samples  = 4096,
      },
      _sys_volume{max_volume()},
      _mute{false}
{
  _sdl_audio_spec = convert(_audio_spec, _sdl_audio_cb, this);
  bool success    = (SDL_OpenAudio(&_sdl_audio_spec, NULL) == 0);
  assert_ifn(success) { LOG_ERROR("audio open failed."); }

  SDL_PauseAudio(0);
}

AudioManager::~AudioManager() { SDL_CloseAudio(); }