#include "level_editor.hpp"

// level_editor.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the Level_Editor class


// Constructor
Level_Editor::Level_Editor(std::map<std::string, Picture*>& resources, std::vector<std::string> names) :
	menu({ 1920, 500 }),
	position({ 0, 0 }),
	crosshair({ 100,100 })
{
	int i = 0;
	for (auto& name : names) {
		tiles.push_back(resources[name]);
		resources[name]->drawable_set_name(name);
	}
	crosshair.setOutlineThickness(10);
	crosshair.setFillColor({ 000,000,000,000 });
}


// Set position of the level editor
void Level_Editor::set_position(sf::Vector2f new_position) {
	// Change position of the editor menu
	position = new_position;
	menu.setPosition({ new_position.x - 960, new_position.y + 100 });
	sf::Vector2f position = { new_position.x - 920, new_position.y + 120 };
	// Change position for every displayed block within the editor menu
	for (auto& tile : tiles) {
		if (position.x > new_position.x + 800) {
			position.y = position.y + 120;
			position.x = new_position.x - 920;
		}
		tile->drawable_set_position(position);
		position.x += 150;
	}
	// Adapt the crosshair to the new position
	crosshair.setPosition(float(int(new_position.x / 100) * 100), float(int(new_position.y / 100) * 100));
}

// Get input for level editor
void Level_Editor::get_input(std::vector<Drawable*>& overworld_drawables, std::vector<Drawable*>& void_drawables, 
	bool& overworld, sf::Vector2f location) {
	// Check for whether the user selects a new tile and if so create a copy
	for (auto& tile : tiles) {
		if (tile->drawable_get_hitbox().contains(location)) {
			Drawable* new_tile = new Rectangle({ float(int(position.x / 100) * 100), float(int(position.y / 100) * 100) }, 
				tile->drawable_get_size(), tile);
			std::cout << tile->drawable_get_name() << std::endl;
			new_tile->drawable_set_name(tile->drawable_get_name());
			if (overworld) {
				overworld_drawables.push_back(new_tile);
			}
			else {
				void_drawables.push_back(new_tile);
				std::cout << "daargaanwe\n";
			}
		}
	}
}

// Return the hitbox of the level_editor
sf::FloatRect Level_Editor::get_hitbox() {
	return menu.getGlobalBounds();
}

// Draw the level_editor menu and all tiles it contains
void Level_Editor::draw(sf::RenderWindow& window) {
	window.draw(menu);
	for (auto& tile : tiles) {
		tile->drawable_draw(window);
	}
	window.draw(crosshair);
}