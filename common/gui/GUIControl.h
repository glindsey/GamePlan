#ifndef GUICONTROL_H
#define GUICONTROL_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "IEventHandler.h"
#include "IRenderable.h"

namespace GUI {

// Forward declarations
class Align;
class IControlApparator;

class Control :
  public IEventHandler,
  public IRenderable
{
  public:
    Control(std::string name, sf::Vector2f const& dimensions);
    virtual ~Control();

    std::string get_name() const;

    void set_focus(bool focus);
    bool get_focus();

    sf::Vector2f get_position() const;
    void set_position(sf::Vector2f const& position);

    sf::Vector2f get_dimensions() const;
    void set_dimensions(sf::Vector2f const& dimensions);

    Align get_alignment() const;
    void set_alignment(Align alignment);

    bool is_visible() const;
    void set_visible(bool visible);

    std::shared_ptr<IControlApparator> get_apparator();
    void set_apparator(std::shared_ptr<IControlApparator> apparator);

    bool do_arrow_keys_control_focus() const;
    void set_arrow_keys_control_focus(bool enable);

    bool does_tab_control_focus() const;
    void set_tab_controls_focus(bool enable);

    bool is_mouse_inside() const;

    void clear_children();

    bool add_child(std::unique_ptr<Control> new_child);
    void must_add_child(std::unique_ptr<Control> new_child);

    std::unique_ptr<Control> remove_child(std::string const& name);
    std::unique_ptr<Control> must_remove_child(std::string const& name);

    Control* get_child(std::string const& name) const;
    Control& must_get_child(std::string const& name) const;

    virtual void render(sf::RenderTarget& target, int frame) override final;

    virtual EventResult handle_event(sf::Event& event) override final;

  protected:
    /// Set instantaneous visibility.
    /// @param visible False to hide the control, True to show it.
    void set_instant_visibility(bool visible);

    /// Given parent size, and child size, position and alignment, return
    /// adjusted absolute coordinates.
    sf::Vector2f get_anchored_position(sf::Vector2f const& child_position,
                                       sf::Vector2f const& child_size) const;

    /// Template method for updating the control's appearance.
    /// This is used by any subclass that wishes to cache the rendered
    /// appearance, rather than rendering from scratch every frame. It is
    /// called by set_position, set_dimensions, set_alignment -- basically,
    /// any time the contents of the control may be updated.
    ///
    /// The default implementation of this method does nothing.
    virtual void _update_appearance();

    /// Template method called when a control is resized.
    /// This is used by subclasses if they need new size information
    /// right away -- for example, to resize a separate texture.
    ///
    /// The default implementation of this method does nothing.
    virtual void _set_dimensions(sf::Vector2f const& dimensions);

    /// Return the vector of child controls.
    /// @note I probably shouldn't be exposing class internals this way,
    ///       and might get rid of this in the future if I can do without it.
    virtual std::vector<std::unique_ptr<Control>>& get_child_controls();

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
