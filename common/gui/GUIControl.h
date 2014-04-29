#ifndef GUICONTROL_H
#define GUICONTROL_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "EventHandler.h"
#include "Renderable.h"

// Forward declarations
class GUIAlign;

class GUIControl :
  public EventHandler,
  public Renderable
{
  public:
    GUIControl(std::string name,
               sf::Vector2f dimensions);
    virtual ~GUIControl();

    std::string get_name() const;

    void set_focus(bool focus);
    bool get_focus();

    sf::Vector2f get_position() const;
    void set_position(sf::Vector2f position);

    sf::Vector2f get_dimensions() const;
    void set_dimensions(sf::Vector2f dimensions);

    GUIAlign get_alignment() const;
    void set_alignment(GUIAlign alignment);

    bool is_mouse_inside();

    bool add_child(std::shared_ptr<GUIControl> new_child);
    void must_add_child(std::shared_ptr<GUIControl> new_child);

    bool remove_child(std::shared_ptr<GUIControl> new_child);
    void must_remove_child(std::shared_ptr<GUIControl> new_child);

    std::shared_ptr<GUIControl> get_child(std::string const& name) const;
    std::shared_ptr<GUIControl> must_get_child(std::string const& name) const;

    virtual void render(sf::RenderTarget& target, int frame) override final;

    virtual EventResult handle_event(sf::Event& event) override final;

  protected:
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
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // GUICONTROL_H
