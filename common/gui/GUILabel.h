#ifndef GUILABEL_H
#define GUILABEL_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"

namespace GUI {

// Forward declarations
class Font;

class Label :
  public Control
{
  public:
    Label(std::string name,
          sf::Vector2f dimensions,
          std::shared_ptr<Font> title_font);
    virtual ~Label();

    void set_text(sf::String str);
    sf::String get_text(void) const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUILABEL_H
