#include "GUIRoot.h"

namespace GUI {

Root::Root(sf::RenderWindow const& window)
  : Control("root", { static_cast<float>(window.getSize().x),
                      static_cast<float>(window.getSize().y) })
{
  //ctor
}

Root::~Root()
{
  //dtor
}

// === PROTECTED METHODS ======================================================

EventResult Root::_handle_event(sf::Event& event)
{

  EventResult result = EventResult::Ignored;

  switch (event.type)
  {
  case sf::Event::EventType::Resized:
    {
      this->set_dimensions({ static_cast<float>(event.size.width),
                             static_cast<float>(event.size.height) });
      break;
    }

  default:
    break;
  }

  return result;
}

void Root::_render(sf::RenderTarget& target, int frame)
{
  /// @todo Get rid of magic constant.
  target.clear(sf::Color(16, 16, 32, 255));
}

} // end namespace GUI
