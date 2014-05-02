#ifndef GUIROOT_H
#define GUIROOT_H

#include "GUIControl.h"

namespace GUI {

class Root : public Control
{
  public:
    Root(std::string name,
         sf::Vector2f dimensions);
    virtual ~Root();
  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;
  private:
};

} // end namespace GUI

#endif // GUIROOT_H
