#pragma once
#ifndef LEVEL_EDITOR_HPP
#define LEVEL_EDITOR_HPP

// level_editor.hpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains class for editing levels


#include "drawables.hpp"

// Class for editing levels
class Level_Editor {
private:
	sf::RectangleShape menu;
	std::vector<Picture*> tiles;
	sf::Vector2f position;
	sf::RectangleShape crosshair;

public:
	// Default constructor of level_editor
	Level_Editor() {}

	// Constructor for level editor
	// Takes in a map with all available pictures in the game,
	// takes in a list of strings with all the available to the level_editor 
	// that the level should be able to place
	Level_Editor(
		std::map<std::string, Picture*>& resources, 
		std::vector<std::string> names
	);

	// Set position of the level editor
	void set_position(sf::Vector2f new_position);

	// get input for level editor
	void get_input(
		std::vector<Drawable*>& overworld_drawables, 
		std::vector<Drawable*>& void_drawables, 
		bool& overworld, 
		sf::Vector2f location
	);

	// Get Boundaries of the level editor
	sf::FloatRect get_hitbox();

	// Draws the level editor to a window
	void draw(sf::RenderWindow& window);
};


#endif // !LEVEL_EDITOR_HPP