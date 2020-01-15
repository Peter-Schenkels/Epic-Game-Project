#include "drawables.hpp"

// picture.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1

// Contains all functions for the picture subclass

// Constructor that stores the given location and link to the texture
Picture::Picture(sf::Vector2f location, sf::Vector2f size, std::string link) :
	Drawable(location, size, "PICTURE", "none"),
	size(size),
	link(link)
{
	// Loads the texture from the given link, sets the texture for the sprite and sets the sprites position
	texture.loadFromFile(link);
	sprite.setTexture(texture);
	sprite.setPosition(location);

}

// Sets picture size
void Picture::picture_set_size(sf::Vector2f new_size) {

	sf::Vector2f current_factor = sprite.getScale();
	sf::Vector2f new_factor(current_factor.x * (new_size.x / texture.getSize().x),
	current_factor.y * (new_size.y / texture.getSize().y));

	sprite.setScale(new_factor);

}

// Draws the picture
void Picture::drawable_draw(sf::RenderWindow& window) {
	sprite.setPosition(location + offset);
	window.draw(sprite);
}

// Returns the link that the picture uses as texture
std::string Picture::drawable_get_visual() {
	return link;
}

// Update the picture
void Picture::drawable_update() {
	sprite.setPosition(location);
	hitbox = sf::FloatRect(location.x, location.y, drawable_get_size().x, drawable_get_size().y);

}