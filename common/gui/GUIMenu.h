#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"
#include "GUIFont.h"

// Forward declarations
class MenuItem;

namespace GUI {

class Menu : public Control
{
  public:
    Menu(std::string name,
         sf::Vector2f dimensions,
         std::shared_ptr<Font> menu_font,
         Orientation menu_orientation);
    virtual ~Menu();

    MenuItem& add_menu_item(std::string name,
                            std::function<void()> item_callback);

    void set_font(std::shared_ptr<Font> const& menu_font);
    std::shared_ptr<Font> get_font() const;

    void set_orientation(Orientation orientation);
    Orientation get_orientation() const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;

};

} // end namespace GUI

#endif // MENU_H
