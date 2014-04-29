#include "GUIRoot.h"

GUIRoot::GUIRoot(std::string name,
                 sf::Vector2f dimensions)
  : GUIControl(name, dimensions)
{
  //ctor
}

GUIRoot::~GUIRoot()
{
  //dtor
}

// === PROTECTED METHODS ======================================================

EventResult GUIRoot::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void GUIRoot::_render(sf::RenderTarget& target, int frame)
{
  /// Implementation does nothing.
}
