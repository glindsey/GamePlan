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

  /// Texture to cache rendered appearance.
  std::unique_ptr<sf::RenderTexture> cached_texture;

  /// Shape used to draw texture onto.
  std::unique_ptr<sf::RectangleShape> cached_shape;
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
  _set_dimensions(dimensions);
}

Label::~Label()
{
  //dtor
}

void Label::set_text(sf::String str)
{
  impl->text_string = str;
  _update_appearance();
}

sf::String Label::get_text() const
{
  return impl->text_string;
}

void Label::set_text_size(unsigned int text_size)
{
  impl->text_size = text_size;
  _update_appearance();
}

unsigned int Label::get_text_size() const
{
  return impl->text_size;
}

void Label::set_text_alignment(Align alignment)
{
  impl->text_alignment = alignment;
  _update_appearance();
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

void Label::_set_dimensions(sf::Vector2f const& dimensions)
{
  impl->cached_texture.reset(new sf::RenderTexture());
  impl->cached_texture->create(dimensions.x, dimensions.y);
  impl->cached_shape.reset(new sf::RectangleShape());
  impl->cached_shape->setFillColor(sf::Color::Red);
  impl->cached_shape->setSize(dimensions);
  impl->cached_shape->setTexture(&(impl->cached_texture->getTexture()), true);
}

void Label::_update_appearance()
{
  sf::RenderTexture& target = *(impl->cached_texture.get());
  sf::Vector2u dimensions = target.getSize();
  target.clear(sf::Color::Transparent);

  int line_spacing_y = impl->text_font->get_normal_font().getLineSpacing(impl->text_size);

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
                           sf::Color::White :
                           sf::Color::Transparent);
      rect.setOutlineThickness(1);
      rect.setPosition(sf::Vector2f(1, 1));
      rect.setSize(sf::Vector2f(dimensions.x - 2, dimensions.y - 2));

      target.draw(rect);
    }

    int line_number = 0;
    int lines_that_fit = dimensions.y / line_spacing_y;

    sf::String& text = impl->text_string;
    int end_of_string = text.getSize();
    int current_character = 0;
    bool this_char_is_whitespace = false;
    bool last_char_was_whitespace = false;
    int start_of_line = 0;

    int start_of_this_word = 0;
    int end_of_last_word = 0;

    sf::String current_line;
    sf::String testing_line;
    sf::Text rendered_line;
    rendered_line.setFont(impl->text_font->get_normal_font());
    rendered_line.setCharacterSize(impl->text_size);
    rendered_line.setColor(sf::Color::White);

    while ((current_character != end_of_string) &&
           (line_number < lines_that_fit))
    {
      // Remember current character if it is WS or non-WS.
      last_char_was_whitespace = this_char_is_whitespace;
      this_char_is_whitespace = isspace(text[current_character]);

      if (!this_char_is_whitespace && last_char_was_whitespace)
      {
        start_of_this_word = current_character;
      }
      else if (this_char_is_whitespace && !last_char_was_whitespace)
      {
        end_of_last_word = current_character - 1;
      }

      // If at end of string, this char is end of last word.
      if (current_character == end_of_string - 1)
      {
        end_of_last_word = current_character;
      }

      // Add this character to the testing line.
      testing_line += text[current_character];

      // Try rendering the testing line.
      rendered_line.setString(testing_line);

      // If the render does NOT fit, or we've hit the end of the string:
      if ((rendered_line.getLocalBounds().width > dimensions.x) ||
          (current_character == end_of_string - 1))
      {
        // Handle instance where last word was longer than target width.
        // In that case, start_of_this_word will equal start_of_line.
        if (start_of_this_word != start_of_line)
        {
          // Back up to the end of the last word.
          current_character = end_of_last_word + 1;
        }

        // Copy from start of this line to end of last word into current_line.
        current_line.clear();
        for (int index = start_of_line; index < current_character; ++index)
        {
          current_line += text[index];
        }

        // Render it.
        rendered_line.setString(current_line);
        draw_text(target, rendered_line, line_number * line_spacing_y);

        // Get ready for the next line: increment past whitespace.
        while ((isspace(text[current_character])) &&
               (current_character != end_of_string))
        {
          ++current_character;
        }

        // Clear out testing and current line.
        testing_line.clear();

        // Set start of new line to current character and increment line number.
        start_of_line = current_character;
        ++line_number;
      } // end if
      else
      {
        // Still fits, so just increment current character.
        ++current_character;
      }
    } // end while
  } // end if

  target.display();
}

/// @todo Move rendering code into _update_appearance so it isn't horribly slow.
void Label::_render(sf::RenderTarget& target, int frame)
{
  target.draw(*(impl->cached_shape.get()), sf::BlendNone);
}

void Label::draw_text(sf::RenderTarget& target,
                      sf::Text& text,
                      int position_y)
{
    sf::FloatRect text_bounds = text.getGlobalBounds();

    sf::Vector2f text_origin;
    sf::Vector2f text_position;
    sf::Vector2u texture_size = target.getSize();

    switch (impl->text_alignment.horiz)
    {
    case HorizAlign::Left:
      text_origin.x = 0;
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

    text_origin.y = 0;
    text_position.y = position_y;

    /// @todo Re-enable vertical text alignment.
    /*
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
    */

    text.setOrigin(text_origin);
    text.setPosition(text_position);

    target.draw(text);
}

} // end namespace GUI
