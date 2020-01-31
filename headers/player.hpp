
#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "drawables.hpp"
#include "player_hitbox.hpp"
#include "animation_controller.hpp"


// Class for the player character
class Player : public Drawable {

private:

    sf::Vector2f speed = { 0, 0 };
    Picture* body;
    Player_Hitbox collision_box;
    sf::Vector2f respawn_location = { 0, 0 } ;
    sf::Clock timer;
    float gravity = 0.5;
    float resistance = 2;
    bool floating = false;
    bool on_ground = false;
    int dead = 0;
    float jump_speed = 10.5; // amount of pixels per update 
    sf::Vector2f static_scale; // shouldn't be changed is used for flipping the body
    Animation_Controller animation_controller;

public:

    // Default contructor
    Player() {}

    // Constructor 
    Player(
        sf::Vector2f position, 
        sf::Vector2f size, 
        std::vector<Animation> animations
    );

    // Set player speed
    void player_set_speed(sf::Vector2f new_speed);

    // Get player speed
    sf::Vector2f player_get_speed();

    // Sets the displayed picture to a new sprite
    void set_picture(Picture* sprite);

    // Draw the player
    void drawable_draw(sf::RenderWindow& window) override;

    // Update the player
    void drawable_update() override;

    // Return visual
    std::string drawable_get_visual() override;

    // Set gravity (for debugging)
    void player_set_static(bool boolean);

    void input_cooldown();

    // Handles all input events
    void player_input(sf::Event event);

    // Return dead variable
    int player_get_dead();

    // Set dead variable
    void player_set_dead(int new_dead);

    // Respawn the player
    void player_respawn();
    // Collision detection between a player and a sf::FloatRect
    bool player_collision(Drawable* object);
	//check if player hitbox intersect with object mainly used for portal detection
    bool player_intersect(sf::FloatRect collide);



};



#endif