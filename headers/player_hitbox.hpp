#pragma once

#ifndef PLAYER_HITBOX
#define PLAYER_HITBOX

// player_hitbox.hpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains Player_Hitbox class


#include "drawables.hpp"


// Class used for creating a hitbox that differentiates between different sides and its insides
class Player_Hitbox {
private:
	sf::Vector2f position, size;
	// Hitboxes for all sides and insides
	sf::RectangleShape left, right, top, bottom, core, touch;
	sf::RectangleShape box;

public:
	// Default Constructor
	Player_Hitbox() {}

	// Constructor
	Player_Hitbox(sf::Vector2f position, sf::Vector2f size);

	
	// Update the hitbox
	void Player_Hitbox_update(sf::Vector2f pposition);

	// Draw the hitbox
	void Player_Hitbox_draw(sf::RenderWindow& window);

	// Check whether this certain part of the hitbox intersects with an object
	bool Player_Hitbox_left_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_right_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_top_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_bottom_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_core_intersect(sf::FloatRect collider);

	bool Player_Hitbox_touch_intersect(sf::FloatRect collider);

	// Returns outerbounds of the hitbox
	sf::FloatRect Player_Hitbox_get_outerbounds();
};


#endif