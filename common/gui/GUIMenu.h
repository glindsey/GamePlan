#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIEnums.h"
#include "GUIPane.h"

// Forward declarations
class MenuItem;

namespace GUI {

class Menu : public Pane
{
  public:
    Menu(std::string name,
         sf::Vector2f dimensions,
         std::shared_ptr<Font> title_font,
         std::shared_ptr<Font> menu_font,
         Orientation menu_orientation);
    virtual ~Menu();

    MenuItem& add_menu_item(std::string name);

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;

};

} // end namespace GUI

#endif // MENU_H
