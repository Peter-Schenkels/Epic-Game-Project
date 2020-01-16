#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "factory.hpp"
#include "settings.hpp"
#include "linked_portals.hpp"
#include "background_tile.hpp"


class Game {
protected:
	std::vector<Drawable*> drawables;
	sf::RenderWindow & window;
	std::map<std::string, Picture*> textures;
	random_background_tiles backdrop;
	Player player;


	// Create a list filled with all drawable objects read from input
	bool edit = false;

public:
	Game(sf::RenderWindow& window) :
		window(window),
		player({ 100,0 }, { 46 , 126 })
	{
		std::cout << "Loading Textures..." << std::endl;
		textures["Player Texture"] = new Picture({ 10,10}, { 100,100 }, "img/wovo idle.png");
		textures["backdrop 1"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 1.png");
		textures["backdrop 2"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 2.png");
		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION);
		std::cout << "Loading objects completed" << std::endl;
		backdrop = random_background_tiles(textures, { 100, 100 }, { "backdrop 1", "backdrop 2" });
		player.player_init(textures["Player Texture"]);

	}
	
	
	void game_set_edit(bool setting) {
		edit = setting;
		sf::sleep(sf::milliseconds(90));
	}

	bool game_get_edit() {
		return edit;
	}

	void game_select(sf::Vector2f location) {
		std::cout << "selected\n";
		bool selected = false;
		for (auto drawing : drawables) {
			if (drawing->drawable_hitbox_contains_point(location) && selected == false) {
				drawing->drawable_select();
				selected = true;
			}
			else {
				drawing->drawable_deselect();
			}
		}
		sf::sleep(sf::milliseconds(90));
	}

	void game_move_mouse(sf::Vector2f location) {
		for (auto& drawing : drawables) {
			if (drawing->drawable_get_selected()) {
				drawing->drawable_set_position(location);
			}
		}
	}

	void game_move_key(sf::Event& entry) {
		std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::W, sf::Vector2f{ 0, 1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::A, sf::Vector2f{ -1, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::S, sf::Vector2f{ 0, -1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::D, sf::Vector2f{ 1, 0 }));

		for (auto& drawing : drawables) {
			if (drawing->drawable_get_selected()) {
				drawing->drawable_move(moves[entry.key.code]);
			}
		}
	}

	std::vector<Drawable*> game_get_drawables() {
		return drawables;
	}

	void game_get_input() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && edit) {
			// Select the object the mouse left-clicks on
			sf::Vector2f location{ float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };
			game_select(location);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && edit) {
			// If an object has been selected by left-clicking, right-clicking will move this object
			// to where right-click has been pressed
			sf::Vector2f location{ float(int(sf::Mouse::getPosition(window).x / 50) * 50), 
				float(int(sf::Mouse::getPosition(window).y / 50) * 50)};
			game_move_mouse(location);
		}
		
		sf::Event key_press;
		if (window.pollEvent(key_press)) {
			player.player_input(key_press);
			if (key_press.type == sf::Event::Closed) {
				// If the window has been close, save the new objects to a file
				drawable_object_write(SAVE_FILE_LOCATION, game_get_drawables());
				window.close();
			}
			else if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::K) {
				// Change in and out of edit mode
				edit = !edit;
				for (auto& drawing : drawables) {
					drawing->drawable_deselect();
				}
			}
			else if (key_press.type == sf::Event::KeyPressed) {
				// Move something with WASD
				auto key = key_press.key.code;
				if (key == sf::Keyboard::W || key == sf::Keyboard::A || key == sf::Keyboard::S ||
					key == sf::Keyboard::D) {
					game_move_key(key_press);
				}
			}
		}	
	}

	void game_update() {

		player.drawable_update();
		for (auto Drawable : drawables) {
			Drawable->drawable_update();
			player.player_collision(Drawable);
		}
	}


	void game_draw() {
		window.clear();
		backdrop.draw(window);
		player.drawable_draw(window);
		for (auto Drawable : drawables) {

			Drawable->drawable_draw(window);
		}
		window.display();
	}
};



#endif