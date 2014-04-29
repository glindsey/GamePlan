#include "App.h"

#include <boost/random/uniform_int_distribution.hpp>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "gui/GUIFont.h"
#include "AppStateGameMode.h"
#include "AppStateMainMenu.h"
#include "AppStateSplashScreen.h"
#include "ConfigSettings.h"
#include "ErrorMacros.h"
#include "StateMachine.h"
#include "TextureAtlas.h"

// Static declarations
std::unique_ptr<App> app_;

// Local typedefs
typedef boost::random::uniform_int_distribution<> uniform_int_dist;

struct App::Impl
{
    std::unique_ptr<boost::random::mt19937> rng;
    std::unique_ptr<sf::RenderWindow> app_window;
    sf::Vector2u app_window_size;
    std::shared_ptr<GUIFont> default_font;
    std::shared_ptr<GUIFont> default_mono_font;
    std::unique_ptr<TextureAtlas> texture_atlas;
    std::unique_ptr<StateMachine> state_machine;
    bool is_running;
    bool has_window_focus;
};

App::App(std::string name)
  : impl(new Impl())
{
  // Create the random number generator.
  impl->rng.reset(new boost::random::mt19937(static_cast<unsigned int>(std::time(0))));

  // Create and open the main window.
  // GSL TODO: Window should not be resizable... probably
  impl->app_window.reset(new sf::RenderWindow(sf::VideoMode(1066, 600), name));

  // Set the app window size.
  impl->app_window_size = impl->app_window->getSize();

  // Create the default fonts.
  /// @todo Font names should be moved into ConfigSettings.
  std::shared_ptr<sf::Font> normal_font(new sf::Font());
  std::shared_ptr<sf::Font> bold_font(new sf::Font());
  std::shared_ptr<sf::Font> mono_font(new sf::Font());

  if (normal_font->loadFromFile("resources/fonts/" + Settings.font_name_default + ".ttf") == false)
  {
    FATAL_ERROR("Could not load the default font (" + Settings.font_name_default + ".ttf)");
  }

  if (bold_font->loadFromFile("resources/fonts/" + Settings.font_name_bold + ".ttf") == false)
  {
    FATAL_ERROR("Could not load the default bold font (" + Settings.font_name_bold + ".ttf)");
  }

  if (mono_font->loadFromFile("resources/fonts/" + Settings.font_name_mono + ".ttf") == false)
  {
    FATAL_ERROR("Could not load the default monospace font (" + Settings.font_name_mono + ".ttf)");
  }

  impl->default_font.reset(new GUIFont(normal_font, bold_font));
  impl->default_mono_font.reset(new GUIFont(mono_font));

  // Create the texture atlas.
  impl->texture_atlas.reset(new TextureAtlas());

  // Create the main state machine.
  impl->state_machine.reset(new StateMachine("app_state_machine"));

  // Set "window has focus" boolean to true.
  impl->has_window_focus = true;
}

App::~App()
{
  impl->app_window->close();
}

EventResult App::handle_event(sf::Event& event)
{
  EventResult result = EventResult::Ignored;

  switch (event.type)
  {
  case sf::Event::EventType::GainedFocus:
    {
      impl->has_window_focus = true;
      result = EventResult::Handled;
      break;
    }

  case sf::Event::EventType::LostFocus:
    {
      impl->has_window_focus = false;
      result = EventResult::Handled;
      break;
    }

  case sf::Event::EventType::Resized:
    {
      impl->app_window->setView(sf::View(sf::FloatRect(0, 0,
                                         event.size.width,
                                         event.size.height)));

      impl->app_window_size = sf::Vector2u(event.size.width,
                                           event.size.height);

      result = EventResult::Acknowledged;
      break;
    }

  case sf::Event::EventType::Closed:
    {
      impl->is_running = false;
      result = EventResult::Handled;
      break;
    }

  case sf::Event::EventType::KeyPressed:
    {
      switch (event.key.code)
      {
      case sf::Keyboard::Key::Escape:
        impl->is_running = false;
        result = EventResult::Handled;
        break;

      default:
        break;
      }
      break;
    }

  default:
    break;
  }

  if (result != EventResult::Handled)
  {
      result = impl->state_machine->handle_event(event);
  }

  return result;
}

bool App::has_window_focus()
{
  return impl->has_window_focus;
}

void App::run()
{
  int frame_counter = 0;
  static sf::Clock clock;

  // Populate the state machine using a template method.
  _populate_states();

  // Set running boolean.
  impl->is_running = true;

  clock.restart();

  // Start the loop
  while (impl->is_running)
  {
    // Process events
    sf::Event event;
    while (impl->app_window->pollEvent(event))
    {
      handle_event(event);
    }

    impl->state_machine->execute();

    // Limit frame rate to 62.5 fps.
    if (clock.getElapsedTime().asMilliseconds() > 16)
    {
      clock.restart();
      impl->app_window->clear();
      impl->state_machine->render(*(impl->app_window.get()), frame_counter);
      impl->app_window->display();
      ++frame_counter;
    }
  }
}

int App::get_rand(int minimum, int maximum)
{
   uniform_int_dist dist(minimum, maximum);
   return dist(*(impl->rng.get()));
}

std::shared_ptr<GUIFont> App::get_default_font()
{
  return impl->default_font;
}

// === Protected Methods ======================================================
StateMachine& App::get_state_machine()
{
  return *(impl->state_machine.get());
}
