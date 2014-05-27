#include "gui/GUIPane.h"

#include "App.h"
#include "ConfigSettings.h"
#include "ErrorMacros.h"
#include "GUIFont.h"

namespace GUI {

struct Pane::Impl
{
  /// Title.
  sf::String title_string;

  /// Title font.
  std::shared_ptr<Font> title_font;

  /// Title alignment on the Pane.
  HorizAlign title_alignment;

  /// Background shape.
  sf::RectangleShape bg_shape;
};

Pane::Pane(std::string name,
           sf::Vector2f dimensions,
           std::shared_ptr<Font> title_font)
  : Control(name, dimensions),
    impl(new Impl())
{
  ASSERT_CONDITION(title_font);

  impl->title_font = title_font;
  impl->title_alignment = HorizAlign::Center;

  /// Pane instances start out hidden until manually shown.
  set_instant_visibility(false);
}

Pane::~Pane()
{
  //dtor
}

void Pane::set_title(sf::String str)
{
  impl->title_string = str;
}

sf::String Pane::get_title() const
{
  return impl->title_string;
}

void Pane::set_title_alignment(HorizAlign alignment)
{
  impl->title_alignment = alignment;
}

HorizAlign Pane::get_title_alignment() const
{
  return impl->title_alignment;
}

void Pane::set_title_font(std::shared_ptr<Font> title_font)
{
  ASSERT_CONDITION(title_font);

  impl->title_font = title_font;
}

std::shared_ptr<Font> Pane::get_title_font() const
{
  return impl->title_font;
}

// === PROTECTED METHODS ======================================================

Font& Pane::get_title_font_ref()
{
  return *(impl->title_font.get());
}

EventResult Pane::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void Pane::_render(sf::RenderTarget& target, int frame)
{
  auto const& dimensions = get_dimensions();

  int title_height = impl->title_font->get_bold_font().getLineSpacing(Settings.text_title_size);

  // Text margins relative to the background rectangle.
  sf::Vector2f text_margin{10, 5};

  // Clear target texture.
  sf::RectangleShape bg_shape;

  bg_shape.setSize({dimensions.x, dimensions.y});
  bg_shape.setPosition({0, 0});
  bg_shape.setFillColor(get_focus() ?
                        Settings.pane_focused_bg_color :
                        Settings.pane_bg_color);
  target.draw(bg_shape);

  // Call the possibly-overridden render_contents.
  _render_contents(target, frame);

  /// @todo Set an icon for the pane, if one exists.

  // IF the pane has a title...
  if (!(impl->title_string.isEmpty()))
  {
    // Draw the title at the top.
    sf::RectangleShape title_rect;
    sf::Text title_text;

    title_rect.setFillColor(get_focus() ?
                            Settings.pane_focused_border_color :
                            Settings.pane_border_color);
    title_rect.setOutlineColor(get_focus() ?
                               Settings.pane_focused_border_color :
                               Settings.pane_border_color);
    title_rect.setOutlineThickness(Settings.pane_border_width);
    title_rect.setPosition(sf::Vector2f(0, 0));
    title_rect.setSize(sf::Vector2f(dimensions.x,
                                    title_height + (text_margin.y * 2)));

    target.draw(title_rect);

    title_text.setString(impl->title_string);
    title_text.setFont(impl->title_font->get_bold_font());
    title_text.setCharacterSize(Settings.text_title_size);

    title_text.setColor(Settings.pane_bg_color);

    sf::FloatRect rect_bounds = title_rect.getGlobalBounds();
    sf::FloatRect text_bounds = title_text.getGlobalBounds();

    sf::Vector2f text_origin;
    sf::Vector2f text_position;

    text_origin.y = text_bounds.top + (text_bounds.height / 2);
    text_position.y = rect_bounds.top + (rect_bounds.height / 2);

    switch (impl->title_alignment)
    {
    case HorizAlign::Left:
      text_origin.x = text_bounds.left;
      text_position.x = rect_bounds.left +
                        (text_margin.x + Settings.pane_border_width);
      break;

    case HorizAlign::Center:
      text_origin.x = text_bounds.left + (text_bounds.width / 2);
      text_position.x = rect_bounds.left + (rect_bounds.width / 2);
      break;

    case HorizAlign::Right:
      text_origin.x = text_bounds.left + text_bounds.width;
      text_position.x = (rect_bounds.left + rect_bounds.width) -
                        (text_margin.x + Settings.pane_border_width);
      break;
    }
    title_text.setOrigin(text_origin);
    title_text.setPosition(text_position);

    target.draw(title_text);
  }

  // Draw the border.
  sf::RectangleShape border_shape;

  border_shape.setSize({dimensions.x - (Settings.pane_border_width * 2),
                        dimensions.y - (Settings.pane_border_width * 2)});
  border_shape.setPosition({Settings.pane_border_width,
                            Settings.pane_border_width});
  border_shape.setFillColor(sf::Color::Transparent);
  border_shape.setOutlineColor(get_focus() ?
                               Settings.pane_focused_border_color :
                               Settings.pane_border_color);
  border_shape.setOutlineThickness(Settings.pane_border_width);
  target.draw(border_shape);
}

void Pane::_render_contents(sf::RenderTarget& target, int frame)
{
  // Default implementation does nothing.
}

} // end namespace GUI
