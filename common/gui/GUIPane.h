#ifndef GUIPANE_H
#define GUIPANE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"

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
    sf::String get_title(void) const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;
    virtual void _render_contents(sf::RenderTarget& target, int frame);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUIPANE_H
