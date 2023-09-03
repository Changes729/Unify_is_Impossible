/** See a brief introduction (right-hand button) */
#include "SDL_View.h"
/* Private include -----------------------------------------------------------*/
#include <SDL2/SDL.h>

/* Private namespace ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private template ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private class -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
SDL_Vertex _convert(const vertex_t& vertex);

/* Private function ----------------------------------------------------------*/
SDL_Vertex _convert(const vertex_t& vertex)
{
  auto color = vertex.color.arg;
  return SDL_Vertex{SDL_FPoint{vertex.pos.x, vertex.pos.y},
                    SDL_Color{color.r, color.g, color.b, color.a},
                    SDL_FPoint{0}};
}

/* Private class function ----------------------------------------------------*/
/**
 * @brief  ...
 * @param  None
 * @retval None
 */

SDLView::SDLView(SDLWindow& win)
    : SDLWidget{win.get_renderer()}
    , IView{win}
    , _sdl_window{win} {};

SDLView::~SDLView() {}

void SDLView::render(point_t pos_start, point_t size)
{
  for(auto& widget: *this) {
    if(widget->is_visible()) {
      widget->render(pos_start, size);
    }
  }
}

void SDLView::clear(const color_t __c)
{
  const auto& color = __c.arg;
  SDL_SetRenderDrawColor(renderer().renderer(), color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer().renderer());
}

void SDLView::draw_geometry(const std::vector<vertex_t>& v)
{
  std::vector<SDL_Vertex> verts{v.size()};

  std::transform(v.cbegin(), v.cend(), verts.begin(), _convert);
  SDL_RenderGeometry(renderer().renderer(),
                     nullptr,
                     verts.data(),
                     verts.size(),
                     nullptr,
                     0);
}
