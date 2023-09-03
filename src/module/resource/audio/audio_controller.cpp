/** See a brief introduction (right-hand button) */
#include "audio_controller.h"
/* Private include -----------------------------------------------------------*/
#include <assert.h>
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
IAudioStreamController::IAudioStreamController()
    : _is_open{false}
    , _audio_spec{}
{}

IAudioStreamController::~IAudioStreamController() { close(); }

void IAudioStreamController::init(const AudioSpec_t& spec, bool auto_play)
{
  auto device_spec = AudioManager::instance().get_audio_spec();
  _audio_spec      = spec;

  if(device_spec != spec) {
    LOG_ERROR("audio current could not play a different sound file.");
  } else if(auto_play) {
    open();
  }
}

void IAudioStreamController::open()
{
  if(!_is_open) {
    _is_open = true;
    AudioManager::instance().register_child(this);
  }
}

void IAudioStreamController::close()
{
  if(_is_open) {
    _is_open = false;
    AudioManager::instance().unregister_child(this);
  }
}
