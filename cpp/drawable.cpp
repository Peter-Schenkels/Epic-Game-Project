#include "drawables.hpp"

// drawable.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the drawable superclass

// Constructor for drawable objects that use a size parameter
Drawable::Drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string color) :
	location(location),
	hitbox({ location.x, location.y, size.x, size.y }),
	type(type),
	selected(false),
	color(color),
	in_over_world(true)
{}

// Constructor for drawable objects that use a radius parameter
Drawable::Drawable(sf::Vector2f location, float radius, std::string type, std::string color) :
	location(location),
	hitbox({ location.x, location.y, radius * 2, radius * 2 }),
	type(type),
	selected(false),
	color(color),
	in_over_world(true)
{}


// Returns whether the object has been selected by the user or not
bool Drawable::drawable_get_selected() {
	return selected;
}

// Returns the location of the object
sf::Vector2f Drawable::drawable_get_location() {
	return location;
}

// Select/deselect a drawable object
void Drawable::drawable_select() {
	selected = true;
}

void Drawable::drawable_deselect() {
	selected = false;
}

// Move object
void Drawable::drawable_move(sf::Vector2f delta) {
	hitbox.left += delta.x;
	hitbox.top += delta.y;
	location += delta;
}

// Set position
void Drawable::drawable_set_position(sf::Vector2f position) {
	hitbox.left = position.x;
	hitbox.top = position.y;
	location = position;
}

// Return the drawable type
std::string Drawable::drawable_get_type() {
	return type;
}

// Return hitbox of object
sf::FloatRect Drawable::drawable_get_hitbox() {
	return hitbox;
}

// Returns whether the hitbox contains a certain coordinate
bool Drawable::drawable_hitbox_contains_point(sf::Vector2f point) {
	return hitbox.contains(point);
}

// Returns size of object
sf::Vector2f Drawable::drawable_get_size() {
	return sf::Vector2f(hitbox.width, hitbox.height);
}

// Get dimension the object finds itself in
bool Drawable::drawable_get_dimension() {
	return in_over_world;
}

// Set dimension the object finds itself in
void Drawable::drawable_set_dimension(bool set) {
	in_over_world = set;
}

// Sets the name
void Drawable::drawable_set_name(std::string new_name) {
	name = new_name; 
}

// Gets the name
std::string Drawable::drawable_get_name() {
	return name; 
}