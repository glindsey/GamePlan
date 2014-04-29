#ifndef GUISLIDER_H
#define GUISLIDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIControl.h"
#include "GUIEnums.h"

// Forward declarations
class GUIFont;

class GUISlider :
  public GUIControl
{
  public:
    GUISlider(std::string name,
              sf::FloatRect dimensions,
              std::pair<long int> extents,
              GUIOrientation orientation = GUIOrientation::Horizontal);
    virtual ~GUISlider();

    GUIOrientation get_orientation(void) const;

    /// Set both the minimum and maximum values of the slider.
    /// @param extents A pair containing the minimum and maximum values.
    /// @note If extents.first > extents.second, the values will be swapped.
    void set_extents(std::pair<long int> extents);

    /// Get both the minimum and maximum values of the slider.
    /// @return A pair in the form (min_value, max_value).
    std:pair<long int> get_extents(void) const;

    void set_min_value(long int min_value);
    long int get_min_value(void) const;

    void set_value(long int value);
    long int get_value(void) const;

    void set_max_value(long int max_value);
    long int get_max_value(void) const;

    /// Set the callback for when the slider value is changed.
    /// @param callback A callback function that takes a long int and returns
    ///                 void.
    void set_callback_changed(std::function<void(long int)> callback);

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual bool _render(sf::RenderTarget& target,
                         sf::FloatRect adjusted_dims,
                         int frame) override;

    virtual bool _render_background(sf::RenderTarget& target,
                                    sf::FloatRect adjusted_dims,
                                    int frame);

    virtual bool _render_slider(sf::RenderTarget& target,
                                sf::FloatRect adjusted_dims,
                                int frame);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // GUILABEL_H
