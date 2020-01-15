#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "drawables.hpp"
#include "factory.hpp"
#include "settings.hpp"
<<<<<<< Updated upstream
#include "player.hpp"

=======
#include "linked_portals.hpp"
#include "background_tile.hpp"
>>>>>>> Stashed changes

class game {
protected:
	std::vector<drawable*> drawables;
	sf::RenderWindow & window;
<<<<<<< Updated upstream
	std::map<std::string, picture*> textures;
=======
	std::map<std::string, Picture*> textures;
	background_tiles backdrop;
>>>>>>> Stashed changes
	Player player;

	// Create a list filled with all drawable objects read from input
	bool edit = false;

public:
	game(sf::RenderWindow& window) :
		window(window),
		player({ 100,0 }, { 46 , 126 })
	{
		std::cout << "Loading Textures..." << std::endl;
<<<<<<< Updated upstream
		textures["Player Texture"] = new picture({ 10,10}, { 100,100 }, "test3.jpeg");
		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION);
		std::cout << "Loading objects completed" << std::endl;

		player.init(textures["Player Texture"]);
=======
		textures["Player Texture"] = new Picture({ 10,10}, { 100,100 }, "img/wovo idle.png");
		textures["Backdrop 1"] = new Picture({ 10, 10 }, { 100, 100 }, "img/backdrop 1.png");
		textures["Backdrop 2"] = new Picture({ 10, 10 }, { 100, 100 }, "img/backdrop 2.png");
		backdrop = background_tiles(textures["Backdrop 1"], { 100,100 });
		player.player_init(textures["Player Texture"]);
 		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION);
		std::cout << "Loading objects completed" << std::endl;


>>>>>>> Stashed changes

	}
	
	
	void set_edit(bool setting) {
		edit = setting;
		sf::sleep(sf::milliseconds(90));
	}

	bool get_edit() {
		return edit;
	}

	void select(sf::Vector2f location) {
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

	void move_mouse(sf::Vector2f location) {
		for (auto& drawing : drawables) {
			if (drawing->drawable_get_selected()) {
				drawing->drawable_set_position(location);
			}
		}
	}

	void move_key(sf::Event& entry) {
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

	std::vector<drawable*> get_drawables() {
		return drawables;
	}

	void get_input() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && edit) {
			// Select the object the mouse left-clicks on
			sf::Vector2f location{ float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };
			select(location);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && edit) {
			// If an object has been selected by left-clicking, right-clicking will move this object
			// to where right-click has been pressed
			sf::Vector2f location{ float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };
			move_mouse(location);
		}
		
		sf::Event key_press;
		if (window.pollEvent(key_press)) {
			player.input(key_press);
			if (key_press.type == sf::Event::Closed) {
				// If the window has been close, save the new objects to a file
				drawable_object_write(SAVE_FILE_LOCATION, get_drawables());
				window.close();
			}
			else if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::K) {
				// Change in and out of edit mode
				edit = !edit;
			}
			else if (key_press.type == sf::Event::KeyPressed) {
				// Move something with WASD
				auto key = key_press.key.code;
				if (key == sf::Keyboard::W || key == sf::Keyboard::A || key == sf::Keyboard::S ||
					key == sf::Keyboard::D) {
					move_key(key_press);
				}
			}
		}
		
	}

	void update() {

		player.drawable_update();
		for (auto Drawable : drawables) {
			Drawable->drawable_update();
			player.collision(Drawable);
		}
	}


	void draw() {
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