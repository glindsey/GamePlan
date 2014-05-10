#ifndef ZOOMFADE_H
#define ZOOMFADE_H

#include "IControlApparator.h"

namespace GUI {

namespace Apparators {

class ZoomFade : public IControlApparator
{
  public:
    ZoomFade();
    virtual ~ZoomFade();

    virtual void alter_shape(sf::RectangleShape& shape,
                             VisibilityState appear_state,
                             float appear_amount) override;

    virtual void alter_texture(sf::RenderTexture& texture,
                               VisibilityState appear_state,
                               float appear_amount) override;

  protected:
  private:
};

} // end namespace Apparators

} // end namespace GUI

#endif // ZOOMFADE_H
