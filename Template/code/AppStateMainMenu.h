#ifndef APPSTATEMAINMENU_H
#define APPSTATEMAINMENU_H

#include <memory>

#include "State.h"


class AppStateMainMenu : public State
{
  public:
    AppStateMainMenu(StateMachine* state_machine);
    virtual ~AppStateMainMenu();

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

#endif // APPSTATEMAINMENU_H
