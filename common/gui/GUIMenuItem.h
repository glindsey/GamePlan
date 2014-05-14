#ifndef MENUITEM_H
#define MENUITEM_H

#include "GUIButton.h"

namespace GUI {

class MenuItem : public Button
{
  public:
    MenuItem(std::string name,
             sf::Vector2f dimensions,
             std::shared_ptr<Font> menu_font);
    virtual ~MenuItem();

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // MENUITEM_H
