#ifndef TILESHEET_H
#define TILESHEET_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

/// Sheet containing all tiles in the application.
class TileSheet
{
  public:
    TileSheet();
    virtual ~TileSheet();

    /// Load a sprite sheet from disk.
    bool load(std::string const& filename);

    /// Get a particular tile from the sheet.
    /// @warning Assumes tile is within the bounds of the loaded texture,
    ///          unless DEBUG is defined, in order to save execution time.
    sf::IntRect get_tile(sf::Vector2u tile) const;

    /// Get a reference to the texture to render.
    sf::Texture& getTexture(void);

    /// Add vertices to the requested vertex array.
    /// This method maps the requested tile onto a quadrilateral specified
    /// by the four coordinate pairs passed in.  This allows for pseudo-3D
    /// walls to be drawn.
    /// @param vertices Vertex array to add to.
    /// @param tile_coords Coordinates of the tile to render.
    /// @param bg_color Color to blend with (for lighting).
    /// @param ul_coord Upper-left coordinates.
    /// @param ur_coord Upper-right coordinates.
    /// @param ll_coord Lower-left coordinates.
    /// @param lr_coord Lower-right coordinates.
    static void add_quad(sf::VertexArray& vertices,
                             sf::Vector2u tile_coords, sf::Color bg_color,
                             sf::Vector2f ul_coord, sf::Vector2f ur_coord,
                             sf::Vector2f ll_coord, sf::Vector2f lr_coord);

    /// Add vertices to the requested vertex array.
    /// This method is similar to add_quad but allows the caller to specify
    /// the color of each vertex individually, allowing for gradients across
    /// the quadrilateral.
    /// @param vertices Vertex array to add to.
    /// @param tile_coords Coordinates of the tile to render.
    /// @param ul_color Color of upper-left vertex.
    /// @param ul_coord Upper-left coordinates.
    /// @param ur_color Color of upper-right vertex.
    /// @param ur_coord Upper-right coordinates.
    /// @param ll_color Color of lower-left vertex.
    /// @param ll_coord Lower-left coordinates.
    /// @param lr_color Color of lower-right vertex.
    /// @param lr_coord Lower-right coordinates.
    static void add_gradient_quad(sf::VertexArray& vertices,
                                  sf::Vector2u tile_coords,
                                  sf::Color ul_color, sf::Vector2f ul_coord,
                                  sf::Color ur_color, sf::Vector2f ur_coord,
                                  sf::Color ll_color, sf::Vector2f ll_coord,
                                  sf::Color lr_color, sf::Vector2f lr_coord);

    /// Add outline vertices to the requested vertex array.
    /// This method draws a hollow quadrilateral in the color specified by
    /// bg_color.
    /// @param vertices Vertex array to add to.
    /// @param bg_color Color to blend with (for lighting).
    /// @param ul_coord Upper-left coordinates.
    /// @param ur_coord Upper-right coordinates.
    /// @param ll_coord Lower-left coordinates.
    /// @param lr_coord Lower-right coordinates.
    static void add_outline_vertices(sf::VertexArray& vertices,
                                     sf::Color bg_color,
                                     sf::Vector2f ul_coord,
                                     sf::Vector2f ur_coord,
                                     sf::Vector2f ll_coord,
                                     sf::Vector2f lr_coord);

  protected:
  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // TILESHEET_H
