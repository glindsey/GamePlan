#include "AppStateGameMode.h"

#include "App.h"

struct AppStateGameMode::Impl
{
  char dummy;
};

AppStateGameMode::AppStateGameMode(StateMachine* state_machine)
  : State(state_machine), impl(new Impl())
{
}

AppStateGameMode::~AppStateGameMode()
{
}

void AppStateGameMode::execute()
{
}

void AppStateGameMode::render(sf::RenderTarget& target, int frame)
{
  /// At the moment, implementation does nothing.
}

EventResult AppStateGameMode::handle_event(sf::Event& event)
{
  switch (event.type)
  {
  case sf::Event::EventType::KeyPressed:
    switch (event.key.code)
    {
    default:
      break;
    }
    break;

  default:
    break;
  }

  return EventResult::Ignored;
}

std::string const& AppStateGameMode::get_name()
{
  static std::string name = std::string("AppStateGameMode");
  return name;
}

bool AppStateGameMode::initialize()
{
  return true;
}

bool AppStateGameMode::terminate()
{
  return true;
}
