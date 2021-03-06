#ifndef GUILABEL_H
#define GUILABEL_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"

namespace GUI {

// Forward declarations
class Font;

/// Class representing a text label.
class Label :
  public Control
{
  public:
    Label(std::string name,
          sf::Vector2f dimensions,
          std::shared_ptr<Font> title_font);
    virtual ~Label();

    void set_text(sf::String str);
    sf::String get_text() const;

    void set_text_size(unsigned int text_size);
    unsigned int get_text_size() const;

    void set_text_alignment(Align alignment);
    Align get_text_alignment() const;

    void set_cursor_visible(bool visible);
    bool is_cursor_visible();

    unsigned long get_cursor_location();
    void set_cursor_location(unsigned long location);

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _set_dimensions(sf::Vector2f const& dimensions) override;

    virtual void _update_appearance() override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;

    void draw_text(sf::RenderTarget& target,
                   sf::Text& text,
                   int position_y);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUILABEL_H
