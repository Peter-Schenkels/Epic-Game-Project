#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"

class main_menu : public Screens {
private:
	bool playing;
	sf::Music main_menu_music;
	sf::RenderWindow& window;

public:
	main_menu(sf::RenderWindow& window) :
		window(window)
	{
		playing = false;
		/*if (!main_menu_music.openFromFile("KANABOONSilhouette.wav")) {
			std::cout << "Main menu theme not loaded\n";
		}*/
		/*if (!main_menu_music.openFromFile("Giorno's Theme.wav")) {
			std::cout << "Main menu theme not loaded\n";
		}*/
		if (!main_menu_music.openFromFile("sounds/menu_music.ogg")) {
			std::cout << "Main menu theme not loaded\n";
		}
		main_menu_music.setVolume(25);
		//main_menu_music.setPlayingOffset(sf::seconds(24.f));
		//main_menu_music.setPlayingOffset(sf::seconds(225.f));
	};
	int Run() {
		sf::Event Event;
		bool Running = true;
		sf::Texture Texture;
		sf::Sprite Sprite;
		int alpha = 0;
		sf::Font Font;
		sf::Text Menu1;
		sf::Text Menu2;
		sf::Text Menu3;
		int menu = 0;

		if (!Texture.loadFromFile("img/main_menu game.png"))
		{
			std::cerr << "Error loading menu background" << std::endl;
			return (-1);
		}

		Sprite.setTexture(Texture);
		Sprite.setColor(sf::Color(255, 255, 255));

		if (!Font.loadFromFile("VerminVibes1989.ttf")) {
			std::cerr << "Error loading ComicSans.ttf" << std::endl;
			return (-1);
		}

		Menu1.setFont(Font);
		Menu1.setCharacterSize(50);
		Menu1.setString("Play");
		Menu1.setPosition({ 915.f, 500.f });

		Menu2.setFont(Font);
		Menu2.setCharacterSize(50);
		Menu2.setString("Exit");
		Menu2.setPosition({ 915.f, 600.f });

		Menu3.setFont(Font);
		Menu3.setCharacterSize(50);
		Menu3.setString("Continue");
		Menu3.setPosition({ 865.f, 500.f });

		main_menu_music.play();

		while (Running) {
			//Verifying events
			while (window.pollEvent(Event)) {
				// Window closed
				if (Event.type == sf::Event::Closed) {
					return (-1);
				}
				//Key pressed
				if (Event.type == sf::Event::KeyPressed) {
					switch (Event.key.code) {
					case sf::Keyboard::Up:
						menu = 0;
						break;
					case sf::Keyboard::Down:
						menu = 1;
						break;
					case sf::Keyboard::Return:
						if (menu == 0)
						{
							//Let's get play !
							main_menu_music.pause();
							playing = true;
							return (1);
						}
						else
						{
							//Let's get work...
							return (-1);
						}
						break;
					default:
						break;
					}
				}
			}
			//if (menu == 0) {
			//	Menu1.setColor(sf::Color(255, 0, 0, 255));	//0, 190, 40
			//	Menu2.setColor(sf::Color(255, 255, 255, 255)); //255, 0, 215
			//	Menu3.setColor(sf::Color(255, 0, 0, 255));
			//}
			//else {
			//	Menu1.setColor(sf::Color(255, 255, 255, 255));
			//	Menu2.setColor(sf::Color(255, 0, 0, 255));
			//	Menu3.setColor(sf::Color(255, 255, 255, 255));
			//}
			if (menu == 0) {
				Menu1.setColor(sf::Color(0, 190, 40, 255));	//0, 190, 40
				Menu2.setColor(sf::Color(255, 0, 215, 255)); //255, 0, 215
				Menu3.setColor(sf::Color(0, 190, 40, 255));
			}
			else {
				Menu1.setColor(sf::Color(255, 0, 215, 255));
				Menu2.setColor(sf::Color(0, 190, 40, 255));
				Menu3.setColor(sf::Color(255, 0, 215, 255));
			}
			//Clearing screen
			window.clear();
			//Drawing
			window.draw(Sprite);
			if (playing) {
				window.draw(Menu3);
			}
			else {
				window.draw(Menu1);
			}
			window.draw(Menu2);
			window.display();
		}
		//Never reaching this point normally, but just in case, exit the application
		return (-1);
	}
};

#endif