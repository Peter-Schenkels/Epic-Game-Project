// main.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1.1

// Reads drawable object from a file, allows the user to move them inside the window and saves the new objects to the file
#include "factory.hpp"
#include "settings.hpp"
#include "game.hpp"
#include <iostream>


int main(int argc, char* argv[]) {

	
	sf::RenderWindow window{ sf::VideoMode{WINDOW_SIZE_X, WINDOW_SIZE_Y}, "epic" };
	game platformer(window);
	window.setFramerateLimit(FRAME_RATE);
	std::cout << "Starting game..." << std::endl;\
	while (window.isOpen()) {
		// Draw all objects
		platformer.get_input();
		platformer.update();
		platformer.draw();

	}
	return 0;
}