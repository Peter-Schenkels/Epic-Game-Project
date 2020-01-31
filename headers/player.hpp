#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

// player.hpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains the pPlayer class, a subclass of Drawable


#include "drawables.hpp"
#include "player_hitbox.hpp"
#include "animation_controller.hpp"


// Class for the player character
class Player : public Drawable {
private:
    sf::Vector2f speed = { 0, 0 };
    // Picture for the player character
    Picture* body;
    Player_Hitbox collision_box;
    sf::Vector2f respawn_location = { 0, 0 } ;
    sf::Clock timer;
    // Set strength of graity
    float gravity = 0.5;
    float resistance = 2;
    // Bools to select whether gravity even applied and whether the player is standing on solid ground
    bool floating = false;
    bool on_ground = false;
    int dead = 0;
    // Amount of pixel for initial jump update
    float jump_speed = 10.5;
    // Variable used for flipping the body
    sf::Vector2f static_scale;
    // Walking animation
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

    // Prevent portal spamming
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

	// Check if player hitbox intersect with an object, meant for portals as not to cancel existing momentum
    bool player_intersect(sf::FloatRect collide);
};



#endif