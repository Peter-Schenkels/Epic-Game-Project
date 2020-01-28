// Reads drawable object from a file, allows the user to move them inside the window and saves the new objects to the file
#include "factory.hpp"
#include "settings.hpp"
#include <iostream>
//#include "screens.hpp"
#include "main_menu.hpp"
#include "game.hpp"

int main(int argc, char* argv[]) {
	//Applications variables
	std::vector<Screens*> Screens;
	int screen = 0;
	sf::RenderWindow window{ sf::VideoMode{WINDOW_SIZE_X, WINDOW_SIZE_Y}, "epic" };
	//Game platformer(window);
	window.setFramerateLimit(FRAME_RATE);
	std::cout << "Starting game..." << std::endl;
	main_menu s0(window);
	Screens.push_back(&s0);
	Game platformer(window);
	Screens.push_back(&platformer);
	//s0.init();

	//Main loop
	while (screen >= 0) {
		screen = Screens[screen]->Run();
	}

	return EXIT_SUCCESS;
}