#pragma once

#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "animation_controller.hpp"

// Class for each of the portals
class Portal : public Drawable {
protected:
	Picture* body;
	std::string orientation;
	std::string doorway;
	Animation_Controller animation_controller;
	float rotation = 0;



public:
	// Default constructor
	Portal() {}

	// Constructor
	Portal(sf::Vector2f position, sf::Vector2f size, Picture* sprite, std::string orientation, std::vector<Animation> animations) :
		Drawable(position, size, "Portal", "White"),
		body(sprite),
		orientation(orientation),
		animation_controller(animations)


	{
		float rotation;
		std::array<std::string, 4> orientations{ "TOP", "RIGHT", "BOTTOM", "LEFT" };

		for (unsigned int i = 0; i < 4; i++) {
			if (orientations[i] == orientation) {
				rotation = float(i * 90);
				if (i <= 1) {
					doorway = orientations[i + 2];
				}
				else {
					doorway = orientations[i - 2];
				}
			}
		}
		animation_controller.animation_controller_set_state("Idle");
		animation_controller.animation_set_size("Idle", size);
		animation_controller.set_origin_of_animation("Idle", {size.x/4, size.y/4});
		body->picture_set_size(size);
		body->picture_set_rotation(rotation);


	}

	void drawable_draw(sf::RenderWindow& window) override {
		body = animation_controller.get_frame();
		body->drawable_draw(window);
	}

	std::string drawable_get_visual() { return color; }

	void drawable_update() {
		animation_controller.rotate_animation("Idle", rotation++);
		animation_controller.update();
		body->drawable_set_position(location);
		body->drawable_update();
	}


	// Return doorway
	std::string portal_get_doorway() {
		return doorway;
	}

	// Return orientation
	std::string portal_get_orientation() {
		return orientation;
	}
};

#endif