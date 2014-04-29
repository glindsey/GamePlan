#ifndef APPTEMPLATE_H
#define APPTEMPLATE_H

#include "App.h"

class AppTemplate : public App
{
  public:
    AppTemplate();
    virtual ~AppTemplate();
  protected:
  private:
    virtual void _populate_states() override;
};

#endif // APPTEMPLATE_H
