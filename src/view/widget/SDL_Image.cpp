/** See a brief introduction (right-hand button) */
#include "SDL_Image.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL_image.h>

#include "log.h"

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
SDLImage::SDLImage(SDLWidget& parent, const std::string& image)
    : SDLWidget(parent)
    , _sdl_surface{IMG_Load(image.c_str())}
    , _sdl_texture{SDL_CreateTextureFromSurface(renderer().renderer(),
                                                _sdl_surface)}
    , _zoom_size{nullptr}
    , _zoom_percent{1.0, 1.0}
{
  /** sdl texture has size limit in some case. */
  assert_ifn(_sdl_texture != nullptr) { LOG_ERROR("%s", SDL_GetError()); }
}

SDLImage::~SDLImage()
{
  SDL_DestroyTexture(_sdl_texture);
  SDL_FreeSurface(_sdl_surface);
  delete _zoom_size;
  _zoom_size   = nullptr;
  _sdl_texture = nullptr;
  _sdl_surface = nullptr;
}

point_t SDLImage::size()
{
  point_t true_size;
  if(nullptr != _zoom_size) {
    true_size = *_zoom_size;
  } else {
    true_size = _raw_size() * _zoom_percent;
  }
  return true_size;
}

void SDLImage::render(point_t pos_start, point_t size)
{
  SDL_Rect source_rect{
      .x = 0,
      .y = 0,
      .w = _raw_size().x,
      .h = _raw_size().y,
  };
  SDL_Rect render_rect{
      .x = int(pos_start.x + start_at().x),
      .y = int(pos_start.y + start_at().y),
      .w = std::min(size.x - start_at().x, this->size().x),
      .h = std::min(size.y - start_at().y, this->size().y),
  };
  SDL_RenderCopy(renderer().renderer(), _sdl_texture, &source_rect, &render_rect);
}

void SDLImage::zoom(float percent)
{
  assert(_zoom_size != nullptr);
  _zoom_percent = {percent, percent};
}

void SDLImage::load_img(const std::string& img)
{
  auto img_surface = IMG_Load(img.c_str());
  auto render      = renderer().renderer();
  if(img_surface == nullptr) {
    LOG_ERROR("%s could not load img.", img.c_str());
  } else {
    SDL_DestroyTexture(_sdl_texture);
    SDL_FreeSurface(_sdl_surface);

    _sdl_surface = img_surface;
    _sdl_texture = SDL_CreateTextureFromSurface(render, _sdl_surface);

    assert(_sdl_texture != nullptr);
  }
}

void SDLImage::zoom(float w_percent, float h_percent)
{
  assert(_zoom_size != nullptr);
  _zoom_percent = {w_percent, h_percent};
}

void SDLImage::zoom_to(point_t size)
{
  delete _zoom_size;
  _zoom_size = nullptr;
  _zoom_size = new point_t(size);
}

point_t SDLImage::_raw_size()
{
  int x, y;
  SDL_QueryTexture(_sdl_texture, nullptr, nullptr, &x, &y);
  assert(x >= 0 && y >= 0);
  return {x, y};
}
