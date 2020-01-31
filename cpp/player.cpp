#include "player.hpp"

Player::Player(sf::Vector2f position, sf::Vector2f size, std::vector<Animation> animations) :
    Drawable(position, size, "player", "White"),
    collision_box(position, size)

{
    // Load the set of sprites as an animation
    animation_controller = Animation_Controller(animations);
    // Set starting location and sprite
    respawn_location = position;
    animation_controller.animation_controller_set_state("Idle left");
}


// Set player speed
void Player::player_set_speed(sf::Vector2f new_speed) {
    speed = new_speed;
}

// Get player speed
sf::Vector2f Player::player_get_speed() {
    return speed;
}

// Sets the displayed picture to a new sprite
void Player::set_picture(Picture* sprite) {
    if (sprite != body) {
        body = sprite;
    }
}

// Draw the player
void Player::drawable_draw(sf::RenderWindow& window) {

    body->drawable_draw(window);

}

// Update the player
void Player::drawable_update() {
    // Set picture to the next one in line from the animation
    set_picture(animation_controller.get_frame());
    animation_controller.update();
    // Apply gravity and speed
    if (!floating) {
        speed.y += gravity;
        location += speed;
    }
    // Update the player hitbox and the picture
    collision_box.Player_Hitbox_update(location);
    body->drawable_set_position(location);
    body->drawable_update();
}

// Return visual
std::string Player::drawable_get_visual() {
    return color;
};

// Set gravity (for debugging)
void Player::player_set_static(bool boolean) {
    floating = boolean;
}

void Player::input_cooldown() {
    timer.restart();
}

// Handles all input events
void Player::player_input(sf::Event event) {
    if (timer.getElapsedTime().asMilliseconds() > 200) {

        // If key up is pressed: jump!
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) && on_ground) {
            speed.y = float(-1 * (jump_speed + 0.01));

        }
        // If key left is pressed: move left!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            speed.x = -7;
            animation_controller.animation_controller_set_state("Walking left");
        }
        else if (speed.x < 0) {
            animation_controller.animation_controller_set_state("idle-right");
            if (on_ground) {
                speed.x = 0;
            }
            else {
                speed.x += float(0.5);
            }
            std::cout << speed.x << "\n";
        }
        // If key right is pressed: move right!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            speed.x = 7;
            animation_controller.animation_controller_set_state("Walking right");
        }
        else if (speed.x > 0) {
            animation_controller.animation_controller_set_state("idle-left");
            if (on_ground) {
                speed.x = 0;
            }
            else {
                speed.x -= float(0.5);
            }
        }
    }
}

// Return dead variable
int Player::player_get_dead() {
    return dead;
}

// Set dead variable
void Player::player_set_dead(int new_dead) {
    dead = new_dead;
}

// Respawn the player
void Player::player_respawn() {
    drawable_set_position(respawn_location);
}

// Collision detection between a player and a sf::FloatRect
bool Player::player_collision(Drawable* object) {

    std::string object_name = object->drawable_get_name();

    // If the object shouldn't collide with player put the name right here
    if (object_name == "arrow left" or object_name == "arrow right" or object_name == "arrow up"
        or object_name == "arrow down" or object_name == "cross") return 0;

    if (collision_box.Player_Hitbox_core_intersect(object->drawable_get_hitbox()) && dead == 0) {
        dead = 155;
        return true;
    }
    // Check if a sf::FloatRect collides with the body of Mr. wo
    if (collision_box.Player_Hitbox_touch_intersect(object->drawable_get_hitbox())) {
        // If the object is a spike kill mr wo
        if (object->drawable_get_name() == "spike") {
            dead = 155;
        }
    }
    if (speed.y == float(-0.00001)) {
        on_ground = true;
    }
    else {
        on_ground = false;
    }

    // Check if a sf::FloatRect collides with the bottom  or top of the hitbox
    if (collision_box.Player_Hitbox_bottom_side_intersect(object->drawable_get_hitbox())) {
        location.y = object->drawable_get_hitbox().top - drawable_get_size().y;
        speed.y = float(-0.00001);



        return true;
    }
    else if (collision_box.Player_Hitbox_top_side_intersect(object->drawable_get_hitbox())) {
        speed.y = 1;
        return true;
    }

    // Check if a sf::FloatRect collides with the right  or left side of the hitbox
    if (collision_box.Player_Hitbox_left_side_intersect(object->drawable_get_hitbox())) {
        speed.x = -0.5;
        location.x = object->drawable_get_hitbox().left + object->drawable_get_hitbox().width;
        return true;
    }
    if (collision_box.Player_Hitbox_right_side_intersect(object->drawable_get_hitbox())) {
        speed.x = 0.5;
        location.x = object->drawable_get_hitbox().left - drawable_get_size().x;
        return true;
    }
    return false;

}
//check if player hitbox intersect with object mainly used for portal detection
bool Player::player_intersect(sf::FloatRect collide) {
    return collision_box.Player_Hitbox_core_intersect(collide) ||
        collision_box.Player_Hitbox_left_side_intersect(collide) ||
        collision_box.Player_Hitbox_right_side_intersect(collide) ||
        collision_box.Player_Hitbox_top_side_intersect(collide) ||
        collision_box.Player_Hitbox_bottom_side_intersect(collide);
}