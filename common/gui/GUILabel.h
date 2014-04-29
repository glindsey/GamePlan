#ifndef GUILABEL_H
#define GUILABEL_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"

// Forward declarations
class GUIFont;

class GUILabel :
  public GUIControl
{
  public:
    GUILabel(std::string name,
             sf::Vector2f dimensions,
             std::shared_ptr<GUIFont> title_font);
    virtual ~GUILabel();

    void set_text(sf::String str);
    sf::String get_text(void) const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target, int frame) override final;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // GUILABEL_H
