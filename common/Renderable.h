#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Graphics.hpp>

// Interface for a class that can be rendered to a target.
class Renderable
{
  public:
    virtual ~Renderable() {}
    virtual void render(sf::RenderTarget& target, int frame) = 0;
  protected:
  private:
};

#endif // RENDERABLE_H
