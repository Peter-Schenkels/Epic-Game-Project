#ifndef FACTORY_HPP
#define FACTORY_HPP
#pragma warning(disable : 4996)

// factory.hpp

// Functions for:
// - Reading objects from a file
// - Writing objects to a file

#include "drawables.hpp"

// Factory pattern
// reading in drawables from a json and exporting a vector<Drawable*> as result
std::vector<Drawable*> drawable_object_read(
	std::string link, 
	std::map<std::string, Picture*>& textures, 
	sf::Vector2f& start_position
);

// Factory pattern
// exporting drawables into a json file
void drawable_object_write(
	std::string link, 
	std::vector<Drawable*> drawables, 
	sf::Vector2f& start_position
);


#endif