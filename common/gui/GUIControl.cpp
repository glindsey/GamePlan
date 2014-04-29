#include "GUIControl.h"

#include "ErrorMacros.h"
#include "GUIEnums.h"

#include "boost/format.hpp"

struct GUIControl::Impl
{
  /// Control dimensions.
  sf::Vector2f dimensions;

  /// Control position (relative to parent).
  sf::Vector2f position;

  /// Control alignment (to parent).
  GUIAlign alignment;

  /// Control name.
  std::string name;

  /// Boolean indicating whether this area has the focus.
  bool focus;

  /// Boolean indicating whether the cursor is within this area.
  bool captured;

  /// Control texture.
  std::unique_ptr<sf::RenderTexture> control_texture;

  /// Collection of child controls.
  std::vector<std::shared_ptr<GUIControl>> children;
};

GUIControl::GUIControl(std::string name,
                       sf::Vector2f dimensions)
  : impl(new Impl())
{
  impl->name = name;
  set_dimensions(dimensions);
  set_position({0, 0});
  set_alignment({GUIHorizAlign::Left, GUIVertAlign::Center});
}

GUIControl::~GUIControl()
{
  //dtor
}

std::string GUIControl::get_name() const
{
  return impl->name;
}

void GUIControl::set_focus(bool focus)
{
  impl->focus = focus;
}

bool GUIControl::get_focus()
{
  return impl->focus;
}

sf::Vector2f GUIControl::get_position() const
{
  return impl->position;
}

void GUIControl::set_position(sf::Vector2f position)
{
  impl->position = position;
}

sf::Vector2f GUIControl::get_dimensions() const
{
  return impl->dimensions;
}

void GUIControl::set_dimensions(sf::Vector2f dimensions)
{
  impl->dimensions = dimensions;
  impl->control_texture.reset(new sf::RenderTexture());
  impl->control_texture->create(dimensions.x, dimensions.y);
}

GUIAlign GUIControl::get_alignment() const
{
  return impl->alignment;
}

void GUIControl::set_alignment(GUIAlign alignment)
{
  impl->alignment = alignment;
}

bool GUIControl::is_mouse_inside()
{
  return impl->captured;
}

bool GUIControl::add_child(std::shared_ptr<GUIControl> new_child)
{
  ASSERT_CONDITION(new_child);

  for (auto child : impl->children)
  {
    if (child.get() == new_child.get())
    {
      return false;
    }
  }

  impl->children.push_back(new_child);
  return true;
}

void GUIControl::must_add_child(std::shared_ptr<GUIControl> new_child)
{
  if (!add_child(new_child))
  {
    FATAL_ERROR(boost::format("Child \"%1%\" already exists in control \"%2%\"")
                % new_child->get_name() % get_name());
  }
}

bool GUIControl::remove_child(std::shared_ptr<GUIControl> old_child)
{
  ASSERT_CONDITION(old_child);

  for (auto iter = std::begin(impl->children);
       iter != std::end(impl->children);
       ++iter)
  {
    if (iter->get() == old_child.get())
    {
      impl->children.erase(iter);
      return true;
    }
  }
  return false;
}

void GUIControl::must_remove_child(std::shared_ptr<GUIControl> old_child)
{
  if (!remove_child(old_child))
  {
    FATAL_ERROR(boost::format("Could not remove child \"%1%\" from control \"%2%\"")
                % old_child->get_name() % get_name());
  }
}

std::shared_ptr<GUIControl> GUIControl::get_child(std::string const& name) const
{
  for (auto child : impl->children)
  {
    if (child->get_name() == name)
    {
      return child;
    }
  }
  return std::shared_ptr<GUIControl>();
}

std::shared_ptr<GUIControl> GUIControl::must_get_child(std::string const& name) const
{
  auto found_child = get_child(name);

  if (!found_child)
  {
    FATAL_ERROR(boost::format("Could not find child \"%1%\" in control \"%2%\"")
                              % name % get_name());
  }

  return found_child;
}

void GUIControl::render(sf::RenderTarget& target, int frame)
{
  auto& control_texture = *(impl->control_texture.get());
  auto const& dimensions = get_dimensions();

  // Call the template method to render onto the control texture.
  _render(control_texture, frame);

  // Render each child onto the control texture.
  for (auto child : impl->children)
  {
    child->render(control_texture, frame);
  }

  control_texture.display();

  // Render the control texture onto the target.
  sf::RectangleShape control_shape;
  control_shape.setSize(dimensions);
  control_shape.setTexture(&(control_texture.getTexture()), true);


  /// TODO - Adjusted dims need to take alignment into account.
  control_shape.setPosition(impl->position.x,
                            impl->position.y);
  target.draw(control_shape);
}

EventResult GUIControl::handle_event(sf::Event& event)
{
  EventResult result = EventResult::Ignored;
  sf::Event event_copy = event;

  switch (event.type)
  {
    // TODO - Do generic control event processing here.
  case sf::Event::MouseMoved:
    {
      result = EventResult::Handled;
      if ((event.mouseMove.x >= impl->position.x) &&
          (event.mouseMove.x < (impl->position.x + impl->dimensions.x)) &&
          (event.mouseMove.y >= impl->position.y) &&
          (event.mouseMove.y < (impl->position.y + impl->dimensions.y)))
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

      /// TODO: Coordinate adjustment must take alignment into account.
      event_copy.mouseMove.x = event.mouseMove.x - impl->position.x;
      event_copy.mouseMove.y = event.mouseMove.y - impl->position.y;
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
  for (auto child : impl->children)
  {
    child->handle_event(event_copy);
  }

  return result;
}

// === PROTECTED METHODS ======================================================
