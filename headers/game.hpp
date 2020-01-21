#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <exception>
#include "drawables.hpp"
#include "factory.hpp"
#include "settings.hpp"
#include "linked_portals.hpp"
#include "background_tile.hpp"
#include "player.hpp"
#include "portal_error.hpp"
#include "portal_bullet.hpp"
#include "animation_controller.hpp"

class Game {
protected:
	bool overworld = true;
	std::vector<Drawable*> drawables;
	std::vector<Drawable*> void_drawables;
	sf::RenderWindow & window;
	std::map<std::string, Picture*> textures;
	random_background_tiles backdrop;
	Player player;
	Portal p1;
	Portal p2;
	sf::View player_view = { { 960,540 },  { 1920, 1080 } };
	sf::View game_edit_view = { { 960,540 },  { 1920, 1080 } };

	// Create a list filled with all drawable objects read from input
	bool edit = false;

public:
	Game(sf::RenderWindow& window) :
		window(window),
		player({ 0,0 }, { 46 , 126 })
	{
		std::cout << "Loading Textures..." << std::endl;
		textures["Player Texture"] = new Picture({ 10,10}, { 100,100 }, "img/wovo idle.png");
		textures["backdrop 1"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 1.png");
		textures["backdrop 2"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 2.png");
		textures["Portal 1"] = new Picture({ 0,0 }, { 100,100 }, "img/test2.jpg");
		textures["Portal 2"] = new Picture({ 0,0 }, { 100,100 }, "img/test3.jpeg");
		textures["walk1"] = new Picture({ {0,0}, {46, 126}, "img/walking1.png" });
		textures["walk2"] = new Picture({ {0,0}, {46, 126}, "img/walking2.png" });
		textures["walk3"] = new Picture({ {0,0}, {46, 126}, "img/walking3.png" });
		textures["walk4"] = new Picture({ {0,0}, {46, 126}, "img/walking4.png" });
		textures["walk5"] = new Picture({ {0,0}, {46, 126}, "img/walking5.png" });
		textures["walk6"] = new Picture({ {0,0}, {46, 126}, "img/walking6.png" });
		textures["walk7"] = new Picture({ {0,0}, {46, 126}, "img/walking7.png" });


		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION_OVERWORLD);
		void_drawables = drawable_object_read(SAVE_FILE_LOCATION_VOID);
		std::cout << "Loading objects completed" << std::endl;

		tile_priority t1("backdrop 1", 2);
		tile_priority t2("backdrop 2", 1);

		backdrop = random_background_tiles(textures, player.drawable_get_location(), { t1, t2 });
		player.player_init(textures["Player Texture"]);
		p1 = Portal({ 50, 50 }, { 50, 50 }, textures["Portal 1"], "TOP");
		p2 = Portal({ 200, 150 }, { 75, 75 }, textures["Portal 2"], "TOP");

		sf::Vector2f player_position = player.drawable_get_location();

		player_view.setCenter(player_position);
		window.setView(player_view);

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

		// Edit overworld or Void depending on which dimension is displayed
		if (overworld) {
			for (auto drawable : drawables) {
				if (drawable->drawable_hitbox_contains_point(location) && selected == false) {
					drawable->drawable_select();
					selected = true;
				}
				else {
					drawable->drawable_deselect();
				}
			}
		}
		else {
			for (auto drawing : void_drawables) {
				if (drawing->drawable_hitbox_contains_point(location) && selected == false) {
					drawing->drawable_select();
					selected = true;
				}
				else {
					drawing->drawable_deselect();
				}
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
		if (overworld) {
			for (auto& drawables : drawables) {
				if (drawables->drawable_get_selected()) {
					drawables->drawable_move(moves[entry.key.code]);
				}
			}
		}
		else {
			for (auto& drawables : void_drawables) {
				if (drawables->drawable_get_selected()) {
					drawables->drawable_move(moves[entry.key.code]);
				}
			}
		}
	}


	void view_move_key(sf::Event& entry) {
		std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Up, sf::Vector2f{ 0, 1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Left, sf::Vector2f{ -1, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Down, sf::Vector2f{ 0, -1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Right, sf::Vector2f{ 1, 0 }));

		game_edit_view.move(moves[entry.key.code]);
	}

	std::vector<Drawable*> game_get_drawables() {
		return drawables;
	}

	void game_get_input() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && edit) {
			// Select the object the mouse left-clicks on
			sf::Vector2i location{
				int(sf::Mouse::getPosition(window).x),
				int(sf::Mouse::getPosition(window).y) };
			game_select(window.mapPixelToCoords(location));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && edit) {
			// If an object has been selected by left-clicking, right-clicking will move this object
			// to where right-click has been pressed
			sf::Vector2i location{ 
				int(int(sf::Mouse::getPosition(window).x / 50) * 50), 
				int(int(sf::Mouse::getPosition(window).y / 50) * 50)};

		
			game_move_mouse(window.mapPixelToCoords(location));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Shoot portal when button left mouse is pressed
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			sf::Vector2f playerPos = player.drawable_get_location();
			playerPos.x += player.drawable_get_size().x / 2;
			playerPos.y += player.drawable_get_size().y / 2;
			Portal_bullet bullet(playerPos, window.getSize(), mousePos);
	/*		try {

				bullet.portal_bullet_impact_calc(drawables, window);
			}
			catch (const std::exception & e) {
				std::cerr << e.what();
			}*/
		}
		
		sf::Event key_press;
		if (window.pollEvent(key_press)) {
			player.player_input(key_press);
			if (key_press.type == sf::Event::Closed) {
				// If the window has been close, save the new objects to a file
				drawable_object_write(SAVE_FILE_LOCATION_OVERWORLD, drawables);
				drawable_object_write(SAVE_FILE_LOCATION_VOID, void_drawables);
				window.close();
			} 
			else if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::K) {
				// Change in and out of edit mode
				edit = !edit;
				for (auto& drawing : drawables) {
					drawing->drawable_deselect();
				}
			}
			else if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::Q) {
				// Switch dimensions
				overworld = !overworld;
			}
			else if (key_press.type == sf::Event::KeyPressed) {
				// Move something with WASD
				auto key = key_press.key.code;
				if (key == sf::Keyboard::Up || key == sf::Keyboard::Left|| key == sf::Keyboard::Down ||
					key == sf::Keyboard::Right) {
					view_move_key(key_press);
				}
			}
		}	
	}

	void game_update() {
		sf::Vector2f delta = player.drawable_get_location();
		player.drawable_update();

		// Update Overworld or Void depending one overworld boolean
		if (overworld) {
			for (auto drawable : drawables) {
				drawable->drawable_update();
				player.player_collision(drawable);
			}
		}
		else {
			for (auto drawable : void_drawables) {
				drawable->drawable_update();
				player.player_collision(drawable);
			}
		}
		delta = player.drawable_get_location() - delta;
		p1.drawable_update();
		p2.drawable_update();
		player_view.move(delta);
		
		if (!edit) {

			window.setView(player_view);	
		}
		else {
			window.setView(game_edit_view);
		}
	}


	void game_draw() {
		window.clear();
		backdrop.draw(window);
		player.drawable_draw(window);

		// Draw Overworld or Void depending one overworld boolean

		if (overworld) {
			for (auto Drawable : drawables) {
				Drawable->drawable_draw(window);
			}

			if (p1.drawable_get_dimension() == true) {
				p1.drawable_draw(window);
			} 

			if (p2.drawable_get_dimension() == true) {
				p2.drawable_draw(window);
			}
		} else {
			for (auto Drawable : void_drawables) {
				Drawable->drawable_draw(window);
			}
			if (p1.drawable_get_dimension() == false) {
				p1.drawable_draw(window);
			}

			if (p2.drawable_get_dimension() == false) {
				p2.drawable_draw(window);
			}
		}

		window.display();
	}
};



#endif