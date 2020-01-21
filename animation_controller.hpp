#pragma once
#include <array>

#include "drawables.hpp"

template <int S>
class Animation {

	std::array<Picture*, S> frames;

public:

	Animation(std::array<Picture*, S> frames) :
		frames(frames)
	{}

	// Return frame number
	Picture* get_frame(uint_fast16_t frame_number) {
		if (frame_number < S) {
			return frames[frame_number];
		} else {
			std::cout << "Out of bound" << std::endl;
			return frames[0];
		}

	}

	void draw(sf::RenderWindow & window) {
		frames[0]->drawable_draw(window);
	}



};