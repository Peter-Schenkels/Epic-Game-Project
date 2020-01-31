#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#pragma warning(disable : 4996)

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"

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

	Main_Menu(sf::RenderWindow& window);

	int run();
};

#endif