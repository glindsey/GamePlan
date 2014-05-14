#include "GUIMenuItem.h"

namespace GUI {

struct MenuItem::Impl
{
  char dummy;
};

MenuItem::MenuItem(std::string name,
           sf::Vector2f dimensions,
           std::shared_ptr<Font> title_font)
  : Button(name, dimensions, title_font),
    impl(new Impl())
{
  //ctor
}

MenuItem::~MenuItem()
{
  //dtor
}

// === PROTECTED METHODS ======================================================

EventResult MenuItem::_handle_event(sf::Event& event)
{
  /// @todo Implement me
  return EventResult::Ignored;
}

void MenuItem::_render(sf::RenderTarget& target, int frame)
{
  /// @todo Implement me
}

} // end namespace GUI
