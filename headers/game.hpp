#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <exception>
#include "drawables.hpp"
#include "factory.hpp"
#include "settings.hpp"
#include "linked_portals.hpp"
#include "tilemap.hpp"
#include "player.hpp"
#include "portal_error.hpp"
#include "portal_bullet.hpp"
#include "animation_controller.hpp"
#include "portal.hpp"
#include "load_textures.cpp"

class Game {
protected:
	// Which dimension is currently being displayed
	bool overworld = true;
	// Lists of drawable objects for each of the dimensions
	std::vector<Drawable*> drawables;
	std::vector<Drawable*> void_drawables;
	sf::RenderWindow & window;
	// Textures for the in-game sprites
	std::map<std::string, Picture*> textures;
	// The background for the 2d map
	TileMap map;
	Player player;
	// The field of view for the player
	sf::View player_view = { { 960,540 },  { 1920, 1080 } };
	sf::View game_edit_view = { { 960,540 },  { 1920, 1080 } };
	// The in-game animations
	Animation walking_animation_left;
	Animation walking_animation_right;
	Animation idle_animation;
	Animation portal_animation_purple;
	Animation portal_animation_green;
	// The portals
	Portal p1;
	Portal p2;
	Linked_Portals portal_set{ p1, p2 };
	// A map filled with keys and their effects
	std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
	// Boolean that shows whether the user can currently edit the world
	bool edit = false;

public:
	// Constructor
	Game(sf::RenderWindow& window) :
		window(window)
	{
		// Load all textures and animations
		load_textures(textures);
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

		// Load all drawable objects
		std::cout << "Loading objects..." << std::endl;
		drawables = drawable_object_read(SAVE_FILE_LOCATION_OVERWORLD, textures);
		void_drawables = drawable_object_read(SAVE_FILE_LOCATION_VOID, textures);
		std::cout << "Loading objects completed" << std::endl;

		// Create a random seed and set a range for the amount of different background textures
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, 255);

		// Create a list filled with random numbers using the previously defined seed and range
		int level[8160];
		for (unsigned int i = 0; i < 8160; i++) {
			level[i] = distr(eng);
		}

		// Loads map with textures using the random numbers from level
		map.load("img/backdrops3.png", sf::Vector2u(128, 128), level, 120, 68);

		// Fill the moves map with the correct keys
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Down, sf::Vector2f{ 0, 10 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Left, sf::Vector2f{ -10, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Up, sf::Vector2f{ 0, -10 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Right, sf::Vector2f{ 10, 0 }));
		
		// Creates a player and the portals
		player = Player({ 100,100 }, { 46 , 126 }, { walking_animation_right, walking_animation_left, idle_animation });
		p1 = Portal({ 50, 50 }, { 64, 128 }, "RIGHT", { portal_animation_purple }, true);
		p2 = Portal({ 200, 150 }, { 64, 128 }, "RIGHT", { portal_animation_green }, false);
	}

	// Changes whether the user can edit the level
	void game_set_edit(bool setting) {
		edit = setting;
	}

	// Returns whether the user can edit the level
	bool game_get_edit() {
		return edit;
	}

	// Selects which drawable item has to be moved by the level editor
	void game_select(sf::Vector2f location) {
		std::cout << "selected\n";
		bool selected = false;

		// Select a drawable item from the overworld or the void depending on which dimension is currently displayed
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
	}

	// Move the selected drawable object along with where the mouse is
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

	// Move the edit camera using lambdas for the arrow-keys
	void view_move_key(sf::Event& entry) {
		game_edit_view.move(moves[entry.key.code]);
	}

	// Return the list of drawables
	std::vector<Drawable*> game_get_drawables() {
		return drawables;
	}

	// Shoots portals
	void game_shoot_portal(bool order) {
		sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f player_position = player.drawable_get_location();
		// Change player_position so it's equal to the middle of the player
		player_position += {player.drawable_get_size().x / 2, player.drawable_get_size().y / 2};
		// Create a bullet to calculate the path and orientation for the new portal
		Portal_Bullet bullet(player_position, window.getSize(), mouse_position);

		// Calculate the position and orientation of the portal or catch an exception if something goes wrong
		try {
			std::pair<sf::Vector2f, std::string> data;
			// Run the calculation with the drawables from the current world
			if (overworld) {
				data = bullet.portal_bullet_impact_calc(drawables, window);
			}
			else {
				data = bullet.portal_bullet_impact_calc(void_drawables, window);
			}
			portal_set.linked_portals_portal_set(data.first, data.second, order, overworld);
		}
		catch (const std::exception & e) {
			std::cerr << e.what();
		}
	}

	// Act upon closed and key events
	void game_act_on_key(sf::Event key_event) {
		player.player_input(key_event);
		if (key_event.type == sf::Event::Closed) {
			// If the window has been close, save the new objects to a file
			drawable_object_write(SAVE_FILE_LOCATION_OVERWORLD, drawables);
			drawable_object_write(SAVE_FILE_LOCATION_VOID, void_drawables);
			window.close();
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::K) {
			// Change in and out of edit mode and deselect all objects
			edit = !edit;
			for (auto& drawing : drawables) {
				drawing->drawable_deselect();
			}
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::LControl) {
			// Switch between dimensions
			overworld = !overworld;
		}
		else if (key_event.type == sf::Event::KeyPressed && edit) {
			// Move around the editing view with the arrow keys
			auto key = key_event.key.code;
			if (key == sf::Keyboard::Up || key == sf::Keyboard::Left || key == sf::Keyboard::Down ||
				key == sf::Keyboard::Right) {
				view_move_key(key_event);
			}
		}
	}

	// Checks for certain inputs and acts accordingly
	void game_get_input() {
		// Left Pressed && edit: create location and game_select(window.mapPixeToCoords(location));
		// Right Pressed && edit: game_move_mouse(window.mapPixelToCoords(location));
		// Right/Left Pressed && !edit: Shoot portal
		// Check event: Closed, K = editmode, Ctrl = dimension, arrow-keys = move screen for edit

		if (edit) {
			// Select object when editing
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				auto location = sf::Mouse::getPosition(window);
				game_select(window.mapPixelToCoords(location));
			}
			// Move selected object around
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				auto location = sf::Mouse::getPosition(window);
				game_select(window.mapPixelToCoords(location));
			}
		}

		// Shoot the portal
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && !edit) {
			game_shoot_portal(sf::Mouse::isButtonPressed(sf::Mouse::Left));
		}
		
		// Check for all other events
		sf::Event key_event;
		if (window.pollEvent(key_event)) {
			game_act_on_key(key_event);
		}
	}

	// Updates the game staete
	void game_update() {
		player.drawable_update();

		// Update overworld or void depending on which one the player finds themselves currently in
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
		// Set the player_view
		player_view.setCenter(player.drawable_get_location());
		
		// Set the view to the one centered on the player when not editing
		// Otherwise set the view to whatever the editor is doing
		if (!edit) {
			window.setView(player_view);	
		}
		else {
			window.setView(game_edit_view);
		}
		
		// Intersect with portals and swap to the correct dimension
		if (player.player_intersect(p1.drawable_get_hitbox()) && overworld == p1.drawable_get_dimension()) {
			portal_set.linked_portals_teleport(player, p1);
			overworld = p2.drawable_get_dimension();
		}
		else if (player.player_intersect(p2.drawable_get_hitbox()) && overworld == p2.drawable_get_dimension()) {
			portal_set.linked_portals_teleport(player, p2);
			overworld = p1.drawable_get_dimension();
		}
		p1.drawable_update();
		p2.drawable_update();
	}

	// Draw the current game state
	void game_draw() {

		window.clear();
		// Draw the background first


		// Draw the drawable objects in the overworld or the void depending one which one the player finds themselves in
		if (overworld) {
			for (auto Drawable : drawables) {
				Drawable->drawable_draw(window);
			}
		} else {
			for (auto Drawable : void_drawables) {
				Drawable->drawable_draw(window);
			}
		}

		// Draw the currently visible portals
		if (p1.drawable_get_dimension() == overworld) {
			p1.drawable_draw(window);
		}
		if (p2.drawable_get_dimension() == overworld) {
			p2.drawable_draw(window);
		}

		player.drawable_draw(window);
		window.display();
	}
};


#endif