#ifndef GUISCROLLBAR_H
#define GUISCROLLBAR_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GUIEnums.h"
#include "GUISlider.h"

namespace GUI {

// Forward declarations
class Font;

class ScrollBar :
  public Slider
{
  public:
    ScrollBar(std::string name,
              sf::FloatRect dimensions,
              std::pair<long int> extents,
              double handle_size = 0.1,
              Orientation orientation = Orientation::Horizontal);
    virtual ~ScrollBar();

    /// Set the size of the scrollbar handle.
    /// @param handle_size  Size of the handle in relation to the total range
    ///                     the scrollbar covers, from 0.0 to 1.0. For example,
    ///                     if the handle represents 25 percent of the total
    ///                     scrollbar range, this parameter should be 0.25.
    void set_handle_size(double handle_size);

    /// Get the size of the scrollbar handle.
    /// @return The size of the handle in relation to the total range that the
    ///         scrollbar covers, from 0.0 to 1.0.
    double get_handle_size(void) const;

  protected:
    virtual EventResult _handle_event(sf::Event& event) override;

    virtual bool _render(sf::RenderTarget& target,
                         sf::FloatRect adjusted_dims,
                         int frame) override final;

    virtual bool _render_background(sf::RenderTarget& target,
                                    sf::FloatRect adjusted_dims,
                                    int frame);

    virtual bool _render_edge_buttons(sf::RenderTarget& target,
                                      sf::FloatRect adjusted_dims,
                                      int frame);

    virtual bool _render_handle(sf::RenderTarget& target,
                                sf::FloatRect adjusted_dims,
                                int frame);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUILABEL_H
