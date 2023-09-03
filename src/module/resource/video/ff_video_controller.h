/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FF_VIDEO_CONTROLLER_H
#define FF_VIDEO_CONTROLLER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <stddef.h>

#include <string>

#include "point_helper.h"

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
typedef enum {
  AVMEDIA_VIDEO,
  AVMEDIA_AUDIO,
  AVMEDIA_DATA,  ///< Opaque data information usually continuous
  AVMEDIA_SUBTITLE,
} AVMediaType_t;

/* Public typedef ------------------------------------------------------------*/
typedef struct __FFVideoData_  FFVideoData_t;
typedef struct __FFVideoCodec_ FFVideoCodec_t;
struct AVFrame;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
class FFVideoController
{
public:
  FFVideoController(const std::string& file);
  virtual ~FFVideoController();

  bool next_frame(AVMediaType_t);
  bool has_frame(AVMediaType_t, AVFrame** saver = nullptr);
  void seek_frame(size_t index);

  bool is_end();
  void clear();

  double  fps();
  point_t video_size();

private:
  std::string     _file;
  FFVideoData_t*  _ff_video_data;
  FFVideoCodec_t* _ff_video_codec;
};

#endif /* FF_VIDEO_CONTROLLER_H */
