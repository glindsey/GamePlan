#ifndef APPSTATEGAMEMODE_H
#define APPSTATEGAMEMODE_H

#include <memory>

#include "State.h"

class AppStateGameMode : public State
{
  public:
    AppStateGameMode(StateMachine* state_machine);
    virtual ~AppStateGameMode();

    void execute() override;
    void render(sf::RenderTarget& target, int frame) override;
    EventResult handle_event(sf::Event& event) override;
    std::string const& get_name() override;
    bool initialize() override;
    bool terminate() override;

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // APPSTATEGAMEMODE_H
