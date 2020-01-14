#include "drawables.hpp"

// drawable.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1

// Contains all functions for the drawable superclass

// Constructor for drawable objects that use a size parameter
drawable::drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string color) :
	location(location),
	hitbox({ location.x, location.y, size.x, size.y }),
	type(type),
	selected(false),
	color(color)
{}

// Constructor for drawable objects that use a radius parameter
drawable::drawable(sf::Vector2f location, float radius, std::string type, std::string color) :
	location(location),
	hitbox({ location.x, location.y, radius * 2, radius * 2 }),
	type(type),
	selected(false),
	color(color)
{}


// Returns whether the object has been selected by the user or not
bool drawable::drawable_get_selected() {
	return selected;
}

// Returns the location of the object
sf::Vector2f drawable::drawable_get_location() {
	return location;
}

// Select/deselect a drawable object
void drawable::drawable_select() {
	selected = true;
}

void drawable::drawable_deselect() {
	selected = false;
}

// Move object
void drawable::drawable_move(sf::Vector2f delta) {
	hitbox.left += delta.x;
	hitbox.top += delta.y;
	location += delta;
}

// Set position
void drawable::drawable_set_position(sf::Vector2f position) {
	hitbox.left = position.x;
	hitbox.top = position.y;
	location = position;
}

// Return the drawable type
std::string drawable::drawable_get_type() {
	return type;
}

// Return hitbox of object
sf::FloatRect drawable::drawable_get_hitbox() {
	return hitbox;
}

// Returns whether the hitbox contains a certain coordinate
bool drawable::drawable_hitbox_contains_point(sf::Vector2f point) {
	return hitbox.contains(point);
}

sf::Vector2f drawable::drawable_get_size() {
	return sf::Vector2f(hitbox.width, hitbox.height);
}