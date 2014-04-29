#include "AppTemplate.h"

int main()
{
  // Create and run the app instance.
  app_.reset(new AppTemplate());
  app_->run();

  return EXIT_SUCCESS;
}
