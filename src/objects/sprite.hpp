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
    sf::RectangleShape fake;
    std::string ID;


public:
    sf::Vector2f size_factor;
    std::string img_location;

    Sprite(
        sf::Vector2f i_position,
        sf::Vector2f size_factor,
        std::string img_location,
        std::string ID
    ):
        Object({0,0}, {0,0}),
        ID(ID),
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
    
    void set_texture(std::string img_location);

    void set_texture(sf::Texture & img);

    void update() override;

    void draw(sf::RenderWindow & window) override ;

    void set_sprite_size(sf::Vector2f new_size);

    std::string get_id(){ return ID; }

    json export_to_json(json object) override;

};





#endif //SFML_TEMPLATES_SPRITE_HPP
