#include "ZoomFade.h"

namespace GUI {

namespace Apparators {

ZoomFade::ZoomFade()
{
  //ctor
}

ZoomFade::~ZoomFade()
{
  //dtor
}

void ZoomFade::alter_shape(sf::RectangleShape& shape,
                           VisibilityState appear_state,
                           float appear_amount)
{
  auto dimensions = shape.getSize();

  shape.setSize({dimensions.x * powf(appear_amount, 0.1),
                 dimensions.y * powf(appear_amount, 0.1)});

  shape.setFillColor({255, 255, 255, (unsigned char)(appear_amount * 255.0f)});
}

void ZoomFade::alter_texture(sf::RenderTexture& texture,
                             VisibilityState appear_state,
                             float appear_amount)
{
  // this apparator does not alter the texture
}

} // end namespace Apparators

} // end namespace GUI
