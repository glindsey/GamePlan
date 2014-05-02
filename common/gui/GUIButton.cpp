#include "gui/GUIButton.h"

#include "App.h"
#include "ConfigSettings.h"
#include "GUIFont.h"

namespace GUI {

struct Button::Impl
{
  /// Text font.
  std::shared_ptr<Font> text_font;

  /// Button text.
  sf::String text_string;

  /// Callback function for when the button is clicked.
  std::function<void()> callback_clicked;

  /// Callback function for when the button is pressed or released.
  std::function<void(bool)> callback_pressed;

  /// Background shape.
  sf::RectangleShape bg_shape;

  /// True when the button is pressed down, false otherwise.
  bool pressed;
};

Button::Button(std::string name,
               sf::Vector2f dimensions,
               std::shared_ptr<Font> text_font) :
  Control(name, dimensions),
  impl(new Impl())
{
  impl->text_font = text_font;
}

Button::~Button()
{
  //dtor
}

void Button::set_text(sf::String str)
{
  impl->text_string = str;
}

sf::String Button::get_text()
{
  return impl->text_string;
}

void Button::set_callback_clicked(std::function<void()> callback)
{
  impl->callback_clicked = callback;
}

void Button::set_callback_pressed(std::function<void(bool)> callback)
{
  impl->callback_pressed = callback;
}

// === PROTECTED METHODS ======================================================

Font const& Button::get_text_font() const
{
  return *(impl->text_font.get());
}

EventResult Button::_handle_event(sf::Event& event)
{
  EventResult result = EventResult::Ignored;

  switch (event.type)
  {
    // TODO - Do generic control event processing here.
  case sf::Event::MouseMoved:
    // If the mouse is moved off of the control, it is no longer pressed.
    if (!is_mouse_inside())
    {
      if (impl->pressed == true)
      {
        impl->pressed = false;
        if (impl->callback_pressed)
        {
          impl->callback_pressed(false);
        }
      }
    }
    result = EventResult::Handled;
    break;

  case sf::Event::MouseButtonPressed:
    if (is_mouse_inside())
    {
      if (impl->pressed == false)
      {
        impl->pressed = true;
        if (impl->callback_pressed)
        {
          impl->callback_pressed(true);
        }
      }
    }
    break;

  case sf::Event::MouseButtonReleased:
    if (is_mouse_inside())
    {
      if (impl->pressed == true)
      {
        impl->pressed = false;
        if (impl->callback_pressed)
        {
          impl->callback_pressed(false);
          impl->callback_clicked();
        }
      }
    }
    break;

  default:
    break;
  }

  return result;
}

void Button::_render(sf::RenderTarget& target, int frame)
{
  // Render the background (if any).
  _render_background(target, frame);

  // IF the button has text...
  if (!impl->text_string.isEmpty())
  {
    // Render it.
    _render_text(target, frame);
  }
}

void Button::_render_background(sf::RenderTarget& target, int frame)
{
  auto const& dimensions = get_dimensions();

  sf::RectangleShape shape;

  // Draw the background.
  shape.setPosition({0, 0});
  shape.setSize(dimensions);
  shape.setFillColor(Settings.button_bg_color);
  target.draw(shape);

  // Draw the border lines.
  // Top side.
  shape.setPosition({Settings.button_border_width, 0});
  shape.setSize({dimensions.x - Settings.button_border_width,
                 Settings.button_border_width});
  shape.setFillColor(impl->pressed ? Settings.button_border_bl_color
                                   : Settings.button_border_tr_color);
  target.draw(shape);

  // Bottom side.
  shape.setPosition({0, dimensions.y - Settings.button_border_width});
  shape.setSize({dimensions.x - Settings.button_border_width,
                 Settings.button_border_width});
  shape.setFillColor(impl->pressed ? Settings.button_border_tr_color
                                   : Settings.button_border_bl_color);
  target.draw(shape);

  // Left side.
  shape.setPosition({0, Settings.button_border_width});
  shape.setSize({Settings.button_border_width,
                 dimensions.y - Settings.button_border_width});
  shape.setFillColor(impl->pressed ? Settings.button_border_tr_color
                                   : Settings.button_border_bl_color);
  target.draw(shape);

  // Right side.
  shape.setPosition({dimensions.x - Settings.button_border_width, 0});
  shape.setSize({Settings.button_border_width,
                 dimensions.y - Settings.button_border_width});
  shape.setFillColor(impl->pressed ? Settings.button_border_bl_color
                                   : Settings.button_border_tr_color);
  target.draw(shape);
}

void Button::_render_text(sf::RenderTarget& target, int frame)
{
  auto const& dimensions = get_dimensions();
  auto const& text_font = get_text_font();

  // Center the string on the button.
  sf::Text button_text;

  button_text.setString(get_text());
  button_text.setFont(text_font.get_bold_font());
  button_text.setCharacterSize(Settings.text_default_size);
  button_text.setColor(Settings.text_color);

  sf::FloatRect text_bounds = button_text.getGlobalBounds();
  button_text.setOrigin(text_bounds.left + (text_bounds.width / 2),
                        text_bounds.top + (text_bounds.height / 2));
  button_text.setPosition(dimensions.x / 2, dimensions.y / 2);
  target.draw(button_text);
}

} // end namespace GUI
