//
// Created by pieper on 01-01-20.
//

#include "object.hpp"


Object::Object(sf::Vector2f position, sf::Vector2f size) : position(position),
                                                           size(size)
                                                           
                                                           {}

sf::FloatRect Object::get_boundaries() {
    sf::RectangleShape tmp_body(size);
    tmp_body.setPosition(position);
    return tmp_body.getGlobalBounds();
}

void Object::select(sf::Event event) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (get_boundaries().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            selected = !selected;
            while (sf::Mouse::isButtonPressed(sf::Mouse::Right));
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected) {
        if (event.mouseMove.x > 0 && event.mouseMove.y > 0) {
            set_position(sf::Vector2f(
                event.mouseMove.x - (size.x / 2),
                event.mouseMove.y - (size.y / 2)));
        }
    }
}
