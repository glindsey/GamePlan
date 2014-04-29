#include "State.h"

#include "ErrorMacros.h"
#include "StateMachine.h"

#include <boost/format.hpp>

struct State::Impl
{
  // State machine that this state belongs to.
  StateMachine* state_machine;
};

State::State(StateMachine* state_machine)
  : impl(new Impl())
{
  impl->state_machine = state_machine;
}

State::~State()
{
  //dtor
}

bool State::change_to(std::string const& new_state)
{
  // Ask the state machine to change to the requested state.
  if (impl->state_machine->change_to(new_state))
  {
    return true;
  }
  else
  {
    MAJOR_ERROR(boost::format("State manager \"%s\" could not change to new state \"%s\"")
                % impl->state_machine->get_name()
                % this->get_name());
    return false;
  }
}
