#include "GUIControl.h"

#include "ErrorMacros.h"
#include "GUIEnums.h"
#include "apparators/IControlApparator.h"

#include <boost/format.hpp>

namespace GUI {

struct Control::Impl
{
  /// Raw pointer to parent control.
  /// If control does not have a parent, pointer is null.
  Control* parent;

  /// Control name.
  std::string name;

  /// Control dimensions.
  sf::Vector2f dimensions;

  /// Control position (relative to parent).
  sf::Vector2f position;

  /// Control alignment (to parent).
  Align alignment;

  /// Current visibility state of this control and its children.
  VisibilityState appear_state;

  /// Visibility amount, from 0 to 1.
  float appear_amount;

  /// How fast this control appears: 0 = never (don't do this!), 1 = instantaneous.
  float appear_speed;

  /// Shared pointer to IControlApparator defining how the control should
  /// appear/disappear.
  std::shared_ptr<IControlApparator> apparator;

  /// Boolean indicating whether this control has the focus.
  bool focus;

  /// Boolean indicating whether the mouse cursor is within this area.
  bool captured;

  /// If true, keyboard focus is changed via arrow keys.
  bool arrow_keys_control_focus;

  /// If true, keyboard focus is changed via tab.
  bool tab_controls_focus;

  /// Control texture.
  std::unique_ptr<sf::RenderTexture> control_texture;

  /// Collection of child controls.
  std::vector<std::unique_ptr<Control>> children;

  /// Iterator pointing to child control with focus.
  std::vector<std::unique_ptr<Control>>::iterator focused_child;

};

Control::Control(std::string name,
                 sf::Vector2f const& dimensions)
  : impl(new Impl())
{
  impl->parent = nullptr;
  impl->name = name;
  set_dimensions(dimensions);
  set_position({0, 0});
  set_alignment({HorizAlign::Left, VertAlign::Top});
  impl->appear_state = VisibilityState::Visible;
  impl->appear_amount = 1.0f;
  impl->appear_speed = 0.05f;
  impl->control_texture->setSmooth(true); // good idea?
  impl->focused_child = std::begin(impl->children);
}

Control::~Control()
{
  //dtor
}

std::string Control::get_name() const
{
  return impl->name;
}

void Control::set_focus(bool focus)
{
  impl->focus = focus;
  _update_appearance();
}

bool Control::get_focus()
{
  return impl->focus;
}

sf::Vector2f Control::get_position() const
{
  return impl->position;
}

void Control::set_position(sf::Vector2f const& position)
{
  impl->position = position;
  _update_appearance();
}

sf::Vector2f Control::get_dimensions() const
{
  return impl->dimensions;
}

void Control::set_dimensions(sf::Vector2f const& dimensions)
{
  impl->dimensions = dimensions;
  impl->control_texture.reset(new sf::RenderTexture());
  impl->control_texture->create(dimensions.x, dimensions.y);

  _set_dimensions(dimensions);
  _update_appearance();
}

Align Control::get_alignment() const
{
  return impl->alignment;
}

void Control::set_alignment(Align alignment)
{
  impl->alignment = alignment;
  _update_appearance();
}

bool Control::is_visible() const
{
  return (impl->appear_state != VisibilityState::Hidden);
}

void Control::set_visible(bool visible)
{
  if (visible == true)
  {
    if ((impl->appear_state == VisibilityState::Hidden) ||
        (impl->appear_state == VisibilityState::Disappearing))
    {
      impl->appear_state = VisibilityState::Appearing;
    }
  }
  else // (visible == false)
  {
    if ((impl->appear_state == VisibilityState::Visible) ||
        (impl->appear_state == VisibilityState::Appearing))
    {
      impl->appear_state = VisibilityState::Disappearing;
    }
  }
  _update_appearance();
}

std::shared_ptr<IControlApparator> Control::get_apparator()
{
  return impl->apparator;
}

void Control::set_apparator(std::shared_ptr<IControlApparator> apparator)
{
  impl->apparator = apparator;
}

bool Control::do_arrow_keys_control_focus() const
{
  return impl->arrow_keys_control_focus;
}

void Control::set_arrow_keys_control_focus(bool enable)
{
  impl->arrow_keys_control_focus = enable;
}

bool Control::does_tab_control_focus() const
{
  return impl->tab_controls_focus;
}

void Control::set_tab_controls_focus(bool enable)
{
  impl->tab_controls_focus = enable;
}

bool Control::is_mouse_inside() const
{
  return impl->captured;
}

void Control::clear_children()
{
  impl->children.clear();
}

bool Control::add_child(std::unique_ptr<Control> new_child)
{
  ASSERT_CONDITION(new_child);

  for (auto& child : impl->children)
  {
    if (child.get() == new_child.get())
    {
      return false;
    }
  }

  new_child->set_parent(this);
  impl->children.push_back(std::move(new_child));

  // Set focus to the first control.
  impl->focused_child = std::begin(impl->children);

  return true;
}

void Control::must_add_child(std::unique_ptr<Control> new_child)
{
  if (!add_child(std::move(new_child)))
  {
    FATAL_ERROR(boost::format("Child \"%1%\" already exists in control \"%2%\"")
                % new_child->get_name() % get_name());
  }
}

std::unique_ptr<Control> Control::remove_child(std::string const& name)
{
  /// @todo Fix focused control iterator if it was on the current child.

  for (auto iter = std::begin(impl->children);
       iter != std::end(impl->children);
       ++iter)
  {
    if ((*iter)->get_name() == name)
    {
      auto child = std::move(*iter);
      impl->children.erase(iter);
      return child;
    }
  }
  return std::unique_ptr<Control>();
}

std::unique_ptr<Control> Control::must_remove_child(std::string const& name)
{
  auto child = std::move(remove_child(name));

  if (!child)
  {
    FATAL_ERROR(boost::format("Could not remove child \"%1%\" from control \"%2%\"")
              % name % get_name());
  }

  return child;
}

Control* Control::get_child(std::string const& name) const
{
  for (auto& child : impl->children)
  {
    if (child->get_name() == name)
    {
      return child.get();
    }
  }
  return nullptr;
}

Control& Control::must_get_child(std::string const& name) const
{
  auto child_ptr = get_child(name);

  if (child_ptr == nullptr)
  {
    FATAL_ERROR(boost::format("Could not find child \"%1%\" in control \"%2%\"")
                              % name % get_name());
  }

  return *(child_ptr);
}

void Control::render(sf::RenderTarget& target, int frame)
{
  auto& control_texture = *(impl->control_texture.get());

  switch (impl->appear_state)
  {
  case VisibilityState::Hidden:
    // If control is not visible, obviously it is not rendered.
    return;

  case VisibilityState::Appearing:
    impl->appear_amount += impl->appear_speed;

    if (impl->appear_amount >= 1.0f)
    {
      impl->appear_amount = 1.0f;
      impl->appear_state = VisibilityState::Visible;
    }
    break;

  case VisibilityState::Disappearing:
    impl->appear_amount -= impl->appear_speed;
    if (impl->appear_amount <= 0.0f)
    {
      impl->appear_amount = 0.0f;
      impl->appear_state = VisibilityState::Hidden;
    }
    break;

  default:
    break;
  }

  // Call the template method to render onto the control texture.
  _render(control_texture, frame);

  // Render each child onto the control texture.
  for (auto& child : impl->children)
  {
    child->render(control_texture, frame);
  }

  control_texture.display();

  // Render the control texture onto the target.
  sf::RectangleShape control_shape;

  control_shape.setSize(impl->dimensions);
  control_shape.setPosition(impl->position);

  if (impl->apparator)
  {
    impl->apparator->alter_texture(control_texture,
                                   impl->appear_state,
                                   impl->appear_amount);

    impl->apparator->alter_shape(control_shape,
                                 impl->appear_state,
                                 impl->appear_amount);
  }

  control_shape.setTexture(&(control_texture.getTexture()), true);

  /// Adjust position based on control alignment.
  sf::Vector2f child_position = control_shape.getPosition();
  sf::Vector2f child_dimensions = control_shape.getSize();
  sf::Vector2f adjusted_position = get_anchored_position(child_position,
                                                         child_dimensions);
  control_shape.setPosition(adjusted_position);
  target.draw(control_shape);
}

EventResult Control::handle_event(sf::Event& event)
{
  EventResult result = EventResult::Ignored;
  sf::Event event_copy = event;

  /// Take alignment into account.
  sf::Vector2f adjusted_position = get_anchored_position(impl->position,
                                                         impl->dimensions);

  // If control is FULLY visible, it cannot process events.
  if (impl->appear_state != VisibilityState::Visible)
  {
    return EventResult::Ignored;
  }

  switch (event.type)
  {

  case sf::Event::KeyPressed:
    if (do_arrow_keys_control_focus() &&
        (impl->children.size() != 0))
    {
      switch (event.key.code)
      {
      case sf::Keyboard::Up:
      case sf::Keyboard::Num8:

      case sf::Keyboard::Left:
      case sf::Keyboard::Num4:

      case sf::Keyboard::Right:
      case sf::Keyboard::Num6:

      case sf::Keyboard::Down:
      case sf::Keyboard::Num2:
        TRACE("Arrow keys not implemented yet!");
        break;

      default:
        break;
      }
    }

    /// @todo Deal with non-focusable controls.
    if (does_tab_control_focus() &&
        (impl->children.size() != 0))
    {
      if (event.key.code == sf::Keyboard::Tab)
      {
        if (event.key.shift == false)
        {
          (*(impl->focused_child))->set_focus(false);
          ++(impl->focused_child);
          if (impl->focused_child == std::end(impl->children))
          {
            impl->focused_child = std::begin(impl->children);
          }
          (*(impl->focused_child))->set_focus(true);
          TRACE(boost::format("New focus is \"%1%\"") % (*(impl->focused_child))->get_name());
          result = EventResult::Handled;
        }
        else
        {
          (*(impl->focused_child))->set_focus(false);
          if (impl->focused_child == std::begin(impl->children))
          {
            impl->focused_child = std::end(impl->children);
          }
          --(impl->focused_child);
          (*(impl->focused_child))->set_focus(true);
          TRACE(boost::format("New focus is \"%1%\"") % (*(impl->focused_child))->get_name());
          result = EventResult::Handled;
        }
      }
    }
    break;

    // TODO - Do generic control event processing here.
  case sf::Event::MouseMoved:
    {
      result = EventResult::Handled;
      if ((event.mouseMove.x >= adjusted_position.x) &&
          (event.mouseMove.x < (adjusted_position.x + impl->dimensions.x)) &&
          (event.mouseMove.y >= adjusted_position.y) &&
          (event.mouseMove.y < (adjusted_position.y + impl->dimensions.y)))
      {
        if (impl->captured == false)
        {
          TRACE(boost::format("Mouse entered Control %1%") % get_name());
          // Change to "Acknowledged" to pass to subclass handler.
          result = EventResult::Acknowledged;
        }
        impl->captured = true;
      }
      else
      {
        if (impl->captured == true)
        {
          TRACE(boost::format("Mouse left Control %1%") % get_name());
          // Change to "Acknowledged" to pass to subclass handler.
          result = EventResult::Acknowledged;
        }
        impl->captured = false;
      }

      // Subtract adjusted position so sub-event is relative to parent.
      event_copy.mouseMove.x = event.mouseMove.x - adjusted_position.x;
      event_copy.mouseMove.y = event.mouseMove.y - adjusted_position.y;
    }
    break;

  default:
    result = EventResult::Ignored;
    break;
  }

  // If the generic handler doesn't handle it, pass down to subclass.
  if (result != EventResult::Handled)
  {
    result = _handle_event(event);
  }

  // Pass the event down to subclasses.
  for (auto& child : impl->children)
  {
    child->handle_event(event_copy);
  }

  return result;
}

// === PROTECTED METHODS ======================================================
void Control::set_instant_visibility(bool visible)
{
  if (visible == false)
  {
    impl->appear_amount = 0.0f;
    impl->appear_state = VisibilityState::Hidden;
  }
  else
  {
    impl->appear_amount = 1.0f;
    impl->appear_state = VisibilityState::Visible;
  }
}

sf::Vector2f Control::get_anchored_position(sf::Vector2f const& child_position,
                                            sf::Vector2f const& child_size) const
{
  if (impl->parent == nullptr)
  {
    return (child_position);
  }

  sf::Vector2f parent_size = impl->parent->get_dimensions();

  sf::Vector2f adjusted_position;

  switch (impl->alignment.horiz)
  {
  case HorizAlign::Left:
  default:
    adjusted_position.x = child_position.x;
    break;
  case HorizAlign::Center:
    adjusted_position.x = ((parent_size.x - child_size.x) / 2) + child_position.x;
    break;
  case HorizAlign::Right:
    adjusted_position.x = (parent_size.x - child_size.x) + child_position.x;
  break;
  }

  switch (impl->alignment.vert)
  {
  case VertAlign::Top:
  default:
    adjusted_position.y = child_position.y;
    break;
  case VertAlign::Center:
    adjusted_position.y = ((parent_size.y - child_size.y) / 2) + child_position.y;
    break;
  case VertAlign::Bottom:
    adjusted_position.y = (parent_size.y - child_size.y) + child_position.y;
  break;
  }

  return adjusted_position;
}

void Control::_update_appearance()
{
  /* The default implementation of this method does nothing. */
}

void Control::_set_dimensions(sf::Vector2f const& dimensions)
{
  /* The default implementation of this method does nothing. */
}

std::vector<std::unique_ptr<Control>>& Control::get_child_controls()
{
  return impl->children;
}


// === PRIVATE METHODS ========================================================
void Control::set_parent(Control* parent)
{
  impl->parent = parent;
}

} // end namespace GUI
