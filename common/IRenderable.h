#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include <SFML/Graphics.hpp>

// Interface for a class that can be rendered to a target.
class IRenderable
{
  public:
    virtual ~IRenderable() {}
    virtual void render(sf::RenderTarget& target, int frame) = 0;
  protected:
  private:
};

#endif // IRENDERABLE_H
