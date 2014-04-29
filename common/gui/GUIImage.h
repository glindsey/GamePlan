#ifndef GUIIMAGE_H
#define GUIIMAGE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"

// Forward declarations
class GUIFont;

class GUIImage :
  public GUIControl
{
  public:
    GUIImage(std::string name,
             sf::FloatRect dimensions);
    virtual ~GUIImage();

    void set_image(sf::Image image);
    sf::Image get_image(void) const;

    void set_scaling_type(GUIScalingType scaling_type);
    GUIScalingType get_scaling_type() const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual bool _render(sf::RenderTarget& target,
                         sf::FloatRect adjusted_dims,
                         int frame) override final;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // GUIIMAGE_H
