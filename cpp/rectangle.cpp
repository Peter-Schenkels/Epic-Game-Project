#include "drawables.hpp"

// rectangle.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the rectangle subclass


// Constructor for the rectangle class that stores the given location, size and color for the rectangle
Rectangle::Rectangle(sf::Vector2f location, sf::Vector2f size, Picture* sprite) :
	Drawable(location, size, "RECTANGLE", color),
	size(size),
	sprite(sprite)
{
	sprite->picture_set_size(size);
}


// Returns the object color
std::string Rectangle::drawable_get_visual() {
	return sprite->drawable_get_visual();
}

// Draw the object
void Rectangle::drawable_draw(sf::RenderWindow& window) {
	sprite->drawable_set_position(next_position);
	sprite->drawable_draw(window);
}

// Update the object
void Rectangle::drawable_update() {
	sprite->drawable_set_position(location);
	next_position = location;
}