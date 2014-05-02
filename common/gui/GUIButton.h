#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "GUIControl.h"

namespace GUI {

// Forward declarations
class Font;

class Button :
  public Control
{
  public:
    Button(std::string name,
            sf::Vector2f dimensions,
            std::shared_ptr<Font> text_font);
    virtual ~Button();

    void set_text(sf::String str);
    sf::String get_text(void);

    /// Set the callback for when the button is clicked (pressed and released).
    void set_callback_clicked(std::function<void()> callback);

    /// Set the callback for when the button is pressed or released.
    /// The only parameter in the callback is a boolean that will be true
    /// if the button was pressed down, or false if the button was released.
    /// @param callback A callback function that takes a bool and returns void.
    void set_callback_pressed(std::function<void(bool)> callback);

  protected:
    Font const& get_text_font() const;

    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override;

    virtual void _render_background(sf::RenderTarget& target, int frame);

    virtual void _render_text(sf::RenderTarget& target, int frame);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUIBUTTON_H
