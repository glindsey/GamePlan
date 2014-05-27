#ifndef APPSTATEMAINMENU_H
#define APPSTATEMAINMENU_H

#include <memory>

#include "State.h"


class AppStateMainMenu : public State
{
  public:
    AppStateMainMenu(StateMachine* state_machine);
    virtual ~AppStateMainMenu();

    virtual void execute() override;
    virtual void render(sf::RenderTarget& target, int frame) override;
    virtual EventResult handle_event(sf::Event& event) override;
    virtual std::string const& get_name() override;
    virtual bool initialize() override;
    virtual bool terminate() override;

    void do_button_clicked();

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // APPSTATEMAINMENU_H
