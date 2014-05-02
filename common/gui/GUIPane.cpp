#include "gui/GUIPane.h"

#include "App.h"
#include "ConfigSettings.h"
#include "GUIFont.h"

namespace GUI {

struct Pane::Impl
{
  /// Title.
  sf::String title_string;

  /// Title font.
  std::shared_ptr<Font> title_font;

  /// Background shape.
  sf::RectangleShape bg_shape;
};

Pane::Pane(std::string name,
           sf::Vector2f dimensions,
           std::shared_ptr<Font> title_font)
  : Control(name, dimensions),
    impl(new Impl())
{
  impl->title_font = title_font;

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

// === PROTECTED METHODS ======================================================

EventResult Pane::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void Pane::_render(sf::RenderTarget& target, int frame)
{
  auto const& dimensions = get_dimensions();

  int title_spacing_y = impl->title_font->get_bold_font().getLineSpacing(Settings.text_title_size);

  // Text offsets relative to the background rectangle.
  float text_offset_x = 3;
  float text_offset_y = 3;

  // Clear target texture.
  sf::RectangleShape bg_shape;

  bg_shape.setSize({dimensions.x, dimensions.y});
  bg_shape.setPosition({0, 0});
  bg_shape.setFillColor(Settings.window_bg_color);
  target.draw(bg_shape);

  // Call the possibly-overridden render_contents.
  _render_contents(target, frame);

  /// @todo Set an icon for the pane, if one exists.

  // IF the pane has a title...
  if (!(impl->title_string.isEmpty()))
  {
    // Draw the title in the upper-left corner.
    sf::RectangleShape title_rect;
    sf::Text title_text;

    title_rect.setFillColor(get_focus() ?
                            Settings.window_focused_border_color :
                            Settings.window_border_color);
    title_rect.setOutlineColor(get_focus() ?
                               Settings.window_focused_border_color :
                               Settings.window_border_color);
    title_rect.setOutlineThickness(Settings.window_border_width);
    title_rect.setPosition(sf::Vector2f(0, 0));
    title_rect.setSize(sf::Vector2f(dimensions.x,
                                    title_spacing_y + (text_offset_y * 2)));

    target.draw(title_rect);

    title_text.setString(impl->title_string);
    title_text.setFont(impl->title_font->get_bold_font());
    title_text.setCharacterSize(Settings.text_title_size);

    title_text.setColor(Settings.window_bg_color);
    title_text.setPosition(sf::Vector2f(text_offset_x + title_spacing_y,
                                        text_offset_y));
    target.draw(title_text);
  }

  // Draw the border.
  sf::RectangleShape border_shape;

  border_shape.setSize({dimensions.x - (Settings.window_border_width * 2),
                        dimensions.y - (Settings.window_border_width * 2)});
  border_shape.setPosition({Settings.window_border_width,
                            Settings.window_border_width});
  border_shape.setFillColor(sf::Color::Transparent);
  border_shape.setOutlineColor(get_focus() ?
                               Settings.window_focused_border_color :
                               Settings.window_border_color);
  border_shape.setOutlineThickness(Settings.window_border_width);
  target.draw(border_shape);
}

void Pane::_render_contents(sf::RenderTarget& target, int frame)
{
  // Default implementation does nothing.
}

} // end namespace GUI
