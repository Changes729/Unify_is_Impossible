/** See a brief introduction (right-hand button) */
#include "widget.h"
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
IWidget::IWidget(IRenderer& renderer, IWidget* parent)
    : _parent{parent}
    , _renderer{renderer}
    , _visible{true}
{
  if(parent) {
    parent->register_child(this);
  }
}

IWidget::IWidget(IWidget& parent)
    : IWidget(parent.renderer(), &parent)
{}

IWidget::~IWidget()
{
  if(parent()) {
    parent()->unregister_child(this);
  }
}
