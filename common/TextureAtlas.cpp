#include <iostream>
#include <boost/format.hpp>

#include "TextureAtlas.h"

#include "ErrorMacros.h"

const unsigned int TextureAtlas::MAXIMUM_ATLAS_DIMENSION = 4096;

struct TextureAtlas::Impl
{
  TextureId nextTextureId;
};

TextureAtlas::TextureAtlas()
  : impl(new Impl())
{
  impl->nextTextureId = static_cast<TextureId>(0);

  unsigned int maximumSize = sf::Texture::getMaximumSize();
  std::cout << boost::format("Maximum theoretical texture size on this computer is %1%x%1%.")
               % maximumSize << std::endl;
  std::cout << boost::format("Block size for this texture atlas is %1%x%1%.")
               % (1 << blockSize) << std::endl;

  maximumSize = std::min(maximumSize, MAXIMUM_ATLAS_DIMENSION);

  std::cout << boost::format("Creating a %1%x%1% atlas.")
               % maximumSize << std::endl;

  atlas.create(maximumSize, maximumSize);
  maxBlocks = maximumSize >> blockSize;
  used.resize(maxBlocks * maxBlocks, false);

  // Mark block (0, 0) as used, and create an area of {255,255,255,255} so
  // we have a "blank" texture.
  sf::Image blankImage;
  blankImage.create((1 << blockSize), (1 << blockSize), sf::Color::White);
  save(blankImage);
}

TextureAtlas::~TextureAtlas()
{

}

TextureId TextureAtlas::save(sf::Image& image)
{
  sf::Vector2u divided
  { image.getSize().x >> blockSize, image.getSize().y >> blockSize };
  sf::Vector2u remaining
  {
    image.getSize().x& ((1 << blockSize) - 1), image.getSize().y
    & ((1 << blockSize) - 1)
  };
  sf::Vector2u imageBlocks
  {
    divided.x + ((remaining.x != 0) ? 1 : 0), divided.y
    + ((remaining.y != 0) ? 1 : 0)
  };

  bool suitable = true;
  sf::Vector2u origin
  { 0, 0 };

  TextureId textureId = impl->nextTextureId;

  suitable = findNextSpot(origin, imageBlocks);

  if (suitable == false)
  {
    FATAL_ERROR("No room left in texture atlas to store an image");
  }

  // At this point, xOrigin/yOrigin is a suitable block to store the image.
  atlas.update(image, origin.x << blockSize, origin.y << blockSize);

  // Save texture information and add it to our set.
  sf::IntRect info;
  info.left = origin.x << blockSize;
  info.top = origin.y << blockSize;
  info.width = image.getSize().x;
  info.height = image.getSize().y;
  texRect[textureId] = info;
  ++(impl->nextTextureId);

  reserveSpot(origin, imageBlocks);

  return textureId;
}

bool TextureAtlas::findNextSpot(sf::Vector2u& origin,
                                sf::Vector2u const& imageBlocks)
{
  bool suitable = false;

  // NOTE: This is super-duper inefficient.
  //       I am sure this algorithm's speed could be greatly improved; for now this works.
  for (origin.y = 0; origin.y < maxBlocks; ++origin.y)
  {
    for (origin.x = 0; origin.x < maxBlocks; ++origin.x)
    {
      // Start by assuming the origin block is suitable.
      suitable = true;

      // Now check the spots left of and below the origin to see if there's room.
      for (unsigned int yCheck = origin.y; yCheck < origin.y + imageBlocks.y;
           ++yCheck)
      {
        for (unsigned xCheck = origin.x; xCheck < origin.x + imageBlocks.x;
             ++xCheck)
        {
          if (used[get_block(xCheck, yCheck)])
          {
            suitable = false;
            break;
          }
        }
        if (suitable == false)
        {
          break;
        }
      }
      if (suitable == true)
      {
        break;
      }
    }
    if (suitable == true)
    {
      break;
    }
  }
  return suitable;
}

void TextureAtlas::reserveSpot(const sf::Vector2u& origin,
                               const sf::Vector2u& imageBlocks)
{
  for (unsigned int yBlocks = origin.y; yBlocks < origin.y + imageBlocks.y;
       ++yBlocks)
  {
    for (unsigned int xBlocks = origin.x; xBlocks < origin.x + imageBlocks.x;
         ++xBlocks)
    {
      used[get_block(xBlocks, yBlocks)] = true;
    }
  }
}

const sf::IntRect& TextureAtlas::getRect(TextureId texNumber)
{
  return texRect[texNumber];
}

const sf::Texture* TextureAtlas::getAtlasTexture(void)
{
  return &atlas;
}
