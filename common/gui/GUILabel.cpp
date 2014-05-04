#include "gui/GUILabel.h"

#include "App.h"
#include "ConfigSettings.h"
#include "GUIFont.h"

namespace GUI {

struct Label::Impl
{
  /// Title.
  sf::String text_string;

  /// Title font.
  std::shared_ptr<Font> text_font;

  /// Text size.
  unsigned int text_size;

  /// Text alignment.
  Align text_alignment;

};

Label::Label(std::string name,
             sf::Vector2f dimensions,
             std::shared_ptr<Font> text_font) :
  Control(name, dimensions),
  impl(new Impl())
{
  impl->text_font = text_font;
  impl->text_size = Settings.text_default_size;
  impl->text_alignment = {HorizAlign::Left, VertAlign::Top};
}

Label::~Label()
{
  //dtor
}

void Label::set_text(sf::String str)
{
  impl->text_string = str;
}

sf::String Label::get_text() const
{
  return impl->text_string;
}

void Label::set_text_size(unsigned int text_size)
{
  impl->text_size = text_size;
}

unsigned int Label::get_text_size() const
{
  return impl->text_size;
}

void Label::set_text_alignment(Align alignment)
{
  impl->text_alignment = alignment;
}

Align Label::get_text_alignment() const
{
  return impl->text_alignment;
}


// === PROTECTED METHODS ======================================================

EventResult Label::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void Label::_render(sf::RenderTarget& target, int frame)
{
  // GSL TODO: Handle proper line wrapping for labels.

  sf::Vector2u dimensions = target.getSize();
  target.clear(sf::Color::Transparent);

  //int line_spacing_y = impl->text_font->get_normal_font().getLineSpacing(Settings.text_default_size);

  // IF there is some text...
  if (!(impl->text_string.isEmpty()))
  {
    // Draw a rect around the text area.
    // Although this is not really necessary, it is useful for debugging
    // because we can turn on an outline.

    if (Settings.debug_control_borders)
    {
      sf::RectangleShape rect;

      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor(Settings.debug_control_borders ?
                           sf::Color::Black :
                           sf::Color::Transparent);
      rect.setOutlineThickness(1);
      rect.setPosition(sf::Vector2f(1, 1));
      rect.setSize(sf::Vector2f(dimensions.x - 2, dimensions.y - 2));

      target.draw(rect);
    }

    // Draw the text.
    sf::Text text;

    text.setString(impl->text_string);
    text.setFont(impl->text_font->get_normal_font());
    text.setCharacterSize(impl->text_size);

    text.setColor(Settings.text_color);

    sf::Vector2u texture_size = target.getSize();
    sf::FloatRect text_bounds = text.getGlobalBounds();

    sf::Vector2f text_origin;
    sf::Vector2f text_position;

    switch (impl->text_alignment.horiz)
    {
    case HorizAlign::Left:
      text_origin.x = text_bounds.left;
      text_position.x = 0;
      break;

    case HorizAlign::Center:
      text_origin.x = text_bounds.left + (text_bounds.width / 2);
      text_position.x = texture_size.x / 2;
      break;

    case HorizAlign::Right:
      text_origin.x = text_bounds.left + text_bounds.width;
      text_position.x = texture_size.x;
      break;
    }

    switch (impl->text_alignment.vert)
    {
    case VertAlign::Top:
      text_origin.y = text_bounds.top;
      text_position.y = 0;
      break;

    case VertAlign::Center:
      text_origin.y = text_bounds.top + (text_bounds.height / 2);
      text_position.y = texture_size.y / 2;
      break;

    case VertAlign::Bottom:
      text_origin.y = text_bounds.top + text_bounds.height;
      text_position.y = texture_size.y;
      break;
    }

    text.setOrigin(text_origin);
    text.setPosition(text_position);

    target.draw(text);
  }
}

} // end namespace GUI
