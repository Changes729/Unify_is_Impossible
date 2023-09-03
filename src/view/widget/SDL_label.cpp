/** See a brief introduction (right-hand button) */
#include "SDL_label.h"
/* Private include -----------------------------------------------------------*/
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL_Font.h"
#include "label.h"
#include "point_helper.h"

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
SDLLabel::SDLLabel(SDLWidget &parent)
    : SDLWidget{parent}
    , _sdl_font{nullptr}
    , _bg_color{0xFFFFFF00}
    , _label_color{0xFFFFFFFF}
    , _sdl_texture{nullptr}
    , _string{}
    , _size{0, 0}
{}

SDLLabel::~SDLLabel() { SDL_DestroyTexture(_sdl_texture); }

const SDLFont *SDLLabel::font() { return _sdl_font; }

const char *SDLLabel::label()
{
  return _string.length() ? _string.c_str() : nullptr;
}

void SDLLabel::update_text(const std::string &str)
{
  _string = str;

  /**
   * BUG RECORD
   *
   * 1. if _string length is null. sdl_surface is nullptr.
   * 2. need re-cal string length.
   */
  if(_string.length() == 0) {
    _size = {0, 0};
    return;
  }

  SDL_Surface *sdl_surface  = nullptr;
  auto         sdl_renderer = renderer().renderer();
  SDL_Color    label_color  = {_label_color.arg.r,
                               _label_color.arg.g,
                               _label_color.arg.b,
                               _label_color.arg.a};
  SDL_Color    bg_color     = {_bg_color.arg.r,
                               _bg_color.arg.g,
                               _bg_color.arg.b,
                               _bg_color.arg.a};

  sdl_surface = TTF_RenderUTF8_Shaded(_sdl_font->get_font(),
                                      _string.c_str(),
                                      label_color,
                                      bg_color);
  assert(sdl_surface != nullptr);
  assert(sdl_surface->w >= 0 && sdl_surface->h >= 0);
  _size = {sdl_surface->w, sdl_surface->h};

  SDL_DestroyTexture(_sdl_texture);
  _sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);
  assert(_sdl_texture != nullptr);
  SDL_FreeSurface(sdl_surface);
}

point_t SDLLabel::size() { return _size; }

void SDLLabel::render(point_t pos_start, point_t render_size)
{
  auto     sdl_renderer = renderer().renderer();
  SDL_Rect src{
      .x = int(0),
      .y = int(0),
      .w = int(std::min(size().x, render_size.x - start_at().x)),
      .h = int(std::min(size().y, render_size.y - start_at().y)),
  };
  SDL_Rect rect{
      .x = int(pos_start.x + start_at().x),
      .y = int(pos_start.y + start_at().y),
      .w = src.w,
      .h = src.h,
  };

  SDL_RenderCopy(sdl_renderer, _sdl_texture, &src, &rect);
}
