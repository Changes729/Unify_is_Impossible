/** See a brief introduction (right-hand button) */
#include "system_manager.h"
/* Private include -----------------------------------------------------------*/
#include <assert.h>
#include <audio_manager.h>
#include <string.h>

#include <algorithm>
#include <filesystem>
#include <fstream>

#include "temp_cstr.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CFG_FILE "punch_config.conf"

/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static SystemManager* _instance = nullptr;

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
std::string operator""_RESOURCE(const char* relative, size_t _)
{
  std::string path;
  if(_instance != nullptr) {
    auto resource_path = _instance->resource_path();
    if(resource_path[resource_path.length() - 1] != '/') {
      resource_path += '/';
    }

    path = resource_path + relative;
  } else {
    path = relative;
  }

  return path;
}

/**
 * @brief  ...
 * @param  None
 * @retval None
 */
SystemManager& SystemManager::instance()
{
  assert(_instance != nullptr);
  return *_instance;
}

SystemManager* SystemManager::create()
{
  assert(_instance == nullptr);
  _instance = new SystemManager();
  assert(_instance != nullptr);
  return _instance;
}

void SystemManager::destroy()
{
  delete _instance;
  _instance = nullptr;
}

SystemManager::SystemManager()
{
  for(auto& config_path: config_path()) {
    std::string config_file = config_path + CFG_FILE;
    if(std::filesystem::exists(config_file)) {
      std::ifstream f(config_file);
      std::string   cfg_str;

      _cfg_path = config_file;
      f.close();
      break;
    }
  }
}

SystemManager::~SystemManager() {}

std::list<std::string> SystemManager::config_path()
{
  auto                   env_str  = std::getenv("PUNCH_CONFIG_PATH");
  std::string            env_path = env_str ? env_str : "";
  std::list<std::string> path_list;

  env_path.append("\0\0");
  std::replace(env_path.begin(), env_path.end(), ':', '\0');
  const char* str = env_path.c_str();
  while(str[0] != '\0' && str < env_path.c_str() + env_path.length()) {
    path_list.push_back(str);
    str += strlen(str) + 1;
  }

  path_list.push_back("./");

  return path_list;
}

const std::string SystemManager::cfg_path()
{
  std::string cfg_path = _cfg_path.length() ? _cfg_path : CFG_FILE;
  return cfg_path;
}
