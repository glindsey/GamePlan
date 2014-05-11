#ifndef GUIROOT_H
#define GUIROOT_H

#include <SFML/Graphics.hpp>

#include "GUIControl.h"

namespace GUI {

class Root : public Control
{
  public:
    Root(sf::RenderWindow const& window);
    virtual ~Root();
  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;
  private:
};

} // end namespace GUI

#endif // GUIROOT_H
