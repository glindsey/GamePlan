#ifndef APP_H
#define APP_H

#include <boost/noncopyable.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <memory>
#include <SFML/Graphics.hpp>

#include "EventHandler.h"

// Forward declarations
namespace GUI
{
  class Font;
}
class MessageLog;
class StateMachine;
class TileSheet;

class App : public EventHandler, public boost::noncopyable
{
  public:
    App(std::string name);
    virtual ~App();

    void run();

    EventResult handle_event(sf::Event& event);

    bool has_window_focus();

    int get_rand(int minimum, int maximum);

    std::shared_ptr<GUI::Font> get_default_font();

  protected:
    StateMachine& get_state_machine();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;

    virtual void _populate_states() = 0;
};

/// Global app instance
extern std::unique_ptr<App> app_;

#endif // APP_H
