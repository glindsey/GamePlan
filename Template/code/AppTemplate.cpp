#include "AppTemplate.h"

#include "AppStateGameMode.h"
#include "AppStateMainMenu.h"
#include "AppStateSplashScreen.h"
#include "StateMachine.h"

AppTemplate::AppTemplate()
  : App("Template Application")
{
  //ctor
}

AppTemplate::~AppTemplate()
{
  //dtor
}

void AppTemplate::_populate_states()
{
  StateMachine& sm = get_state_machine();
  // Add states to the state machine.
  sm.add_state(new AppStateSplashScreen(&sm));
  sm.add_state(new AppStateMainMenu(&sm));
  sm.add_state(new AppStateGameMode(&sm));

  // Switch to initial state.
  // DEBUG: Go right to game mode for now.
  sm.change_to("AppStateMainMenu");
  //sm.change_to("AppStateGameMode");
}
