#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <boost/container/flat_map.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/strong_typedef.hpp>
#include <memory>
#include <SFML/Graphics.hpp>

BOOST_STRONG_TYPEDEF(unsigned int, TextureId);

// Forward declaration

/// "Atlas" texture containing all graphical textures used in the engine.
class TextureAtlas
{
public:
  TextureAtlas();
  virtual ~TextureAtlas();

  /// Save a texture into the atlas.
  TextureId save(sf::Image& image);

  /// Get the coordinates corresponding to a particular texture.
  sf::IntRect const& getRect(TextureId texNumber);

  /// Get the atlas texture.
  sf::Texture const* getAtlasTexture(void);

  /// Constant for the largest atlas we will try to construct.
  static const unsigned int MAXIMUM_ATLAS_DIMENSION;

protected:
private:
  /// Locate a free spot in the texture to place an image.
  bool findNextSpot(sf::Vector2u& origin, sf::Vector2u const& imageBlocks);

  /// Mark a spot in the texture as reserved.
  void reserveSpot(sf::Vector2u const& origin,
                   sf::Vector2u const& imageBlocks);

  inline unsigned int get_block(unsigned int x, unsigned int y)
  {
    return (y * maxBlocks) + x;
  }

  struct Impl;
  std::unique_ptr<Impl> impl;

  /// Number of blocks.  Each block is 16x16 (by default) in size.
  unsigned int maxBlocks;

  /// Bitset indicating which blocks are in use.
  boost::dynamic_bitset<> used;

  /// Big texture stored on the graphics card.
  sf::Texture atlas;

  /// Map of texture rects.
  boost::container::flat_map<TextureId, sf::IntRect> texRect;

  /// Next serial number to use.
  TextureId nextSerialNumber;

  // === Static public members ==============================================
public:
  static unsigned int const BLANK = 0;

  // === Static private members =============================================
private:
  /// Size of blocks, as a power of 2.
  /// Larger blocks will let the placer algorithm run faster but results
  /// in less efficient packing of images; smaller blocks make the placer
  /// algorithm take longer to find a suitable place.
  static unsigned int const blockSize = 4;
};

#define TAtlas TextureAtlas::instance()

#endif // TEXTUREATLAS_H
