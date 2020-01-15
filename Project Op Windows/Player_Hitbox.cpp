#include "player_hitbox.hpp"


Player_Hitbox::Player_Hitbox(sf::Vector2f position, sf::Vector2f size) :
    position(position),
    size(size),
    left(sf::Vector2f{ 0, size.y / 2 }),
    right{ sf::Vector2f{0, size.y / 2} },
    top({ size.x - size.x / 8, 0 }),
    bottom({ size.x - size.x / 8, 0 }),
    box(size)
{
    left.setPosition({ position.x, position.y + size.y / 4 });
    right.setPosition({ position.x + 1 + size.x, position.y + size.y / 4 });
    top.setPosition(position);
    bottom.setPosition({ position.x + 1, position.y + size.y });
    box.setPosition(position);

    left.setOutlineThickness(1.f);
    right.setOutlineThickness(1.f);
    top.setOutlineThickness(1.f);
    bottom.setOutlineThickness(1.f);
}

void Player_Hitbox::update(sf::Vector2f new_position) {
    position = new_position;
    left.setPosition({ position.x, position.y + size.y / 4 });
    right.setPosition({ position.x + 1 + size.x, position.y + size.y / 4 });
    top.setPosition(position);
    bottom.setPosition({ position.x + 1, position.y + size.y });
    box.setPosition(position);
}

void Player_Hitbox::draw(sf::RenderWindow& window) {
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
}

bool Player_Hitbox::leftSideIntersect(sf::FloatRect collider) {
    return left.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::rightSideIntersect(sf::FloatRect collider) {
    return right.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::topSideIntersect(sf::FloatRect collider) {
    return top.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::bottomSideIntersect(sf::FloatRect collider) {
    return bottom.getGlobalBounds().intersects(collider);
}

sf::FloatRect Player_Hitbox::getOuterbounds() {
    return box.getGlobalBounds();
}