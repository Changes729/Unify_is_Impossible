/** See a brief introduction (right-hand button) */
#include "SDL_plane.h"
/* Private include -----------------------------------------------------------*/
#include "SDL2/SDL.h"

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

SDLPlane::SDLPlane(SDLWidget& parent)
    : SDLWidget{parent}
    , _sdl_texture{nullptr}
    , _bg_color{0xFFFFFFFF}
    , _size{parent.size()}
{}

SDLPlane::~SDLPlane() { SDL_DestroyTexture(_sdl_texture); }

point_t SDLPlane::size() { return _size; }

void SDLPlane::resize(const point_t& size) { _size = size; }

void SDLPlane::render(point_t pos_start, point_t size)
{
  SDL_Rect rect{
      .x = start_at().x,
      .y = start_at().y,
      .w = this->size().x,
      .h = this->size().y,
  };

  SDL_SetRenderDrawColor(renderer().renderer(),
                         _bg_color.arg.r,
                         _bg_color.arg.g,
                         _bg_color.arg.b,
                         _bg_color.arg.a);
  SDL_RenderFillRect(renderer().renderer(), &rect);
}
