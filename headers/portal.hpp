#pragma once

#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "animation_controller.hpp"

// Class for each of the portals
class Portal : public Drawable {
protected:
	Picture* body;
	std::string entrance;
	Animation_Controller animation_controller;
	float rotation = 0;
	bool order;
	sf::Vector2f portal_size;
	bool placed = false;

	
public:
	// Default constructor
	Portal() {}

	// Constructor
	Portal(
		sf::Vector2f position, 
		sf::Vector2f size, 
		std::string entrance, 
		std::vector<Animation> animations, 
		bool order
	);

	// Draw portal
	void drawable_draw(sf::RenderWindow& window) override;

	// Return visual
	std::string drawable_get_visual() override;

	// Update portal
	void drawable_update() override;

	// To get first time placement
	bool portal_placed_get();
	// for first time placement
	void portal_placed_set(bool new_value);

	// Set entrance
	void portal_set_entrance(std::string new_entrance);

	// Return doorway
	std::string portal_get_entrance();

	// Return order
	bool portal_get_order();

	void portal_align();
};

#endif