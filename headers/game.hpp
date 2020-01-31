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
	Animation idle_animation_left;
	Animation idle_animation_right;
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
	sf::Sound death_sound;
	sf::SoundBuffer death_sound_buffer;
	sf::Music level1_background;
	sf::Music level2_background;
	sf::Music level3_background;
	std::vector<sf::Music*> musicList;
	sf::Clock portal_placement_delay; // For portal placement delay
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
	int dead = 0;
	sf::RectangleShape fade_out{ sf::Vector2f{1920, 1080} };
	

public:
	// Constructor
	Game(sf::RenderWindow& window);

	// Loads the drawables into the vectors for corresponding level
	void game_load_level();

	// Changes whether the user can edit the level
	void game_set_edit(bool setting);

	// Returns whether the user can edit the level
	bool game_get_edit();

	void pause_music();

	void stop_music();

	void change_music(int level);

	// Selects which drawable item has to be moved by the level editor
	void game_select(sf::Vector2f location);

	// Move the selected drawable object along with where the mouse is
	void game_move_mouse(sf::Vector2f location);

	// Move the edit camera using lambdas for the arrow-keys
	void view_move_key(sf::Event& entry);

	// Return the list of drawables
	std::vector<Drawable*> game_get_drawables();

	// Saves the current level
	void save();

	// Shoots portals
	void game_shoot_portal(bool order);

	// Act upon closed and key events
	void game_act_on_key(sf::Event key_event);

	// Delete object from the game
	void game_delete_object(sf::Vector2f location);

	// Checks for certain inputs and acts accordingly
	void game_get_input();

	void win();

	// Updates the game staete
	void game_update();

	void check_player_death();

	// Draw the current game state
	void game_draw();

	int run();
};


#endif