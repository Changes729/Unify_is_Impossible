/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <list>
#include <string>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
std::string operator "" _RESOURCE(const char*, std::size_t len);

/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class SystemManager
{
public:
  static SystemManager& instance();
  static SystemManager* create();
  static void           destroy();

public:
  SystemManager();
  virtual ~SystemManager();

  std::list<std::string> config_path();
  const std::string      cfg_path();

  /* read & write */
  std::string& resource_path() { return _resource_path; }
  std::string& url_host() { return _url_host; }
  std::string& device_id() { return _device_id; }
  std::string& download_url() { return _download_url; }

private:
  std::string _cfg_path;
  std::string _resource_path;
  std::string _url_host;
  std::string _device_id;
  std::string _download_url;
};

#endif /* SYSTEM_MANAGER_H */
