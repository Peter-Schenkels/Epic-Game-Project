//
// Created by pieper on 01-01-20.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>
#include "object.hpp"

using namespace nlohmann;

///\brief
/// a Circle drawable
class Circle : public Object
{
    sf::CircleShape body;
    float radius;
    sf::Color color;

public:
    Circle(
        sf::Vector2f position,
        float radius,
        sf::Color color)
        : Object(position, sf::Vector2f(radius * 2, radius * 2)), body(radius), radius(radius), color(color)
    {
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(0);
    }

    void update() override;

    void draw(sf::RenderWindow &window) override;

    json export_to_json(json object) override;
};

#endif //CIRCLE_HPP
