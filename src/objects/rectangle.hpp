//
// Created by pieper on 01-01-20.
//

#ifndef SFML_TEMPLATES_RECTANGLE_HPP
#define SFML_TEMPLATES_RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "object.hpp"

using namespace nlohmann;

///\brief 
/// a Rectangle drawable
class Rectangle : public Object {

private:
    sf::RectangleShape body;
    sf::Color color;

public:
    Rectangle(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color
    ):
        Object(position, size),
        body(size),
        color(color)
    {
        body.setPosition(position);
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(0);
    }

    void update() override;
    

    void draw(sf::RenderWindow & window) override {
        window.draw(body);
    }

    json export_to_json(json object) override;

};


#endif //SFML_TEMPLATES_RECTANGLE_HPP
