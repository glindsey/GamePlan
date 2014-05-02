#include "AppStateMainMenu.h"

#include "App.h"

#include "gui/GUIButton.h"
#include "gui/GUIEnums.h"
#include "gui/GUIFont.h"
#include "gui/GUIPane.h"

struct AppStateMainMenu::Impl
{
  sf::Text title;
  sf::Text subtitle;

  std::shared_ptr<GUI::Pane> main_menu_pane;
};

AppStateMainMenu::AppStateMainMenu(StateMachine* state_machine)
  : State(state_machine), impl(new Impl())
{
  impl->main_menu_pane.reset(new GUI::Pane("main_menu_pane", {400, 200},
                                           app_->get_default_font()));
  impl->main_menu_pane->set_position({100, 100});
  impl->main_menu_pane->set_title("Test GUI Pane");

  std::shared_ptr<GUI::Button> test_button;
  test_button.reset(new GUI::Button("test_button", {150, 40},
                                    app_->get_default_font()));
  test_button->set_alignment({GUI::HorizAlign::Center, GUI::VertAlign::Center});
  test_button->set_text("Test Button");
  impl->main_menu_pane->add_child(test_button);

  impl->main_menu_pane->set_visible(true);
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
  std::shared_ptr<GUI::Font> default_font = app_->get_default_font();

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
