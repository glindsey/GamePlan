#include "gui/GUIMenu.h"

#include "gui/GUIFont.h"
#include "ConfigSettings.h"
#include "ErrorMacros.h"

namespace GUI {

struct Menu::Impl
{
  std::shared_ptr<Font> font;
  Orientation orientation;
};

Menu::Menu(std::string name,
           sf::Vector2f dimensions,
           std::shared_ptr<Font> menu_font,
           Orientation menu_orientation)
  : Control(name, dimensions),
    impl(new Impl())
{
  ASSERT_CONDITION(menu_font);
  impl->font = menu_font;
  impl->orientation = menu_orientation;
}

Menu::~Menu()
{
  //dtor
}

void Menu::set_font(std::shared_ptr<Font> const& menu_font)
{
  ASSERT_CONDITION(menu_font);
  impl->font = menu_font;
}

std::shared_ptr<Font> Menu::get_font() const
{
  return impl->font;
}

void Menu::set_orientation(Orientation orientation)
{
  impl->orientation = orientation;
}

Orientation Menu::get_orientation() const
{
  return impl->orientation;
}

// === PROTECTED METHODS ======================================================

EventResult Menu::_handle_event(sf::Event& event)
{
  /// @todo Implement me
  return EventResult::Ignored;
}

void Menu::_render(sf::RenderTarget& target, int frame)
{
  auto const& dimensions = get_dimensions();

  // Text margins relative to the background rectangle.
  sf::Vector2f text_margin{10, 5};

  // Clear target texture.
  sf::RectangleShape bg_shape;

  bg_shape.setSize({dimensions.x, dimensions.y});
  bg_shape.setPosition({0, 0});
  bg_shape.setFillColor(get_focus() ?
                        Settings.menu_focused_bg_color :
                        Settings.menu_bg_color);
  target.draw(bg_shape);

  // Draw the border.
  sf::RectangleShape border_shape;

  border_shape.setSize({dimensions.x - (Settings.menu_border_width * 2),
                        dimensions.y - (Settings.menu_border_width * 2)});
  border_shape.setPosition({Settings.menu_border_width,
                            Settings.menu_border_width});
  border_shape.setFillColor(sf::Color::Transparent);
  border_shape.setOutlineColor(get_focus() ?
                               Settings.menu_focused_border_color :
                               Settings.menu_border_color);
  border_shape.setOutlineThickness(Settings.menu_border_width);
  target.draw(border_shape);
}

} // end namespace GUI
