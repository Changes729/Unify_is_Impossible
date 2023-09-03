/** See a brief introduction (right-hand button) */
#include "video_player.h"
/* Private include -----------------------------------------------------------*/
#include "SDL2/SDL.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

#include "SDL_Event.h"
#include "event_timer.h"
#include "timer_feedback.h"

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

VideoPlayer::VideoPlayer(SDLWidget &parent, const std::string &v_file)
    : SDLWidget{parent}
    , _controller{v_file}
    , _sdl_texture{SDL_CreateTexture(renderer().renderer(),
                                     SDL_PIXELFORMAT_IYUV,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     size().x,
                                     size().y)}
    , _loop_play{false}
    , _player_state{STOP}
{
  _timer_cb = TimerEventManager::instance().every(1000 / _controller.fps(),
                                                  TIMER_CALLBACK(
                                                      &VideoPlayer::feed_frame),
                                                  this);
  set_visible(false);
}

VideoPlayer::~VideoPlayer()
{
  SDL_DestroyTexture(_sdl_texture);
  TimerEventManager::instance().cancel(_timer_cb);
  _timer_cb = nullptr;
}

void VideoPlayer::render(point_t pos_start, point_t size)
{
  auto     sdl_renderer = renderer().renderer();
  AVFrame *_av_frame;
  SDL_Rect texture_rect{
      .x = 0,
      .y = 0,
      .w = int(_controller.video_size().x),
      .h = int(_controller.video_size().y),
  };
  SDL_Rect render_rect{
      .x = int(pos_start.x + start_at().x),
      .y = int(pos_start.y + start_at().y),
      .w = int(_controller.video_size().x),
      .h = int(_controller.video_size().y),
  };
  if(_controller.has_frame(AVMEDIA_VIDEO, &_av_frame)) {
    SDL_UpdateYUVTexture(_sdl_texture,
                         &texture_rect,
                         _av_frame->data[0],
                         _av_frame->linesize[0],
                         _av_frame->data[1],
                         _av_frame->linesize[1],
                         _av_frame->data[2],
                         _av_frame->linesize[2]);
  }
  /** move render out, so that video could stop at last frame. */
  SDL_RenderCopy(sdl_renderer, _sdl_texture, NULL, &render_rect);
}

void VideoPlayer::play()
{
  _player_state = PLAY;
  set_visible(true);
  _controller.clear();
  /** feed_frame will load first video frame. */
  feed_frame();
}

void VideoPlayer::stop()
{
  _player_state = STOP;
  _controller.seek_frame(0);
}

void VideoPlayer::pause() { _player_state = PAUSE; }

void VideoPlayer::feed_frame()
{
  switch(_player_state) {
    case PLAY:
      _controller.next_frame(AVMEDIA_VIDEO);
      if(_controller.is_end()) {
        stop();

        if(is_loop()) {
          play();
        }
      }
      break;
    default:
      break;
  }
}

point_t VideoPlayer::size() { return _controller.video_size(); }