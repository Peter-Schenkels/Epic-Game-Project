#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "drawables.hpp"
#include "player_hitbox.hpp"

class Player : public drawable {

private:
    sf::Vector2f speed = { 0, 0 };
    picture* body;
    Player_Hitbox collision_box;
    float gravity = 0.5;
    float resistance = 2;
    bool floating = false;
    bool on_ground = false;
    int jump_speed = 15; /// amount of pixels per update 

public:
    Player(sf::Vector2f position, sf::Vector2f size) :
        drawable(position, size, "player", "White"),
        collision_box(position, size)
    {}

    Player(sf::Vector2f position, sf::Vector2f size, picture* sprite) :
        drawable(position, size, "player", "White"),
        collision_box(position, size)
    {
        init(sprite);
    }

    void init(picture* sprite)
    {
        std::cout << "Initialising player..." << std::endl;
        body = sprite;
<<<<<<< Updated upstream
        body->set_picture_size(drawable_get_size());
        body->drawable_set_position(location);
=======
        body->picture_set_size(drawable_get_size());
        body->drawable_set_position(position);
>>>>>>> Stashed changes
        std::cout << "Initialising player completed" << std::endl;
    }

    void drawable_draw(sf::RenderWindow& window) override
    {
        body->drawable_draw(window);
    }

    void drawable_update() override
    {
        if (!floating) {
            speed.y += gravity;
            position += speed;
        }
<<<<<<< Updated upstream

        collision_box.update(location);
        body->drawable_set_position(location);
=======
        collision_box.Player_Hitbox_update(position);
        body->drawable_set_position(position);
>>>>>>> Stashed changes
        body->drawable_update();
    }

    std::string drawable_get_visual() override {
        return color;
    };

    void set_static(bool boolean) {
        floating = boolean;
    }


    //handles all input events
    void input(sf::Event event) {
        //if key up is pressed: jump!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && speed.y == -0.5) {
            speed.y = float(-1 * (jump_speed + 0.01));
        }
        //if key left is pressed: move left!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            speed.x = -7;
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
        }
        else if (speed.x > 0) {
            speed.x -= 7;
            if (speed.x < 0) {
                speed.x = 0;
            }
        }
    }

    //collision detection between a player and a sf::FloatRect
    void collision(drawable* object)
    {
        //check if a sf::FloatRect collides with the right  or left side of the hitbox
        if (collision_box.leftSideIntersect(object->drawable_get_hitbox()))
        {
            speed.x = 0;
<<<<<<< Updated upstream
            location.x = object->drawable_get_hitbox().left + object->drawable_get_hitbox().width;

=======
            position.x = object->drawable_get_hitbox().left + object->drawable_get_hitbox().width;
>>>>>>> Stashed changes
        }
        else if (collision_box.rightSideIntersect(object->drawable_get_hitbox()))
        {
            speed.x = 0;
<<<<<<< Updated upstream
            location.x = object->drawable_get_hitbox().left - drawable_get_size().x;


        }
        //check if a sf::FloatRect collides with the bottom  or top of the hitbox
        else if (collision_box.bottomSideIntersect(object->drawable_get_hitbox()))

        {
            location.y = object->drawable_get_hitbox().top - drawable_get_size().y;
=======
            position.x = object->drawable_get_hitbox().left - drawable_get_size().x;
        }
        // Check if a sf::FloatRect collides with the bottom  or top of the hitbox
        else if (collision_box.Player_Hitbox_bottom_side_intersect(object->drawable_get_hitbox())){
            position.y = object->drawable_get_hitbox().top - drawable_get_size().y;
>>>>>>> Stashed changes
            speed.y = -0.5;
            on_ground = true;
        }
        else if (collision_box.topSideIntersect(object->drawable_get_hitbox())){
            on_ground = false;
            speed.y = 1;
        }

    }

};



#endif