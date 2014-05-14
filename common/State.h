#ifndef STATE_H
#define STATE_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

#include "IEventHandler.h"
#include "IRenderable.h"

// Forward declarations
class StateMachine;

class State : public IEventHandler,
              public IRenderable,
              public boost::noncopyable
{
  public:
    State(StateMachine* state_machine);
    virtual ~State();

    // Get the name of this state.
    virtual std::string const& get_name() = 0;

    // Initialize the state upon entering it.
    virtual bool initialize() = 0;

    // Execute while in the state.
    virtual void execute() = 0;

    // Terminate the state upon leaving it.
    virtual bool terminate() = 0;

    // Tell state machine to change to a new state.
    bool change_to(std::string const& new_state);

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // STATE_H
