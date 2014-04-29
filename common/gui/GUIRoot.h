#ifndef GUIROOT_H
#define GUIROOT_H

#include "GUIControl.h"


class GUIRoot : public GUIControl
{
  public:
    GUIRoot(std::string name,
            sf::Vector2f dimensions);
    virtual ~GUIRoot();
  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;
  private:
};

#endif // GUIROOT_H
