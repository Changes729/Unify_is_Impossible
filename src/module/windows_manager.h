/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WINDOWS_MANAGER_H
#define WINDOWS_MANAGER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <list>

#include "manager_interface.h"
#include "point_helper.h"
#include "render/renderer.h"
#include "style/style.h"

#include "widget.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class IWindow;
class IView
{
public:
  IView(IWindow& parent);
  virtual ~IView();

  bool             visible() { return _visible; }
  void             set_visible(bool show) { _visible = show; }
  virtual void     render() = 0;
  virtual IWindow& window() { return _parent; }

private:
  IWindow& _parent;
  bool     _visible;
};

class IWindow: public IManager<IView*>
{
public:
  IWindow();
  virtual ~IWindow();

  virtual void render()  = 0;
  virtual void present() = 0;

  virtual point_t size() = 0;
};

class WindowsManager: public IManager<IWindow*>
{
public:
  static WindowsManager& instance();
  static WindowsManager* create(const char* name = "");
  static void            destroy();

public:
  void render();

protected:
  WindowsManager(const char* name);
  ~WindowsManager();
};

#endif /* WINDOWS_MANAGER_H */
