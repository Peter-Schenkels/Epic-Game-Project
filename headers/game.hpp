#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <exception>
#include "SFML/Audio.hpp"
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
#include "level_editor.hpp"
#include "level_selector.hpp"
#include "screens.hpp"

class Game : public Screens {
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
	TileMap map_overworld;
	TileMap map_void;
	Player player;
	//Start position of player
	sf::Vector2f start_position; 
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
	// Sounds and music
	sf::Sound portal_shoot;
	sf::SoundBuffer portal_shoot_buffer;
	sf::Sound dimension_switch;
	sf::SoundBuffer dimension_switch_buffer;
	sf::Sound portal_teleport;
	sf::SoundBuffer portal_teleport_buffer;
	sf::Sound level_clear;
	sf::SoundBuffer level_clear_buffer;
	sf::Music level1_background;
	sf::Music level2_background;
	sf::Music level3_background;
	std::vector<sf::Music*> musicList;
	// A map filled with keys and their effects
	std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
	// Boolean that shows whether the user can currently edit the world
	bool edit = false;
	// Level editor
	Level_Editor level_editor = Level_Editor(textures, {});
	// Level Selector 
	Level_Selector level_selector = Level_Selector({
		{LOCATION_OVERWORLD_LEVEL_1, LOCATION_VOID_LEVEL_1 },
		{LOCATION_OVERWORLD_LEVEL_2, LOCATION_VOID_LEVEL_2 },
		{LOCATION_OVERWORLD_LEVEL_3, LOCATION_VOID_LEVEL_3 }
		});
	bool esc = false;
	bool new_music = true;

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
				{ "green1", "green2", "green3", "green4", "green5", "green6", "green7", "green8", "green9", "green10", "green11", "green12" },
				"Idle", 50);

			walking_animation_left = Animation(textures, { 46 , 126 },
				{ "walk1", "walk2","walk3","walk4","walk5","walk6","walk7" }, "Walking left", 50);
			walking_animation_right = Animation(textures, { 46 , 126 },
				{ "left1","left2","left3","left4","left5","left6","left7" }, "Walking right", 50);
			idle_animation = Animation(textures, { 46, 126 }, { "Player Texture", "Player Texture" }, "Idle", 50);

		}

		// Load all drawable objects
		std::cout << "Loading objects..." << std::endl;
		load_level();
		std::cout << "Loading objects completed" << std::endl;

		// Create a random seed and set a range for the amount of different background textures
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, 5);

		// Create a list filled with random numbers using the previously defined seed and range
		int level[8160];
		for (unsigned int i = 0; i < 8160; i++) {
			level[i] = distr(eng);
		}

		// Loads map with textures using the random numbers from level
		map_overworld.load("img/backdrops2.png", sf::Vector2u(100, 100), level, 120, 68);
		map_void.load("img/void_backdrops.png", sf::Vector2u(100, 100), level, 120, 68);

		// Fill the moves map with the correct keys
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Down, sf::Vector2f{ 0, 100 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Left, sf::Vector2f{ -100, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Up, sf::Vector2f{ 0, -100 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::Right, sf::Vector2f{ 100, 0 }));
		
		// Creates a player and the portals
		player = Player(start_position, { 46 , 126 }, { walking_animation_right, walking_animation_left, idle_animation });
		p1 = Portal({ 50, 50 }, { 64, 128 }, "RIGHT", { portal_animation_purple }, true);
		p2 = Portal({ 200, 150 }, { 64, 128 }, "RIGHT", { portal_animation_green }, false);

		// Creates the sound and music
		// Shoot sound
		if (!portal_shoot_buffer.loadFromFile("sounds/portal_shooting.ogg")) {
			std::cout << "Portal shooting sound not loaded\n";
		}
		portal_shoot.setBuffer(portal_shoot_buffer);

		// Portal teleport sound
		if (!portal_teleport_buffer.loadFromFile("sounds/portal_go_through.ogg")) {
			std::cout << "Portal teleport sound not loaded\n";
		}
		portal_teleport.setBuffer(portal_teleport_buffer);

		// Dimension switch sound
		if (!dimension_switch_buffer.loadFromFile("sounds/dimension_swap.ogg")) {
			std::cout << "Dimension switch sound not loaded\n";
		}
		dimension_switch.setBuffer(dimension_switch_buffer);

		// Level clear sound
		if (!level_clear_buffer.loadFromFile("sounds/level_clear.ogg")) {
			std::cout << "Level clear sound not loaded\n";
		}
		level_clear.setBuffer(level_clear_buffer);

		// Level 1 music
		if (!level1_background.openFromFile("sounds/background_music_1.ogg"))
			std::cout << "Background music level 1 not loaded";
		level1_background.setVolume(25);
		musicList.push_back(&level1_background);

		// Level 2 music
		if (!level2_background.openFromFile("sounds/background_music_2.ogg"))
			std::cout << "Background music level 2 not loaded";
		level2_background.setVolume(25);
		musicList.push_back(&level2_background);

		// Level 3 music
		if (!level3_background.openFromFile("sounds/background_music_3.ogg"))
			std::cout << "Background music level 3 not loaded";
		level3_background.setVolume(25);
		musicList.push_back(&level3_background);

		/*player_view.setCenter(100, 100);
		window.setView(player_view);*/
		level_editor = Level_Editor(textures,
			{
				"filling", "floor down","corner left down","corner left",
				"corner right down", "corner right", "corner down left",
				"corner left in", "corner rigth in down", "corner right in",
				"floor", "wall left", "wall right",
				"corner1", "corner2","corner3", "corner4",
				"floor1", "floor2", "floor3", "floor4",
				"hook1", "hook2", "hook3", "hook4", "map", "fishstick"
			});
		level_editor.set_position(player_view.getCenter());
	}

	// Loads the drawables into the vectors for corresponding level
	void load_level() {
		drawables = drawable_object_read(level_selector.get_current_level().overworld, textures, start_position);
		void_drawables = drawable_object_read(level_selector.get_current_level().voidworld, textures, start_position);
		player.drawable_set_position(start_position);
	}

	// Changes whether the user can edit the level
	void game_set_edit(bool setting) {
		edit = setting;
	}

	// Returns whether the user can edit the level
	bool game_get_edit() {
		return edit;
	}

	void pause_music() {
		for (auto music: musicList) {
			music->pause();
		}
	}

	void stop_music() {
		for (auto music : musicList) {
			music->stop();
		}
	}

	void change_music(int level) {
		std::cout << "changing music";
		musicList[level-1]->play();
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
			for (auto& drawable : void_drawables) {
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
			portal_shoot.play();
			// Run the calculation with the drawables from the current world
			if (overworld) {
				data = bullet.portal_bullet_impact_calc(drawables);
			}
			else {
				data = bullet.portal_bullet_impact_calc(void_drawables);
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
			drawable_object_write(level_selector.get_current_level().overworld, drawables, start_position);
			drawable_object_write(level_selector.get_current_level().voidworld, void_drawables, start_position);
			window.close();
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::K) {
			// Change in and out of edit mode and deselect all objects
			edit = !edit;
			for (auto& drawing : drawables) {
				drawing->drawable_deselect();
			}
		}
		else if (key_event.type == sf::Event::MouseButtonReleased && key_event.key.code == sf::Mouse::Left) {
			// Add objects to level via level editor
			level_editor.get_input(drawables, void_drawables, overworld, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::LControl) {
			// Switch between dimensions
			dimension_switch.play();
			overworld = !overworld;
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::Num9) {
			stop_music();
			new_music = true;
			level_selector.next_level();
			load_level();
		}
		else if (key_event.type == sf::Event::KeyReleased && key_event.key.code == sf::Keyboard::Num8) {
			level_selector.previous_level();
			stop_music();
			new_music = true;
			load_level();
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

	// Delete object from the game
	void game_delete_object(sf::Vector2f location) {
		std::cout << "deleted\n";
		if (overworld) {
			for (auto& drawable : drawables) {
				if (drawable->drawable_get_selected()) {
					drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
				}
			}
		}
		else {
			for (auto& drawable : void_drawables) {
				if (drawable->drawable_get_selected()) {
					void_drawables.erase(std::remove(void_drawables.begin(), void_drawables.end(), drawable), void_drawables.end());
				}
			}
		}
	}

	// Checks for certain inputs and acts accordingly
	void game_get_input() {
		sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		// Left Pressed && edit: select a drawable
		// Right Pressed && edit: move a drawable around using the mouse
		// Delete Pressed && edit: delete drawable object
		// Right/Left Pressed && !edit: shoot portal
		// Check event: Closed, K = editmode, Ctrl = dimension, arrow-keys = move screen for edit

		// Make sure not to misplace the level editor
		if (edit && !level_editor.get_hitbox().contains(mouse_position)) {
			auto location = sf::Mouse::getPosition(window);
			// Select object when editing
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				game_select(window.mapPixelToCoords(location));
			}
			// Move selected object around
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				auto position = window.mapPixelToCoords(location);
				game_move_mouse({ float(int(position.x / 100) * 100), float(int(position.y / 100) * 100) });
			}
			// Delete selected object
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				game_delete_object(window.mapPixelToCoords(location));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			esc = true;
			pause_music();
			std::cout << "esc pressed" << std::endl;
		}
		// Shoot the portal
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && !edit) {
			game_shoot_portal(sf::Mouse::isButtonPressed(sf::Mouse::Left));
		}
		
		// Check for all other events
		sf::Event key_event;
		window.pollEvent(key_event);
		game_act_on_key(key_event);
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
			portal_teleport.play();
			portal_set.linked_portals_teleport(player, p1);
			overworld = p2.drawable_get_dimension();
		}
		else if (player.player_intersect(p2.drawable_get_hitbox()) && overworld == p2.drawable_get_dimension()) {
			portal_teleport.play();
			portal_set.linked_portals_teleport(player, p2);
			overworld = p1.drawable_get_dimension();
		}
		p1.drawable_update();
		p2.drawable_update();
		if (new_music) {
			change_music(level_selector.get_level_index());
			new_music = false;
		}
	}

	// Draw the current game state
	void game_draw() {

		window.clear();
		// Draw the background first
		if (overworld) {
			window.draw(map_overworld);
		}
		else {
			window.draw(map_void);
		}

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
		// Draw level editor if in edit mode 
		if (edit) {
			level_editor.set_position(game_edit_view.getCenter());
			level_editor.draw(window);
		}
		window.display();
	}
	int Run() {
		bool Running = true;
		new_music = true;
		
		while (Running) {
			game_get_input();
			if (esc == true) {
				esc = false;
				std::cout << "to main menu" << std::endl;
				window.setView(sf::View({ 960,540 }, { 1920, 1080 }));
				return(0);
			}
			game_update();
			game_draw();
		}
		return (-1);
	}
};


#endif