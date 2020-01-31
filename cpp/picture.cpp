#include "drawables.hpp"

// picture.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the picture subclass

// Constructor that stores the given location, size and link to the texture
Picture::Picture(sf::Vector2f location, sf::Vector2f size, std::string link) :
	Drawable(location, size, "PICTURE", "none"),
	size(size),
	link(link)
{
	// Loads the texture from the given link, sets the texture for the sprite and sets the sprites position
	texture.loadFromFile(link);
	sprite.setTexture(texture);
	sprite.setPosition(location);
	picture_set_size(size);
}

// Constructor that stores the given location,size, link to the texture and a specific name for the object
Picture::Picture(sf::Vector2f location, sf::Vector2f size, std::string link, std::string name) :
	Drawable(location, size, name, "none"),
	size(size),
	link(link)
{
	// Loads the texture from the given link, sets the texture for the sprite and sets the sprites position
	texture.loadFromFile(link);
	sprite.setTexture(texture);
	sprite.setPosition(location);
	picture_set_size(size);
}


// Sets picture size
void Picture::picture_set_size(sf::Vector2f new_size) {
	size = sf::Vector2f( float(texture.getSize().x), float(texture.getSize().y) );
	sf::Vector2f new_factor((new_size.x / size.x),
	(new_size.y / size.y));
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

// Sets picture scale
void Picture::picture_set_scale(sf::Vector2f scale) { sprite.setScale(scale); }

// Returns picture scale
sf::Vector2f Picture::picture_get_scale() { return sprite.getScale(); }

// Sets picture offset
void Picture::picture_set_offset(sf::Vector2f new_offset) { offset = new_offset; };

// Sets picture color
void Picture::picture_set_color(sf::Color color) { sprite.setColor(color); }

// Sets rotation of picture
void Picture::picture_set_rotation(float rotation) { sprite.setRotation(rotation); }

// Sets origin of picture
void Picture::picture_set_origin(sf::Vector2f origin) { sprite.setOrigin(origin); }