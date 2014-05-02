#ifndef GUICONTROL_H
#define GUICONTROL_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "EventHandler.h"
#include "Renderable.h"

namespace GUI {

// Forward declarations
class Align;
class IControlApparator;

class Control :
  public EventHandler,
  public Renderable
{
  public:
    Control(std::string name,
               sf::Vector2f dimensions);
    virtual ~Control();

    std::string get_name() const;

    void set_focus(bool focus);
    bool get_focus();

    sf::Vector2f get_position() const;
    void set_position(sf::Vector2f position);

    sf::Vector2f get_dimensions() const;
    void set_dimensions(sf::Vector2f dimensions);

    Align get_alignment() const;
    void set_alignment(Align alignment);

    bool is_visible() const;
    void set_visible(bool visible);

    std::shared_ptr<IControlApparator> get_apparator();
    void set_apparator(std::shared_ptr<IControlApparator> apparator);

    bool is_mouse_inside() const;

    bool add_child(std::shared_ptr<Control> new_child);
    void must_add_child(std::shared_ptr<Control> new_child);

    bool remove_child(std::shared_ptr<Control> new_child);
    void must_remove_child(std::shared_ptr<Control> new_child);

    std::shared_ptr<Control> get_child(std::string const& name) const;
    std::shared_ptr<Control> must_get_child(std::string const& name) const;

    virtual void render(sf::RenderTarget& target, int frame) override final;

    virtual EventResult handle_event(sf::Event& event) override final;

  protected:
    /// Set instantaneous visibility.
    /// @param visibility False to hide the control, True to show it.
    void set_instant_visibility(bool visible);

    /// Given parent size, and child size, position and alignment, return
    /// adjusted absolute coordinates.
    sf::Vector2f get_anchored_position(sf::Vector2f child_position,
                                       sf::Vector2f child_size) const;

    /// Template method for rendering the control. Pure virtual in GUIControl.
    /// @param target Target to render to.
    /// @param frame Animation frame to render.
    virtual void _render(sf::RenderTarget& target,
                         int frame) = 0;

    /// Subclass method for handling events. Pure virtual in GUIControl.
    /// @param event Event to handle.
    /// @return Result of handling the event.
    virtual EventResult _handle_event(sf::Event& event) = 0;

  private:
    /// Set parent of control.
    void set_parent(Control* parent);

    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // end namespace GUI

#endif // GUICONTROL_H
