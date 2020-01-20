#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "drawables.hpp"
#include "player_hitbox.hpp"


class Player : public Drawable {

private:
    sf::Vector2f speed = { 0, 0 };
    Picture* body;
    Player_Hitbox collision_box;
    float gravity = 0.5;
    float resistance = 2;
    bool floating = false;
    bool on_ground = false;
    int jump_speed = 15; /// amount of pixels per update 
    sf::Vector2f static_scale; // shouldn't be changed is used for flipping the body


public:
    Player(sf::Vector2f position, sf::Vector2f size) :
        Drawable(position, size, "player", "White"),
        collision_box(position, size)
    {}

    Player(sf::Vector2f position, sf::Vector2f size, Picture* sprite) :
        Drawable(position, size, "player", "White"),
        collision_box(position, size)
    {
        player_init(sprite);

       
    }


    // Set player speed
    void player_set_speed(sf::Vector2f new_speed) {
        speed = new_speed;
    }

    // Get player speed
    sf::Vector2f player_get_speed() {
        return speed;
    }

    void player_init(Picture* sprite) {
        std::cout << "Initialising player..." << std::endl;
        body = sprite;
        body->picture_set_size(drawable_get_size());
        body->drawable_set_position(location);
        static_scale = sprite->picture_get_scale();
        std::cout << "Initialising player completed" << std::endl;
    }

    void drawable_draw(sf::RenderWindow& window) override {
        collision_box.Player_Hitbox_draw(window);
        body->drawable_draw(window);
    }

    void drawable_update() override {
        if (!floating) {
            speed.y += gravity;
            location += speed;
        }
        collision_box.Player_Hitbox_update(location);
        body->drawable_set_position(location);
        body->drawable_update();
    }

    std::string drawable_get_visual() override {
        return color;
    };

    void player_set_static(bool boolean) {
        floating = boolean;
    }




    // Handles all input events
    void player_input(sf::Event event) {
        // If key up is pressed: jump!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && speed.y == -0.5) {
            speed.y = float(-1 * (jump_speed + 0.01));
        }
        // If key left is pressed: move left!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            speed.x = -7;
            body->picture_set_scale(static_scale);
            body->picture_set_offset({ 0, 0 });
        }
        else if (speed.x < 0) {
            speed.x += 7;
            if (speed.x > 0) {
                speed.x = 0;
            }
        }
        //if key right is pressed: move right!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            speed.x = 7;
            body->picture_set_scale({ -1*static_scale.x, static_scale.y });
            body->picture_set_offset({ drawable_get_size().x, 0 });
        }
        else if (speed.x > 0) {
            speed.x -= 7;
            if (speed.x < 0) {
                speed.x = 0;
            }
        }
    }

    // Collision detection between a player and a sf::FloatRect
    void player_collision(Drawable* object) {
        // Check if a sf::FloatRect collides with the right  or left side of the hitbox
        if (collision_box.Player_Hitbox_left_side_intersect(object->drawable_get_hitbox())){
            speed.x = 0;
            location.x = object->drawable_get_hitbox().left + object->drawable_get_hitbox().width;
        }
        else if (collision_box.Player_Hitbox_right_side_intersect(object->drawable_get_hitbox())){
            speed.x = 0;
            location.x = object->drawable_get_hitbox().left - drawable_get_size().x;
        }
        // Check if a sf::FloatRect collides with the bottom  or top of the hitbox
        else if (collision_box.Player_Hitbox_bottom_side_intersect(object->drawable_get_hitbox())){
            location.y = object->drawable_get_hitbox().top - drawable_get_size().y;
            speed.y = -0.5;
            on_ground = true;
        }
        else if (collision_box.Player_Hitbox_top_side_intersect(object->drawable_get_hitbox())){
            on_ground = false;
            speed.y = 1;
        }
    }
};



#endif