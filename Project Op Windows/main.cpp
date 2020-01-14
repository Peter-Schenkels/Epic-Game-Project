// main.cpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1.1

// Reads drawable object from a file, allows the user to move them inside the window and saves the new objects to the file
#include "factory.hpp"

int main(int argc, char* argv[]) {
	sf::RenderWindow window{ sf::VideoMode{640, 480}, "SFML window" };

	std::string link("objects.json");
	// Create a list filled with all drawable objects read from input
	std::vector<drawable*> drawables = drawable_object_read(link);
	game platformer{ drawables, window };

	while (window.isOpen()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && platformer.get_edit()) {
			// Select the object the mouse left-clicks on
			sf::Vector2f location{ float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };
			platformer.select(location);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && platformer.get_edit()) {
			// If an object has been selected by left-clicking, right-clicking will move this object
			// to where right-click has been pressed
			sf::Vector2f location{ float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };
			platformer.move_mouse(location);
		}

		sf::Event key_press;
		if (window.pollEvent(key_press)) {
			if (key_press.type == sf::Event::KeyReleased && key_press.key.code == sf::Keyboard::K) {
				// Change in and out of edit mode
				platformer.set_edit(!platformer.get_edit());
			}
			else if (key_press.type == sf::Event::KeyPressed) {
				// Move something with WASD
				auto key = key_press.key.code;
				if (key == sf::Keyboard::W || key == sf::Keyboard::A || key == sf::Keyboard::S ||
					key == sf::Keyboard::D) {
					platformer.move_key(key_press);
				}
			}
		}

		sf::Event event;
		if (window.pollEvent(event)) {
			// If the window has been close, save the new objects to a file
			if (event.type == sf::Event::Closed) {
				drawable_object_write(link, platformer.get_drawables());
				window.close();
			}
		}

		// Draw all objects
		platformer.draw();
		sf::sleep(sf::milliseconds(10));
	}
	return 0;
}