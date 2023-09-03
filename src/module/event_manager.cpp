/** See a brief introduction (right-hand button) */
#include "event_manager.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>

#include <functional>

#include "config.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static EventManager* _instance = nullptr;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
EventManager& EventManager::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

EventManager* EventManager::create()
{
  assert(_instance == nullptr);
  _instance = new EventManager();

  return _instance;
}

void EventManager::destroy()
{
  delete _instance;
  _instance = nullptr;
}

void EventManager::notify_all()
{
  for(auto e: *this) {
    e->notify();
  }
}

EventSender::EventSender() { EventManager::instance().register_child(this); }

EventSender::~EventSender() { EventManager::instance().unregister_child(this); }