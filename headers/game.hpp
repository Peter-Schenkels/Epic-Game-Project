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
#include "portal.hpp"

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
	Animation walking_animation_left;
	Animation walking_animation_right;
	Animation idle_animation;
	Animation portal_animation_purple;
	Animation portal_animation_green;
	Linked_Portals portal_set{ p1, p2 };


	// Create a list filled with all drawable objects read from input
	bool edit = false;

public:
	Game(sf::RenderWindow& window) :
		window(window)
	{
		std::cout << "Loading Textures..." << std::endl;
		{
			textures["Player Texture"] = new Picture({ 10,10 }, { 100,100 }, "img/wovo idle.png");
			{
				textures["backdrop 1"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 1.png");
				textures["backdrop 2"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 2.png");
			}
			{
				textures["Portal 1"] = new Picture({ 0,0 }, { 100,100 }, "img/test2.jpg");
				textures["Portal 2"] = new Picture({ 0,0 }, { 100,100 }, "img/test3.jpeg");
			}
			{
				textures["walk1"] = new Picture({ {0,0}, {46, 126}, "img/walking1.png" });
				textures["walk2"] = new Picture({ {0,0}, {46, 126}, "img/walking2.png" });
				textures["walk3"] = new Picture({ {0,0}, {46, 126}, "img/walking3.png" });
				textures["walk4"] = new Picture({ {0,0}, {46, 126}, "img/walking4.png" });
				textures["walk5"] = new Picture({ {0,0}, {46, 126}, "img/walking5.png" });
				textures["walk6"] = new Picture({ {0,0}, {46, 126}, "img/walking6.png" });
				textures["walk7"] = new Picture({ {0,0}, {46, 126}, "img/walking7.png" });
			}
			{
				textures["left1"] = new Picture({ {0,0}, {46, 126}, "img/left1.png" });
				textures["left2"] = new Picture({ {0,0}, {46, 126}, "img/left2.png" });
				textures["left3"] = new Picture({ {0,0}, {46, 126}, "img/left3.png" });
				textures["left4"] = new Picture({ {0,0}, {46, 126}, "img/left4.png" });
				textures["left5"] = new Picture({ {0,0}, {46, 126}, "img/left5.png" });
				textures["left6"] = new Picture({ {0,0}, {46, 126}, "img/left6.png" });
				textures["left7"] = new Picture({ {0,0}, {46, 126}, "img/left7.png" });
			}
				
			{
				textures["green1"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green1.png" });
				textures["green2"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green2.png" });
				textures["green3"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green3.png" });
				textures["green4"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green4.png" });
				textures["green5"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green5.png" });
				textures["green6"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green6.png" });
				textures["green7"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green7.png" });
				textures["green8"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green8.png" });
				textures["green9"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green9.png" });
				textures["green10"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green10.png" });
				textures["green11"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green11.png" });
				textures["green12"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green12.png" });
			}
			{
				textures["purple1"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple1.png" });
				textures["purple2"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple2.png" });
				textures["purple3"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple3.png" });
				textures["purple4"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple4.png" });
				textures["purple5"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple5.png" });
				textures["purple6"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple6.png" });
				textures["purple7"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple7.png" });
				textures["purple8"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple8.png" });
				textures["purple9"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple9.png" });
				textures["purple10"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple10.png" });
				textures["purple11"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple11.png" });
				textures["purple12"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple12.png" });
			}
		}
		{
			portal_animation_purple = Animation(textures, { 64, 128 },
				{ "purple1", "purple2", "purple3", "purple4", "purple5", "purple6", "purple7", "purple8", "purple9", "purple10", "purple11", "purple12" },
				"Idle", 50);

			portal_animation_green = Animation(textures, { 64, 128 },
				{ "green1", "green2", "green3", "green4", "green5", "green6", "green7", "green8", "green9", "green10", "green11", "green12"},
				"Idle", 50);

			walking_animation_left = Animation(textures, { 46 , 126 },
				{ "walk1", "walk2","walk3","walk4","walk5","walk6","walk7" }, "Walking left", 50);
			walking_animation_right = Animation(textures, { 46 , 126 },
				{ "left1","left2","left3","left4","left5","left6","left7" }, "Walking right", 50);
			idle_animation = Animation(textures, { 46, 126 }, { "Player Texture", "Player Texture" }, "Idle", 50);

		}


		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION_OVERWORLD);
		void_drawables = drawable_object_read(SAVE_FILE_LOCATION_VOID);
		std::cout << "Loading objects completed" << std::endl;

		tile_priority t1("backdrop 1", 2);
		tile_priority t2("backdrop 2", 1);

		backdrop = random_background_tiles(textures, { 100, 100 }, { t1, t2 });

		player = Player({ 100,100 }, { 46 , 126 }, textures["Player Texture"], { walking_animation_right, walking_animation_left, idle_animation });
		
		p1 = Portal({ 50, 50 }, { 64, 128 }, "TOP", { portal_animation_purple }, true);
		p2 = Portal({ 200, 150 }, { 64, 128 }, "RIGHT", { portal_animation_green }, false);

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
			for (auto drawable : void_drawables) {
				if (drawable->drawable_hitbox_contains_point(location) && selected == false) {
					drawable->drawable_select();
					selected = true;
				}
				else {
					drawable->drawable_deselect();
				}
			}
		}
		sf::sleep(sf::milliseconds(90));
	}

	void game_move_mouse(sf::Vector2f location) {
		if (overworld) {
			for (auto& drawable : drawables) {
				if (drawable->drawable_get_selected()) {
					drawable->drawable_set_position(location);
				}
			}
		}
		else {
			for (auto& drawable : drawables) {
				if (drawable->drawable_get_selected()) {
					drawable->drawable_set_position(location);
				}
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
			for (auto& drawable : drawables) {
				if (drawable->drawable_get_selected()) {
					drawable->drawable_move(moves[entry.key.code]);
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

	// Move the edit camera using labda's
	void view_move_key(sf::Event& entry) {
		std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Down, sf::Vector2f{ 0, 10 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Left, sf::Vector2f{ -10, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Up, sf::Vector2f{ 0, -10 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Right, sf::Vector2f{ 10, 0 }));

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
			else if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::LControl) {
				// Switch dimensions
				overworld = !overworld;
				if (overworld) {
					backdrop.set_color({ 255,255,255,255 });
				} else {
					backdrop.set_color({ 100,255,100,255 });
				}
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
		player_view.move(delta);
		
		if (!edit) {
			window.setView(player_view);	
		}
		else {
			window.setView(game_edit_view);
		}

		// Collide with portals
		if (player.player_collision(&p1)) {
			portal_set.linked_portals_teleport(player, p1);

		}
		else if (player.player_collision(&p2)) {
			portal_set.linked_portals_teleport(player, p2);
		}
		p1.drawable_update();
		p2.drawable_update();
	}


	void game_draw() {
		window.clear();
		backdrop.draw(window);

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

		player.drawable_draw(window);
		window.display();
	}
};



#endif