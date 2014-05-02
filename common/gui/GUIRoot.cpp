#include "GUIRoot.h"

namespace GUI {

Root::Root(std::string name,
           sf::Vector2f dimensions)
  : Control(name, dimensions)
{
  //ctor
}

Root::~Root()
{
  //dtor
}

// === PROTECTED METHODS ======================================================

EventResult Root::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void Root::_render(sf::RenderTarget& target, int frame)
{
  /// Implementation does nothing.
}

} // end namespace GUI
