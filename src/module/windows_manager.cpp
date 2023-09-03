/** See a brief introduction (right-hand button) */
#include "windows_manager.h"

/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>
#include <assert.h>

#include <algorithm>
#include <iterator>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static WindowsManager* _instance = nullptr;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
IView::IView(IWindow& parent)
    : _parent{parent}
    , _visible{true}
{
  parent.register_child(this);
}

IView::~IView() { window().unregister_child(this); }

IWindow::IWindow() { WindowsManager::instance().register_child(this); }

IWindow::~IWindow() { WindowsManager::instance().unregister_child(this); }

/**
 * @brief  ...
 * @param  None
 * @retval None
 */
WindowsManager& WindowsManager::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

WindowsManager* WindowsManager::create(const char* name)
{
  assert(name != nullptr);
  assert(_instance == nullptr);
  _instance = new WindowsManager(name);
  return _instance;
}

void WindowsManager::destroy()
{
  delete _instance;
  _instance = nullptr;
}

void WindowsManager::render()
{
  for(auto win: *this) {
    win->render();
    win->present();
  }
}

WindowsManager::WindowsManager(const char* name)
{
  SDL_Init(SDL_INIT_EVERYTHING);
}

WindowsManager::~WindowsManager() { SDL_Quit(); }
