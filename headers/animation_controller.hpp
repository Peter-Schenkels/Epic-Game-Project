#pragma once
#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP
#include <array>
#include "drawables.hpp"

// This class represents an animation made up of picture*
class Animation {
	std::vector<Picture*> frames;
	uint_fast16_t amount_of_frames = 0;
	int rate_in_ms;
	std::string name;
public:
	// Default Constructor
	Animation() {}

	Animation(
		std::map<std::string, Picture*>& resources,
		sf::Vector2f sprite_size,
		std::vector<std::string> names,
		std::string name,
		int rate_in_ms

	) : name(name),
		rate_in_ms(rate_in_ms)
	{
		//get all resources
		for (auto& name : names) {
			//also changes the size of global size, might be a problem for later
			//short term solution is to change every sprite size before drawing per object
			//TODO: check if it's more effecient to use 2 sprites instead of updating the sprite size
			resources[name]->picture_set_size(sprite_size);
			frames.push_back(resources[name]);
			amount_of_frames++;
		}

	}

	// Rotate the animation in a certain degree
	void rotate(float degrees) {

		for (auto& frame : frames) {
			frame->picture_set_rotation(degrees);
		}

	}

	// Return Picture* from animation
	Picture* get_frame(uint_fast16_t frame_number) {
		if (frame_number < amount_of_frames) {
			return frames[frame_number];
		}
		else {
			std::cout << "Out of bound" << std::endl;
			return frames[0];
		}

	}
	// Get refresh rate per frame
	int get_rate_in_ms() { return rate_in_ms; }

	// Return name of the animation
	std::string get_name() { return name; }

	// Get the amount of frames inside the animation
	uint_fast16_t get_amount_of_frames() {
		return amount_of_frames;
	}

	// Set origin of animation
	void set_origin(sf::Vector2f origin) {

		for (auto& frame : frames) {
			frame->picture_set_origin(origin);
		}

	}

	// Set size of animation
	void set_size(sf::Vector2f size) {

		for (auto& frame : frames) {
			frame->picture_set_size(size);
		}

	}

	void set_position(sf::Vector2f new_position) {

		for (auto& frame : frames) {
			frame->drawable_set_position(new_position);
		}

	}

};


// This class is used for animation controlling
class Animation_Controller {

	std::vector<Animation> animations;
	std::vector<std::string> states;
	sf::Clock clock;
	int current_animation = 0;
	int current_frame = 0;

public:

	// Default constructor
	Animation_Controller() {}

	// Animation Controller
	// Input a vector of Animation_States
	Animation_Controller(std::vector<Animation> animations) :
		animations(animations)
	{
		clock.restart();
	}

	// Change animation of the animation controller
	void animation_controller_set_state(std::string state) {
		if (state != animations[current_animation].get_name()) {
			int index = 0;
			for (auto& animation : animations) {

				if (animation.get_name() == state) {
					current_animation = index;
					current_frame = 0;
					clock.restart();
					break;
				}
				index++;
			}
		}
	}

	void set_position(sf::Vector2f new_position) {
		animations[current_animation].set_position(new_position);
	}

	void rotate_animation(std::string name, float degrees) {

		for (auto & animation : animations) {

			if (animation.get_name() == name) {
				animation.rotate(degrees);
				return;
			}

		}
		std::cout << "Animation with the name: " << name << " was not found." << std::endl;

	}
	// Update alle the current animation
	void update() {
		if (clock.getElapsedTime().asMilliseconds() > animations[current_animation].get_rate_in_ms()) {
			current_frame++;
			if (current_frame == animations[current_animation].get_amount_of_frames()) {
				current_frame = 0;
			}
			clock.restart();
		}
	}

	void set_origin_of_animation(std::string name, sf::Vector2f origin) {
		for (auto& animation : animations) {

			if (animation.get_name() == name) {
				animation.set_origin(origin);
				return;
			}

		}
		std::cout << "Animation with the name: " << name << " was not found." << std::endl;

	}

	void animation_set_size(std::string name, sf::Vector2f size) {
		for (auto& animation : animations) {

			if (animation.get_name() == name) {
				animation.set_size(size);
				return;
			}

		}
		std::cout << "Animation with the name: " << name << " was not found." << std::endl;
	}

	// return current frame of the current animation
	Picture* get_frame() {
		return animations[current_animation].get_frame(current_frame);
	}
};




#endif