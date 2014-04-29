#include "AppStateMainMenu.h"

#include "App.h"

#include "gui/GUIButton.h"
#include "gui/GUIFont.h"
#include "gui/GUIPane.h"

struct AppStateMainMenu::Impl
{
  sf::Text title;
  sf::Text subtitle;

  std::shared_ptr<GUIPane> main_menu_pane;
};

AppStateMainMenu::AppStateMainMenu(StateMachine* state_machine)
  : State(state_machine), impl(new Impl())
{
  impl->main_menu_pane.reset(new GUIPane("main_menu_pane", {400, 200},
                                         app_->get_default_font()));
  impl->main_menu_pane->set_position({200, 200});
  impl->main_menu_pane->set_title("Test GUIPane");

  std::shared_ptr<GUIButton> test_button;
  test_button.reset(new GUIButton("test_button", {150, 40},
                                  app_->get_default_font()));
  test_button->set_position({10, 100});
  test_button->set_text("Test Button");
  impl->main_menu_pane->add_child(test_button);
}

AppStateMainMenu::~AppStateMainMenu()
{
}

void AppStateMainMenu::execute()
{
}

void AppStateMainMenu::render(sf::RenderTarget& target, int frame)
{
  target.draw(impl->title);
  target.draw(impl->subtitle);
  impl->main_menu_pane->render(target, frame);
}

EventResult AppStateMainMenu::handle_event(sf::Event& event)
{
  EventResult result = EventResult::Ignored;

  switch (event.type)
  {
  case sf::Event::EventType::KeyPressed:
    switch (event.key.code)
    {
    case sf::Keyboard::Key::Space:
      // Switch to game state.
      this->change_to("AppStateGameMode");

      result = EventResult::Handled;
      break;

    default:
      break;
    }
    break;

  default:
    break;
  }

  if (result == EventResult::Ignored)
  {
    // Pass along to main menu pane.
    result = impl->main_menu_pane->handle_event(event);
  }

  return result;
}

std::string const& AppStateMainMenu::get_name()
{
  static std::string name = std::string("AppStateMainMenu");
  return name;
}

bool AppStateMainMenu::initialize()
{
  std::shared_ptr<GUIFont> default_font = app_->get_default_font();

  impl->title.setString("GUI Element Test");
  impl->title.setFont(default_font->get_normal_font());
  impl->subtitle.setString("Press Spacebar to continue.");
  impl->subtitle.setFont(default_font->get_normal_font());
  impl->subtitle.setCharacterSize(16);
  impl->subtitle.setPosition(0, 100);

  return true;
}

bool AppStateMainMenu::terminate()
{
  return true;
}
