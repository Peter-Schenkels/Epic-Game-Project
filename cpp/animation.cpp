#include <animation_controller.hpp>

Animation::Animation(
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

void Animation::rotate(float degrees) {

	for (auto& frame : frames) {
		frame->picture_set_rotation(degrees);
	}

}

Picture* Animation::get_frame(uint_fast16_t frame_number) {
	if (frame_number < amount_of_frames) {
		return frames[frame_number];
	}
	else {
		std::cout << "Out of bound" << std::endl;
		return frames[0];
	}

}

int Animation::get_rate_in_ms() { return rate_in_ms; }


std::string Animation::get_name() { return name; }


uint_fast16_t Animation::get_amount_of_frames() {
	return amount_of_frames;
}

void Animation::set_origin(sf::Vector2f origin) {

	for (auto& frame : frames) {
		frame->picture_set_origin(origin);
	}

}

// Set size of animation
void Animation::set_size(sf::Vector2f size) {

	for (auto& frame : frames) {
		frame->picture_set_size(size);
	}

}

void Animation::set_position(sf::Vector2f new_position) {

	for (auto& frame : frames) {
		frame->drawable_set_position(new_position);
	}

}