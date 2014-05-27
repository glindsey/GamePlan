#ifndef GUIPANE_H
#define GUIPANE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"

namespace GUI {

// Forward declarations
class Font;

class Pane :
  public Control
{
  public:
    Pane(std::string name,
         sf::Vector2f dimensions,
         std::shared_ptr<Font> title_font);
    virtual ~Pane();

    void set_title(sf::String str);
    sf::String get_title() const;

    void set_title_alignment(HorizAlign alignment);
    HorizAlign get_title_alignment() const;

    void set_title_font(std::shared_ptr<Font> title_font);
    std::shared_ptr<Font> get_title_font() const;

  protected:
    Font& get_title_font_ref();

    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override;
    virtual void _render_contents(sf::RenderTarget& target, int frame);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUIPANE_H
