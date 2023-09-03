/** See a brief introduction (right-hand button) */
#include "SDL_Font.h"
/* Private include -----------------------------------------------------------*/
#include "SDL2/SDL_ttf.h"
#include "assert.h"

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
void SDLFont::init() { TTF_Init(); }

SDLFont::SDLFont(const std::string path, const std::string family, size_t size)
    : IFont(path, family, size)
    , _font{TTF_OpenFont(_font_path.c_str(), _font_size)}
{
  assert(_font != nullptr);
}

SDLFont::~SDLFont()
{
  TTF_CloseFont(_font);
  _font = nullptr;
}