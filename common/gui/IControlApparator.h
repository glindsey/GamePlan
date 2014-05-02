#ifndef ICONTROLAPPARATOR_H
#define ICONTROLAPPARATOR_H

#include <SFML/Graphics.hpp>

#include "GUIEnums.h"

namespace GUI {

/// This class defines an "apparator" which alters one or more aspects of
/// the control as it appears and/or disappears.
class IControlApparator
{
  public:
    virtual ~IControlApparator();

    virtual void alter_shape(sf::RectangleShape& shape,
                             VisibilityState appear_state,
                             float appear_amount) = 0;

    virtual void alter_texture(sf::RenderTexture& texture,
                               VisibilityState appear_state,
                               float appear_amount) = 0;
  protected:
  private:
};

} // end namespace GUI

#endif // ICONTROLAPPARATOR_H
