//
// Created by pieper on 01-01-20.
//

#ifndef SFML_TEMPLATES_SPRITE_HPP
#define SFML_TEMPLATES_SPRITE_HPP

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include <string>
using namespace nlohmann;

///\brief 
/// drawable with an image
class Sprite : public Object{

    sf::Texture texture;
    sf::Sprite body;

    /// this Shape is used for the factory 
    /// pattern to display an outline if thsi sprite is selected
    sf::RectangleShape fake;

public:
    sf::Vector2f size_factor;
    std::string img_location;

    /// Sprite contructor: Takes in a sf::Vector2f for start position
    /// And a sf::Vector2f for a size factor to scale ups the image to the factor
    /// A image location as an std::string
    Sprite(
        sf::Vector2f i_position,
        sf::Vector2f size_factor,
        std::string img_location
    ):
        Object({0,0}, {0,0}),
        size_factor(size_factor),
        img_location(img_location)
    {
        set_texture(img_location);
        body.setScale(size_factor);
        position  = i_position;
        size = sf::Vector2f(texture.getSize().x * size_factor.x, texture.getSize().y * size_factor.y);
        fake.setSize(size);
        fake.setOutlineThickness(0);
        fake.setOutlineColor(sf::Color::White);
        set_sprite_size(sf::Vector2f(50, 50));
    }
    
    /// Set texture of sprite to different img using an image location
    /// !(Warning) Don't use this function during runtime, it makes the program
    /// substantially slower (use set_texture(sf::Texture & img) instead)
    void set_texture(std::string img_location);

    /// Set texture of sprite to different img using an sf::Texture
    void set_texture(sf::Texture & img);

    /// Updates the current values of the object
    void update() override;

    /// Draws the body of this class into a window
    void draw(sf::RenderWindow & window) override ;

    /// Changes the sprite size to any givin pixel size
    void set_sprite_size(sf::Vector2f new_size);

    /// This function si only to be used by the factory pattern
    /// it exports this class to a json format       
    json export_to_json(json object) override;

    /// This function returns the global bounds of the body in sf::floatrec
    sf::FloatRect get_boundaries() override { return body.getGlobalBounds(); }

};





#endif //SFML_TEMPLATES_SPRITE_HPP
