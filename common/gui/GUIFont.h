#ifndef GUIFONT_H
#define GUIFONT_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI {

class Font
{
  public:
    Font(std::shared_ptr<sf::Font> normal_font,
         std::shared_ptr<sf::Font> bold_font = std::shared_ptr<sf::Font>(),
         std::shared_ptr<sf::Font> italic_font = std::shared_ptr<sf::Font>(),
         std::shared_ptr<sf::Font> boldital_font = std::shared_ptr<sf::Font>());
    virtual ~Font();

    sf::Font const& get_normal_font() const;
    sf::Font const& get_bold_font() const;
    sf::Font const& get_italic_font() const;
    sf::Font const& get_boldital_font() const;

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

}

#endif // GUIFONT_H
