/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include "SDL_Widget.h"
#include "SDL_Windows.h"
#include "event_manager.h"
#include "ff_video_controller.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class VideoPlayer: public SDLWidget
{
public:
  VideoPlayer(SDLWidget &, const std::string &v_file);
  virtual ~VideoPlayer();

public:
  virtual void render(point_t pos_start, point_t size) override;

  void play();
  void stop();
  void pause();

  void set_loop_mode(bool loop) { _loop_play = loop; }
  bool is_loop() { return _loop_play; }

  point_t size() override final;

protected:
  void feed_frame();
  void resize(const point_t &size) override final{};

private:
  enum STATE {
    PLAY,
    STOP,
    PAUSE,
  };

private:
  FFVideoController _controller;
  SDL_Texture      *_sdl_texture;
  void             *_timer_cb;

  bool  _loop_play;
  STATE _player_state;
};

#endif /* VIDEO_PLAYER_H */
