#pragma once
#ifndef PORTAL_BULLET_HPP
#define PORTAL_BULLET_HPP

// portal_bullet.hpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains the class for Portal_Bullet

#include "drawables.hpp"
#include "player_hitbox.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include "portal_error.hpp"
#include <exception>

// Class to calculate the trajectory of the bullet and the orientation the portal should have
class Portal_Bullet : public Drawable {
private:
	sf::Vector2f start_pos;
	sf::Vector2u window;
	Player_Hitbox collision_box;
	sf::Vector2f angle;
	sf::FloatRect hitbox;

public:
	Portal_Bullet(
		sf::Vector2f& pos_player, 
		sf::Vector2u windowSize, 
		sf::Vector2f& pos_mouse
	);


	// Function that draws the bullet
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns visual of the bullet
	std::string drawable_get_visual() override;

	// Update the bullet
	void drawable_update() override;

	// Function to calculate if a object will be hit in the bullet's trajectory 
	// and return the coordinates of the impact and the orientation of the portal
	std::pair<sf::Vector2f, std::string> portal_bullet_impact_calc(const std::vector<Drawable*>& drawables);
};


#endif