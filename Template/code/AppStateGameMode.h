#ifndef APPSTATEGAMEMODE_H
#define APPSTATEGAMEMODE_H

#include <memory>

#include "State.h"

class AppStateGameMode : public State
{
  public:
    AppStateGameMode(StateMachine* state_machine);
    virtual ~AppStateGameMode();

    virtual void execute() override;
    virtual void render(sf::RenderTarget& target, int frame) override;
    virtual EventResult handle_event(sf::Event& event) override;
    virtual std::string const& get_name() override;
    virtual bool initialize() override;
    virtual bool terminate() override;

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // APPSTATEGAMEMODE_H
