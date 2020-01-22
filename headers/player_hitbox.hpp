#pragma once

#ifndef PLAYER_HITBOX
#define PLAYER_HITBOX

#include "drawables.hpp"

class Player_Hitbox {
protected:
	sf::Vector2f position, size;
	sf::RectangleShape left, right, top, bottom, core;
	sf::RectangleShape box;

public:

	// Default Constructor
	Player_Hitbox() {}

	Player_Hitbox(sf::Vector2f position, sf::Vector2f size);

	void Player_Hitbox_update(sf::Vector2f pposition);

	void Player_Hitbox_draw(sf::RenderWindow& window);

	bool Player_Hitbox_left_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_right_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_top_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_bottom_side_intersect(sf::FloatRect collider);

	bool Player_Hitbox_core_intersect(sf::FloatRect collider);

	sf::FloatRect Player_Hitbox_get_outerbounds();
};


#endif