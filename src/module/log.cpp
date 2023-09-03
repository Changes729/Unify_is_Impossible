/** See a brief introduction (right-hand button) */
#include "log.h"
/* Private include -----------------------------------------------------------*/
/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef __DEBUG
#pragma message("program is in DEBUG mod")
static log_level_t _log_level = DEBUG;
#else
#pragma message("program is in NORMAL mod")
static log_level_t _log_level = ERROR;
#endif

/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/
/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */
log_level_t syslog_level() { return _log_level; }

void set_syslog_level(log_level_t level) { _log_level = level; }
