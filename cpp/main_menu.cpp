// main_menu.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the Main_Menu class


#include "main_menu.hpp"


// Constructor
Main_Menu::Main_Menu(sf::RenderWindow& window) :
	window(window)
{
	// Load music, fonts and textures
	playing = false;
	if (!main_menu_music.openFromFile("sounds/menu_music.ogg")) {
		std::cout << "Main menu theme not loaded" << std::endl;
	}
	main_menu_music.setVolume(25);
	main_menu_music.setLoop(true);

	if (!texture.loadFromFile("img/main_menu_game.png")) {
		std::cerr << "Main menu background not loaded" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255));

	if (!font.loadFromFile("VerminVibes1989.ttf")) {
		std::cerr << "Font not loaded" << std::endl;
	}

	menu_start.setFont(font);
	menu_start.setCharacterSize(50);
	menu_start.setString("Start");
	menu_start.setPosition({ 915.f, 500.f });

	menu_exit.setFont(font);
	menu_exit.setCharacterSize(50);
	menu_exit.setString("Exit");
	menu_exit.setPosition({ 915.f, 600.f });

	menu_continue.setFont(font);
	menu_continue.setCharacterSize(50);
	menu_continue.setString("Continue");
	menu_continue.setPosition({ 865.f, 500.f });
};

// Run the menu
int Main_Menu::run() {
	bool Running = true;
	sf::Event Event;
	main_menu_music.play();

	while (Running) {
		// Verifying events
		while (window.pollEvent(Event)) {
			// Window closed
			if (Event.type == sf::Event::Closed) {
				return (-1);
			}
			// Key pressed; Either selecting one of 2 options on the menu using Up and Down or pressing Enter
			// to actually press the button
			if (Event.type == sf::Event::KeyPressed) {
				switch (Event.key.code) {
				case sf::Keyboard::Up:
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0){
						// Continue playing
						main_menu_music.pause();
						playing = true;
						return (1);
					}
					else{
						// Quit game
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		// Display different colors based on the kind of menu
		if (menu == 0) {
			menu_start.setColor(sf::Color(0, 190, 40, 255));
			menu_exit.setColor(sf::Color(255, 0, 215, 255));
			menu_continue.setColor(sf::Color(0, 190, 40, 255));
		}
		else {
			menu_start.setColor(sf::Color(255, 0, 215, 255));
			menu_exit.setColor(sf::Color(0, 190, 40, 255));
			menu_continue.setColor(sf::Color(255, 0, 215, 255));
		}

		// Draw the menu
		window.clear();
		window.draw(sprite);
		if (playing) {
			window.draw(menu_continue);
		}
		else {
			window.draw(menu_start);
		}
		window.draw(menu_exit);
		window.display();
	}
	// Just to be sure
	return (-1);
}