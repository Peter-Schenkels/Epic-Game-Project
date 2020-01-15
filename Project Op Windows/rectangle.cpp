#include "drawables.hpp"

// rectangle.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1

// Contains all functions for the rectangle subclass

// Constructor for the rectangle class that stores the given location, size and color for the rectangle
rectangle::rectangle(sf::Vector2f location, sf::Vector2f size, std::string color) :
	drawable(location, size, "RECTANGLE", color),
	size(size)
{
	// Sets size, position and color of the rectangle to those that have been received through the constructor
	// COLORS EVERYWHERE NEED TO BE REPLACE BY TEXTURES - XXX DONIOL
	shape.setSize(size);
	shape.setPosition(location);
	if (color == "red") {
		shape.setFillColor({ 255, 0, 0 });
	}
	else if (color == "green") {
		shape.setFillColor({ 0, 255, 0 });
	}
	else if (color == "blue") {
		shape.setFillColor({ 0, 0, 255 });
	}
}


// Function that draws the rectangle
void rectangle::drawable_draw(sf::RenderWindow& window) {
	window.draw(shape);
}

// Returns color
std::string rectangle::drawable_get_visual() {
	return color;
}

// Update the rectangle
<<<<<<< Updated upstream
void rectangle::drawable_update() {
	shape.setPosition(location);
	hitbox = sf::FloatRect(location.x, location.y, drawable_get_size().x, drawable_get_size().y);
=======
void Rectangle::drawable_update() {
	shape.setPosition(position);
	hitbox = sf::FloatRect(position.x, position.y, drawable_get_size().x, drawable_get_size().y);
>>>>>>> Stashed changes

}