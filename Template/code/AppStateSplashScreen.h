#ifndef APPSTATESPLASHSCREEN_H
#define APPSTATESPLASHSCREEN_H

#include <memory>

#include "State.h"

class AppStateSplashScreen : public State
{
  public:
    AppStateSplashScreen(StateMachine* state_machine);
    virtual ~AppStateSplashScreen();

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

#endif // APPSTATESPLASHSCREEN_H
