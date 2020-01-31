#include "animation_controller.hpp"

Animation_Controller::Animation_Controller(std::vector<Animation> animations) :
	animations(animations)
{
	clock.restart();
}

void Animation_Controller::animation_controller_set_state(std::string state) {
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

void Animation_Controller::set_position(sf::Vector2f new_position) {
	animations[current_animation].set_position(new_position);
}

void Animation_Controller::rotate_animation(std::string name, float degrees) {

	for (auto& animation : animations) {

		if (animation.get_name() == name) {
			animation.rotate(degrees);
			return;
		}

	}
	std::cout << "Animation with the name: " << name << " was not found." << std::endl;

}

void Animation_Controller::update() {
	if (clock.getElapsedTime().asMilliseconds() > animations[current_animation].get_rate_in_ms()) {
		current_frame++;
		if (current_frame == animations[current_animation].get_amount_of_frames()) {
			current_frame = 0;
		}
		clock.restart();
	}
}

void Animation_Controller::set_origin_of_animation(std::string name, sf::Vector2f origin) {
	for (auto& animation : animations) {

		if (animation.get_name() == name) {
			animation.set_origin(origin);
			return;
		}

	}
	std::cout << "Animation with the name: " << name << " was not found." << std::endl;

}

void Animation_Controller::animation_set_size(std::string name, sf::Vector2f size) {
	for (auto& animation : animations) {

		if (animation.get_name() == name) {
			animation.set_size(size);
			return;
		}

	}
	std::cout << "Animation with the name: " << name << " was not found." << std::endl;
}

Picture* Animation_Controller::get_frame() {
	return animations[current_animation].get_frame(current_frame);
}