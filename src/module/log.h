/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOG_H
#define LOG_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <assert.h>
#include <stdio.h>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
#define TO_STR(x) #x

#define __log_with_tag(level_, info, ...)                                      \
  if(level_ <= syslog_level()) {                                               \
    fprintf(stdout, "[%s] ", TO_STR(level_));                                  \
    fprintf(stdout, info __VA_OPT__(, ) __VA_ARGS__);                          \
    fprintf(stdout, "\n");                                                     \
  }

#define LOG_WARN(info, ...)                                                    \
  __log_with_tag(WARN, info __VA_OPT__(, ) __VA_ARGS__)

#define LOG_INFO(info, ...)                                                    \
  __log_with_tag(INFO, info __VA_OPT__(, ) __VA_ARGS__)

#define LOG_DEBUG(info, ...)                                                   \
  __log_with_tag(DEBUG, info __VA_OPT__(, ) __VA_ARGS__)

#define LOG_ERROR(info, ...)                                                   \
  __log_with_tag(ERROR, info __VA_OPT__(, ) __VA_ARGS__)

#define assert_ifn(exp)                                                        \
  assert((exp));                                                               \
  if(!(exp))

/* Public typedef ------------------------------------------------------------*/
typedef enum {
  NONE,
  INFO,
  WARN,
  ERROR,
  DEBUG,
} log_level_t;

/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
log_level_t syslog_level();
void        set_syslog_level(log_level_t);

#endif /* LOG_H */
