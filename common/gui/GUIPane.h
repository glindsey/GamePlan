#ifndef GUIPANE_H
#define GUIPANE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"

// Forward declarations
class GUIFont;

class GUIPane :
  public GUIControl
{
  public:
    GUIPane(std::string name,
            sf::Vector2f dimensions,
            std::shared_ptr<GUIFont> title_font);
    virtual ~GUIPane();

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

#endif // GUIPANE_H
