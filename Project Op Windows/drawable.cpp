#include "drawables.hpp"

// drawable.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1

// Contains all functions for the drawable superclass

// Constructor for drawable objects that use a size parameter
<<<<<<< Updated upstream
drawable::drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string color) :
	location(location),
=======
Drawable::Drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string color) :
	position(location),
>>>>>>> Stashed changes
	hitbox({ location.x, location.y, size.x, size.y }),
	type(type),
	selected(false),
	color(color)
{}



// Constructor for drawable objects that use a radius parameter
<<<<<<< Updated upstream
drawable::drawable(sf::Vector2f location, float radius, std::string type, std::string color) :
	location(location),
	hitbox({ location.x, location.y, radius * 2, radius * 2 }),
=======
Drawable::Drawable(sf::Vector2f position, float radius, std::string type, std::string color) :
	position(position),
	hitbox({ position.x, position.y, radius * 2, radius * 2 }),
>>>>>>> Stashed changes
	type(type),
	selected(false),
	color(color)
{}


// Returns whether the object has been selected by the user or not
bool drawable::drawable_get_selected() {
	return selected;
}

// Returns the location of the object
<<<<<<< Updated upstream
sf::Vector2f drawable::drawable_get_location() {
	return location;
=======
sf::Vector2f Drawable::drawable_get_location() {
	return position;
>>>>>>> Stashed changes
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
	position += delta;
}

// Set position
<<<<<<< Updated upstream
void drawable::drawable_set_position(sf::Vector2f position) {
	auto new_position = sf::Vector2f(float(int(position.x / 30.0) * 30.0), float(int(position.y / 30.0) * 30.0));
	hitbox.left = new_position.x;
	hitbox.top = new_position.y;
	location = new_position;
=======
void Drawable::drawable_set_position(sf::Vector2f new_position) {
	hitbox.left = new_position.x;
	hitbox.top = new_position.y;
	position = new_position;
>>>>>>> Stashed changes
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