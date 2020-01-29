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

	
public:
	// Default constructor
	Portal() {}

	// Constructor
	Portal(sf::Vector2f position, sf::Vector2f size, std::string entrance, std::vector<Animation> animations, bool order) :
		Drawable(position, size, "Portal", "White"),
		entrance(entrance),
		animation_controller(animations),
		order(order),
		portal_size(size)
	{
		portal_align();
	}

	// Draw portal
	void drawable_draw(sf::RenderWindow& window) override {
		body = animation_controller.get_frame();
		body->drawable_draw(window);
		// The commented part is for debugging: showing the portals' hitbox
		/*sf::RectangleShape hitbox_draw(sf::Vector2f(hitbox.width, hitbox.height));
		hitbox_draw.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
		hitbox_draw.setFillColor(sf::Color::White);
		window.draw(hitbox_draw);*/
	}

	// Return visual
	std::string drawable_get_visual() { return color; }

	// Update portal
	void drawable_update() {
		animation_controller.update();
		body->drawable_set_position(location);
		body->drawable_update();
		//std::cout << location.x << " " << location.y << std::endl;
		hitbox = sf::FloatRect(location.x -16 , location.y -16 , 32 , 32);

	}

	// Set entrance
	void portal_set_entrance(std::string new_entrance) {
		entrance = new_entrance;
	}

	// Return doorway
	std::string portal_get_entrance() {
		return entrance;
	}

	// Return order
	bool portal_get_order() {
		return order;
	}

	void portal_align() {
		float rotation;
		std::array<std::string, 4> orientations{ "RIGHT", "BOTTOM", "LEFT", "TOP" };

		for (unsigned int i = 0; i < 4; i++) {
			if (orientations[i] == entrance) {
				rotation = float(i * 90);
			}
		}
		animation_controller.animation_controller_set_state("Idle");
		animation_controller.animation_set_size("Idle", portal_size);
		animation_controller.set_origin_of_animation("Idle", {portal_size.x/4, portal_size.y/4});
		animation_controller.rotate_animation("Idle", rotation);
		body = animation_controller.get_frame();
	}
};

#endif