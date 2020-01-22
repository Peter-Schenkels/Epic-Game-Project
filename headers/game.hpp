#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "factory.hpp"
#include "settings.hpp"
#include "linked_portals.hpp"
#include "background_tile.hpp"
#include "player.hpp"
#include "portal_error.hpp"
#include "portal_bullet.hpp"

class Game {
protected:
	std::vector<Drawable*> drawables;
	sf::RenderWindow & window;
	std::map<std::string, Picture*> textures;
	random_background_tiles backdrop;
	Player player;
	Portal p1;
	Portal p2;
	Linked_Portals portal_set{p1, p2};
	bool done = false;

	// Create a list filled with all drawable objects read from input
	bool edit = false;

public:
	Game(sf::RenderWindow& window) :
		window(window),
		player({ 100,0 }, { 46 , 126 })
	{
		std::cout << "Loading Textures..." << std::endl;
		textures["Player Texture"] = new Picture({ 10,10 }, { 100,100 }, "img/wovo idle.png");
		textures["backdrop 1"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 1.png");
		textures["backdrop 2"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 2.png");
		textures["Portal 1"] = new Picture({ 0,0 }, { 100,100 }, "img/test2.jpg");
		textures["Portal 2"] = new Picture({ 0,0 }, { 100,100 }, "img/test3.jpeg");

		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION);
		std::cout << "Loading objects completed" << std::endl;
		tile_priority t1("backdrop 1", 2);
		tile_priority t2("backdrop 2", 1);
		backdrop = random_background_tiles(textures, { 100, 100 }, { t1, t2 });
		player.player_init(textures["Player Texture"]);

		p1 = Portal({ 200, 100 }, { 130, 5 }, textures["Portal 1"], "TOP", true);
		p2 = Portal({ 400, 100 }, { 130, 5 }, textures["Portal 2"], "LEFT", false);
		auto portal_hitbox = p1.drawable_get_hitbox();
		auto portal_hitbox2 = p2.drawable_get_hitbox();
		std::cout << portal_hitbox.top << " " << portal_hitbox.left << " " << portal_hitbox.height << " " << portal_hitbox.width << "\n";
		std::cout << portal_hitbox2.top << " " << portal_hitbox2.left << " " << portal_hitbox2.height << " " << portal_hitbox2.width << "\n";
	}
	
	
	// Change in and out of the edit-mode
	void game_set_edit(bool setting) {
		edit = setting;
		sf::sleep(sf::milliseconds(90));
	}

	// Return the current edit-mode
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
				float(int(sf::Mouse::getPosition(window).y / 50) * 50) };
			game_move_mouse(location);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			// Shoot portal when button left mouse is pressed
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			sf::Vector2f playerPos = player.drawable_get_location();
			playerPos.x += player.drawable_get_size().x / 2;
			playerPos.y += player.drawable_get_size().y / 2;
			Portal_Bullet bullet(playerPos, window.getSize(), mousePos);
			bool order = false;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				order = true;
			}
			try {
				auto data = bullet.portal_bullet_impact_calc(drawables, window);
				std::cout << data.second;
				portal_set.linked_portals_portal_set(data.first, data.second, order);
				//portal_set.linked_portals_print_portals();
			}
			catch (const std::exception & e) {
				std::cerr << e.what();
			}
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

	// Updates the game state
	void game_update() {
		// Collide with regular drawables
		player.drawable_update();
		for (auto drawable : drawables) {
			drawable->drawable_update();
			player.player_collision(drawable);
		}

		// Collide with portals
		if (player.player_collision(&p1)) {
			portal_set.linked_portals_teleport(player, p1);
		}
		else if (player.player_collision(&p2)) {
			portal_set.linked_portals_teleport(player, p2);
		}

		//std::cout << player.player_get_speed().x << ", " << player.player_get_speed().y << "\n";
		p1.drawable_update();
		p2.drawable_update();
		//sf::sleep(sf::milliseconds(500));
	}

	// Draws the game state
	void game_draw() {
		window.clear();
		backdrop.draw(window);
		player.drawable_draw(window);
		for (auto Drawable : drawables) {
			Drawable->drawable_draw(window);
		}

		p1.drawable_draw(window);
		p2.drawable_draw(window);
		window.display();
	}
};



#endif