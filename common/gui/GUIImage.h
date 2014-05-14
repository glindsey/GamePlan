#ifndef GUIIMAGE_H
#define GUIIMAGE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"

namespace GUI {

// Forward declarations
class Font;

/// Class representing a simple image displayed on the screen.
class Image :
  public Control
{
  public:
    Image(std::string name,
          sf::FloatRect dimensions);
    virtual ~Image();

    void set_image(sf::Image image);
    sf::Image get_image(void) const;

    void set_scaling_type(ScalingType scaling_type);
    ScalingType get_scaling_type() const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual void _render(sf::RenderTarget& target,
                         sf::FloatRect adjusted_dims,
                         int frame) override final;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUIIMAGE_H
