#include "player_hitbox.hpp"


Player_Hitbox::Player_Hitbox(sf::Vector2f position, sf::Vector2f size) :
    position(position),
    size(size),
    left(sf::Vector2f{ 0, size.y / 2 }),
    right{ sf::Vector2f{0, size.y / 2} },
    top({ size.x - size.x / 8, 0 }),
    bottom({ size.x - size.x / 2, 0 }),
    core({ size.x / 3, size.y / 3 }),
    touch({ size.x - size.x / 8, size.y }),
    box(size)
{
    Player_Hitbox_update(position);

    left.setOutlineThickness(1.f);
    right.setOutlineThickness(1.f);
    top.setOutlineThickness(1.f);
    bottom.setOutlineThickness(1.f);
    core.setOutlineThickness(1.f);
}

void Player_Hitbox::Player_Hitbox_update(sf::Vector2f new_position) {
    position = new_position;
    left.setPosition({ position.x, position.y + size.y / 4 });
    right.setPosition({ position.x + 1 + size.x, position.y + size.y / 4 });
    top.setPosition(position);
    bottom.setPosition({ position.x + size.x / 4, position.y + size.y });
    core.setPosition({ position.x + size.x / 6, position.y + size.y / 6 });
    touch.setPosition({ position.x + size.x / 8, position.y });
    box.setPosition(position);
}

void Player_Hitbox::Player_Hitbox_draw(sf::RenderWindow& window) {
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
    window.draw(core);
}

bool Player_Hitbox::Player_Hitbox_left_side_intersect(sf::FloatRect collider) {
    return left.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::Player_Hitbox_right_side_intersect(sf::FloatRect collider) {
    return right.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::Player_Hitbox_top_side_intersect(sf::FloatRect collider) {
    return top.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::Player_Hitbox_bottom_side_intersect(sf::FloatRect collider) {
    return bottom.getGlobalBounds().intersects(collider);
}


bool Player_Hitbox::Player_Hitbox_core_intersect(sf::FloatRect collider) {
    return core.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::Player_Hitbox_touch_intersect(sf::FloatRect collider) {
    return touch.getGlobalBounds().intersects(collider);
}

sf::FloatRect Player_Hitbox::Player_Hitbox_get_outerbounds() {
    return box.getGlobalBounds();
}




