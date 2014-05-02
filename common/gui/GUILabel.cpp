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

};

Label::Label(std::string name,
             sf::Vector2f dimensions,
             std::shared_ptr<Font> text_font) :
  Control(name, dimensions),
  impl(new Impl())
{
  impl->text_font = text_font;
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

// === PROTECTED METHODS ======================================================

EventResult Label::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void Label::_render(sf::RenderTarget& target, int frame)
{
  //int line_spacing_y = impl->text_font->get_normal_font().getLineSpacing(Settings.text_title_size);

  // IF there is some text...
  if (!(impl->text_string.isEmpty()))
  {
    // Draw the title in the upper-left corner.
    sf::Text text;

    text.setString(impl->text_string);
    text.setFont(impl->text_font->get_normal_font());
    text.setCharacterSize(Settings.text_title_size);

    text.setColor(Settings.text_color);
    text.setPosition({0, 0});

    target.draw(text);
  }
}

} // end namespace GUI
