#include "GUIMenu.h"

namespace GUI {

struct Menu::Impl
{
  char dummy;
};

Menu::Menu(std::string name,
           sf::Vector2f dimensions,
           std::shared_ptr<Font> title_font,
           std::shared_ptr<Font> menu_font,
           Orientation menu_orientation)
  : Pane(name, dimensions, title_font),
    impl(new Impl())
{
  //ctor
}

Menu::~Menu()
{
  //dtor
}

// === PROTECTED METHODS ======================================================

EventResult Menu::_handle_event(sf::Event& event)
{
  /// @todo Implement me
  return EventResult::Ignored;
}

void Menu::_render(sf::RenderTarget& target, int frame)
{
  /// @todo Implement me
}

} // end namespace GUI
