#pragma once
#ifndef LEVEL_EDITOR_HPP
#define LEVEL_EDITOR_HPP
#include "drawables.hpp"

class Level_Editor {

	sf::RectangleShape menu;
	std::vector<Picture*> tiles;
	sf::Vector2f position;
	sf::RectangleShape crosshair;

public:
	Level_Editor() {}

	Level_Editor(std::map<std::string, Picture*>& resources, std::vector<std::string> names) :
		menu({ 1920, 500 }),
		position({ 0, 0 }),
		crosshair({100,100})
	{
		int i = 0;
		for (auto& name : names) {
			//also changes the size of global size, might be a problem for later
			//short term solution is to change every sprite size before drawing per object
			//TODO: check if it's more effecient to use 2 sprites instead of updating the sprite size
			tiles.push_back(resources[name]);
			resources[name]->drawable_set_name(name);
		}
		crosshair.setOutlineThickness(2);
		crosshair.setFillColor({ 000,000,000,000 });
	}

	// Set position of the level editor
	void set_position(sf::Vector2f new_position) {

		position = new_position;
		menu.setPosition({ new_position.x - 960, new_position.y + 100 });
		sf::Vector2f position = { new_position.x - 920, new_position.y + 120 };
		for (auto& tile : tiles) {

			if (position.x > new_position.x + 800) {
				position.y = position.y + 120;
				position.x = new_position.x - 920;
			}
			tile->drawable_set_position(position);
			position.x += 150;

		}
		crosshair.setPosition(float(int(new_position.x / 100) * 100), float(int(new_position.y / 100) * 100));

	}

	// get input for level editor
	void get_input(std::vector<Drawable*>& overworld_drawables, std::vector<Drawable*>& void_drawables, bool& overworld, sf::Vector2f location) {

		for (auto& tile : tiles) {

			if (tile->drawable_get_hitbox().contains(location)) {
				Drawable* new_tile = new Rectangle({ float(int(position.x / 100) * 100), float(int(position.y / 100) * 100) }, tile->drawable_get_size(), tile);
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

	sf::FloatRect get_hitbox() {
		return menu.getGlobalBounds();
	}

	void draw(sf::RenderWindow& window) {

		window.draw(menu);
		for (auto& tile : tiles) {
			tile->drawable_draw(window);
		}
		window.draw(crosshair);

	}

	void update() {};

};




#endif // !LEVEL_EDITOR_HPP
