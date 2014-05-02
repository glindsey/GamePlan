#include "GUIFont.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI {

struct Font::Impl
{
  std::shared_ptr<sf::Font> normal_font;
  std::shared_ptr<sf::Font> bold_font;
  std::shared_ptr<sf::Font> italic_font;
  std::shared_ptr<sf::Font> boldital_font;
};

Font::Font(std::shared_ptr<sf::Font> normal_font,
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

sf::Font const& Font::get_normal_font() const
{
  return *(impl->normal_font.get());
}

sf::Font const& Font::get_bold_font() const
{
  return (impl->bold_font) ?
          *(impl->bold_font.get()) :
          *(impl->normal_font.get());
}

sf::Font const& Font::get_italic_font() const
{
  return (impl->italic_font) ?
          *(impl->italic_font.get()) :
          *(impl->normal_font.get());
}

sf::Font const& Font::get_boldital_font() const
{
  return (impl->boldital_font) ?
          *(impl->boldital_font.get()) :
          *(impl->normal_font.get());
}

Font::~Font()
{
  //dtor
}

} // end namespace GUI
