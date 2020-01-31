#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#pragma warning(disable : 4996)

// main_menu.hpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains the Main_Menu class


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"

// Class for displaying the main menu
class Main_Menu : public Screens {
private:
	bool playing;
	sf::Music main_menu_music;
	sf::RenderWindow& window;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text menu_start;
	sf::Text menu_exit;
	sf::Text menu_continue;
	int menu = 0;

public:
	// Constructor
	Main_Menu(sf::RenderWindow& window);

	// Run the menu
	int run();
};

#endif