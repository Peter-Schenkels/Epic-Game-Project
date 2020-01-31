#pragma warning(push)
#pragma warning(disable: 4244)
#ifndef TILEMAP_HPP
#define TILEMAP_HPP

// tilemap.hpp
// Check if a sf::FloatRect collides with the right or left side of the hitbox
// Contains Tile_Map class

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

// Class for creating random backgrounds
class Tile_Map : public sf::Drawable, public sf::Transformable{
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    // Draw the background
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Apply the transform
        states.transform *= getTransform();

        // Apply the tileset texture
        states.texture = &m_tileset;

        // Draw the vertex array
        target.draw(m_vertices, states);
    }

public:
    // Load the textures
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // Load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // Resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // Populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // Get the current tile number
                int tileNumber = tiles[i + j * width];

                // Find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // Get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // Define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // Define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        return true;
    }
};

#pragma warning(pop)
#endif