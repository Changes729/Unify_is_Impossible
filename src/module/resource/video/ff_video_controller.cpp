/** See a brief introduction (right-hand button) */
#include "ff_video_controller.h"
/* Private include -----------------------------------------------------------*/
#include "assert.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

#include "log.h"

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct __FFVideoData_
{
  AVFormatContext* av_format_context;
  AVPacket         av_packet;
  bool             is_end;

  bool has_av_context() { return av_format_context != nullptr; }
  bool has_av_codec(int stream_index, const AVCodec** avcodec = nullptr)
  {
    assert(has_av_context());
    auto codec_id = av_format_context->streams[stream_index]->codecpar->codec_id;
    auto av_codec  = avcodec_find_decoder(codec_id);
    bool has_codec = (av_codec != nullptr);
    if(avcodec != nullptr && has_codec) {
      *avcodec = av_codec;
    }
    return has_codec;
  }

  bool has_stream(AVMediaType type, int* stream_index = nullptr)
  {
    assert(has_av_context());
    auto index       = av_find_best_stream(av_format_context,
                                     AVMEDIA_TYPE_VIDEO,
                                     -1,
                                     -1,
                                     nullptr,
                                     0);
    bool has_stream_ = (index != -1);
    if(stream_index != nullptr && has_stream_) {
      *stream_index = index;
    }

    return has_stream_;
  }

  AVPacket& curr_av_pack() { return av_packet; }
  bool      next_av_pack()
  {
    av_packet_unref(&av_packet);
    int state = av_read_frame(av_format_context, &av_packet);
    if(state != 0) {
      LOG_DEBUG("av base time %d, duration: %d", AV_TIME_BASE, av_packet.duration);
      LOG_DEBUG("av_read_frame get state: 0x%X", state);

      if(0 == av_packet.duration) {
        is_end = true;
      }
    }
    return state == 0;
  }

  AVCodecParameters* get_codec_params(int stream_index)
  {
    return av_format_context->streams[stream_index]->codecpar;
  }

  __FFVideoData_(const std::string& url)
      : av_format_context{nullptr}
      , is_end{false}
  {
    avformat_open_input(&av_format_context, url.c_str(), 0, nullptr);
    assert(av_format_context != nullptr);
    int state = av_read_frame(av_format_context, &av_packet);
    assert(state == 0);
  }
  ~__FFVideoData_()
  {
    av_packet_unref(&av_packet);
    avformat_close_input(&av_format_context);
  }

} FFVideoData_t;

typedef struct __FFVideoCodec_
{
  AVCodecContext* av_codec_context;
  AVFrame*        av_frame_next;
  AVFrame*        av_frame_curr;

  bool has_codec_context() { return av_codec_context != nullptr; }
  bool has_codec_screen_size(point_t* size = nullptr)
  {
    bool has = has_codec_context();
    if(has && size) {
      size->x = av_codec_context->width;
      size->y = av_codec_context->height;
    }
    return has;
  }

  void open() { avcodec_open2(av_codec_context, nullptr, nullptr); }
  void close() { avcodec_close(av_codec_context); }

  void update_frame(AVPacket* av_packet)
  {
    avcodec_send_packet(av_codec_context, av_packet);
    int state = avcodec_receive_frame(av_codec_context, av_frame_next);
    av_frame_free(&av_frame_curr);
    if(state == 0) {
      av_frame_curr = av_frame_clone(av_frame_next);
    } else {
      LOG_WARN("codec decode error %d\n", state);
    }
  }

  AVFrame* frame_curr() { return av_frame_curr; }

  __FFVideoCodec_(FFVideoData_t& ff_video_data, AVMediaType type)
      : av_codec_context{nullptr}
      , av_frame_next{nullptr}
      , av_frame_curr{nullptr}
  {
    const bool     FAILED  = true;
    const AVCodec* avcodec = nullptr;
    int            video_stream;

    if(ff_video_data.has_av_context() &&
       ff_video_data.has_stream(AVMEDIA_TYPE_VIDEO, &video_stream) &&
       ff_video_data.has_av_codec(video_stream, &avcodec))
    {
      av_codec_context = avcodec_alloc_context3(avcodec);
      av_frame_next    = av_frame_alloc();
      assert(av_codec_context != nullptr);

      auto param = ff_video_data.get_codec_params(video_stream);
      if(FAILED == avcodec_parameters_to_context(av_codec_context, param)) {
        assert(false);
        avcodec_free_context(&av_codec_context);
        av_frame_free(&av_frame_next);
        av_codec_context = nullptr;
      }
    }
  }
  ~__FFVideoCodec_()
  {
    av_frame_free(&av_frame_next);
    av_frame_free(&av_frame_curr);
    av_frame_next = nullptr;
    av_frame_curr = nullptr;
    avcodec_free_context(&av_codec_context);
  }

} FFVideoCodec_t;

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
FFVideoController::FFVideoController(const std::string& file)
    : _file{file}
    , _ff_video_data{new FFVideoData_t{file}}
    , _ff_video_codec{new FFVideoCodec_t{*_ff_video_data, AVMEDIA_TYPE_VIDEO}}
{
  if(_ff_video_codec->has_codec_context()) {
    _ff_video_codec->open();
  }
  next_frame(AVMEDIA_VIDEO);
}

FFVideoController::~FFVideoController()
{
  if(_ff_video_codec->has_codec_context()) {
    _ff_video_codec->close();
  }
  delete _ff_video_codec;
  _ff_video_codec = nullptr;

  delete _ff_video_data;
  _ff_video_data = nullptr;
}

bool FFVideoController::next_frame(AVMediaType_t type)
{
  bool     has_next     = false;
  AVFrame* curr_frame   = nullptr;
  int      stream_index = -1;
  auto&    av_pack      = _ff_video_data->curr_av_pack();
  if(_ff_video_data->has_stream((AVMediaType)type, &stream_index)) {
    do {
      has_next = _ff_video_data->next_av_pack();
    } while(av_pack.stream_index != stream_index && has_next);

    if(has_next) {
      _ff_video_codec->update_frame(&av_pack);
    }
  }

  return has_next;
}

bool FFVideoController::has_frame(AVMediaType_t type, AVFrame** saver)
{
  bool has_frame = false;

  if(type == AVMEDIA_VIDEO) {
    has_frame = _ff_video_data->has_av_context() &&
                _ff_video_codec->has_codec_context() &&
                _ff_video_codec->frame_curr() != nullptr &&
                !_ff_video_data->is_end;
    if(has_frame && saver != nullptr) {
      *saver = _ff_video_codec->frame_curr();
    }
  }

  return has_frame;
}

bool FFVideoController::is_end() { return _ff_video_data->is_end; }

void FFVideoController::clear() { _ff_video_data->is_end = false; }

void FFVideoController::seek_frame(size_t index)
{
  auto stream_index = av_find_best_stream(_ff_video_data->av_format_context,
                                          AVMEDIA_TYPE_VIDEO,
                                          -1,
                                          -1,
                                          nullptr,
                                          0);
  if(av_seek_frame(_ff_video_data->av_format_context,
                   stream_index,
                   index,
                   AVSEEK_FLAG_BACKWARD) < 0)
  {
    LOG_ERROR("failed seek frame");
  }
}

double FFVideoController::fps()
{
  auto& context = _ff_video_data->av_format_context;
  auto  stream_index =
      av_find_best_stream(context, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
  return av_q2d(context->streams[stream_index]->r_frame_rate);
}

point_t FFVideoController::video_size()
{
  point_t point{0, 0};

  assert(_ff_video_codec != nullptr);
  _ff_video_codec->has_codec_screen_size(&point);

  return point;
}
