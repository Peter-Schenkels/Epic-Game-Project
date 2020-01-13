//
// Created by pieper on 01-01-20.
//

#include "sprite.hpp"

void print_vector2f(sf::Vector2f size) {
    std::cout << size.x << " " << size.y << std::endl;
}

void Sprite::set_sprite_size(sf::Vector2f new_size) {
    sf::Vector2f current_factor = body.getScale();
    sf::Vector2f new_factor(current_factor.x * (new_size.x / size.x),
                            current_factor.y * (new_size.y / size.y));

    size = new_size;
    body.setScale(new_factor);
    fake.setSize(size);
}

void Sprite::set_texture(std::string img_location) {
    texture.loadFromFile(img_location);
    body.setTexture(texture);
}

void Sprite::set_texture(sf::Texture& img) {
    texture = img;
    body.setTexture(texture);
}

void Sprite::update() {
    body.setPosition(position);
    fake.setPosition(position);
    if (selected) {
        fake.setOutlineThickness(2);
    } else {
        fake.setOutlineThickness(0);
    }
}

void Sprite::draw(sf::RenderWindow& window) {
    window.draw(fake);
    window.draw(body);
}

json Sprite::export_to_json(json object) {
    object["location"] = img_location;
    vector2f_to_json(object["factor"], size_factor);
    vector2f_to_json(object["position"], position);
    object["type"] = "Sprite";

    return object;
}