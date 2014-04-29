#include "GUIFont.h"

#include <SFML/Graphics.hpp>
#include <memory>

struct GUIFont::Impl
{
  std::shared_ptr<sf::Font> normal_font;
  std::shared_ptr<sf::Font> bold_font;
  std::shared_ptr<sf::Font> italic_font;
  std::shared_ptr<sf::Font> boldital_font;
};

GUIFont::GUIFont(std::shared_ptr<sf::Font> normal_font,
                 std::shared_ptr<sf::Font> bold_font,
                 std::shared_ptr<sf::Font> italic_font,
                 std::shared_ptr<sf::Font> boldital_font)
  : impl(new Impl())
{
  impl->normal_font = normal_font;
  impl->bold_font = bold_font;
  impl->italic_font = italic_font;
  impl->boldital_font = boldital_font;
}

sf::Font const& GUIFont::get_normal_font() const
{
  return *(impl->normal_font.get());
}

sf::Font const& GUIFont::get_bold_font() const
{
  return (impl->bold_font) ?
          *(impl->bold_font.get()) :
          *(impl->normal_font.get());
}

sf::Font const& GUIFont::get_italic_font() const
{
  return (impl->italic_font) ?
          *(impl->italic_font.get()) :
          *(impl->normal_font.get());
}

sf::Font const& GUIFont::get_boldital_font() const
{
  return (impl->boldital_font) ?
          *(impl->boldital_font.get()) :
          *(impl->normal_font.get());
}

GUIFont::~GUIFont()
{
  //dtor
}
