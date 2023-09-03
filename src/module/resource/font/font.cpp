/** See a brief introduction (right-hand button) */
#include "font.h"
/* Private include -----------------------------------------------------------*/
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
IFont::IFont(const std::string path, const std::string family, size_t size)
    : _font_family{family}
    , _font_path{path}
    , _font_size{size}
{}
