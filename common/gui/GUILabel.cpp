#include "gui/GUILabel.h"

#include "App.h"
#include "ConfigSettings.h"
#include "GUIFont.h"

struct GUILabel::Impl
{
  /// Title.
  sf::String text_string;

  /// Title font.
  std::shared_ptr<GUIFont> text_font;

};

GUILabel::GUILabel(std::string name,
                 sf::Vector2f dimensions,
                 std::shared_ptr<GUIFont> text_font) :
  GUIControl(name, dimensions),
  impl(new Impl())
{
  impl->text_font = text_font;
}

GUILabel::~GUILabel()
{
  //dtor
}

void GUILabel::set_text(sf::String str)
{
  impl->text_string = str;
}

sf::String GUILabel::get_text() const
{
  return impl->text_string;
}

// === PROTECTED METHODS ======================================================

EventResult GUILabel::_handle_event(sf::Event& event)
{
  return EventResult::Ignored;
}

void GUILabel::_render(sf::RenderTarget& target, int frame)
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
