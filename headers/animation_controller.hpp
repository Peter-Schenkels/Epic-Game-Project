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

	// Animation constructor
	Animation(
		std::map<std::string, Picture*>& resources,
		sf::Vector2f sprite_size,
		std::vector<std::string> names,
		std::string name,
		int rate_in_ms
	);

	// Rotate the animation in a certain degree
	void rotate(float degrees);

	// Return Picture* from animation
	Picture* get_frame(uint_fast16_t frame_number);

	// Get refresh rate per frame
	int get_rate_in_ms();

	// Return name of the animation
	std::string get_name();

	// Get the amount of frames inside the animation
	uint_fast16_t get_amount_of_frames();

	// Set origin of animation
	void set_origin(sf::Vector2f origin);

	// Set size of animation
	void set_size(sf::Vector2f size);

	// Set postion of animation
	void set_position(sf::Vector2f new_position);

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
	Animation_Controller(std::vector<Animation> animations);

	// Change animation of the animation controller
	void animation_controller_set_state(std::string state);

	// Set position of current animation
	void set_position(sf::Vector2f new_position);

	// Rotateall animations
	void rotate_animation(std::string name, float degrees);

	// Update the current animation
	void update();

	// Set origin of the given animation
	void set_origin_of_animation(std::string name, sf::Vector2f origin);

	// Set size of the given animation
	void animation_set_size(std::string name, sf::Vector2f size);

	// return current frame of the current animation
	Picture* get_frame();

};




#endif