#ifndef DRAWABLES_HPP
#define DRAWABLES_HPP

// drawable.hpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1

// Contains all classes that can be read from and written to a file

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <map>


class drawable {
// Superclass for all the of the objects that can be used
protected:
	// Location of the object and a bool to remember whether an object has been selected by the user
	sf::Vector2f location;
	sf::FloatRect hitbox;
	bool selected;
	std::string type;
	std::string color;

public:
	// Constructor for drawable objects that use a size parameter
	drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string color);

	// Constructor for drawable objects that use a radius parameter
	drawable(sf::Vector2f location, float radius, std::string type, std::string color);

	// Returns whether the object has been selected by the user or not
	bool drawable_get_selected();

	// Returns the location of the object
	sf::Vector2f drawable_get_location();

	// Select/Deselect the drawable object
	void drawable_select();
	void drawable_deselect();

	// Move object
	void drawable_move(sf::Vector2f delta);

	// Set position
	void drawable_set_position(sf::Vector2f delta);

	// Return drawable type
	std::string drawable_get_type();

	// Return the size of the object hitbox
	sf::FloatRect drawable_get_hitbox();

	// Returns whether the hitbox contains a certain coordinate
	bool drawable_hitbox_contains_point(sf::Vector2f point);

	// Returns the size of the object
	sf::Vector2f drawable_get_size();

	// Returns the object color
	virtual std::string drawable_get_visual() = 0;

	// Draw the object
	virtual void drawable_draw(sf::RenderWindow& window) = 0;

	// Update the object
	virtual void drawable_update() = 0;
};


class game {
protected:
	std::vector<drawable*> drawables;
	sf::RenderWindow& window;
	bool edit;

public:
	game(std::vector<drawable*> vec, sf::RenderWindow& window) :
		drawables(vec),
		window(window),
		edit(false)
	{}

	void set_edit(bool setting) {
		edit = setting;
		sf::sleep(sf::milliseconds(90));
	}

	bool get_edit() {
		return edit;
	}

	void select(sf::Vector2f location) {
		std::cout << "selected\n";
		bool selected = false;
		for (auto drawing : drawables) {
			if (drawing->drawable_hitbox_contains_point(location) && selected == false) {
				drawing->drawable_select();
				selected = true;
			}
			else {
				drawing->drawable_deselect();
			}
		}
		sf::sleep(sf::milliseconds(90));
	}

	void move_mouse(sf::Vector2f location) {
		for (auto& drawing : drawables) {
			if (drawing->drawable_get_selected()) {
				drawing->drawable_set_position(location);
			}
		}
	}

	void move_key(sf::Event& entry) {
		std::map<sf::Keyboard::Key, sf::Vector2f> moves{};
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::W, sf::Vector2f{ 0, 1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::A, sf::Vector2f{ -1, 0 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::S, sf::Vector2f{ 0, -1 }));
		moves.insert(std::pair<sf::Keyboard::Key, sf::Vector2f>(sf::Keyboard::D, sf::Vector2f{ 1, 0 }));

		for (auto& drawing : drawables) {
			if (drawing->drawable_get_selected()) {
				drawing->drawable_move(moves[entry.key.code]);
			}
		}
	}

	std::vector<drawable*> get_drawables() {
		return drawables;
	}

	void draw() {
		window.clear();
		for (auto drawing : drawables) {
			drawing->drawable_update();
			drawing->drawable_draw(window);
		}
		window.display();
	}
};


class circle : public drawable {
// Subclass of drawable for circle objects
protected:
	// Shape of the circle, radius of the circle and the color of the circle that is read from the file
	sf::CircleShape shape;
	float radius;

public:
	// Constructor for circle that stores the given location, radius and color of the circle
	circle(sf::Vector2f location, float radius, std::string color);

	// Constructor for circle using a drawable pointer
	circle(drawable* input);


	// Function that draws the circle
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns color of circle
	std::string drawable_get_visual() override;

	// Update the circle
	void drawable_update() override;
};


class rectangle : public drawable {
// Subclass of drawable for rectangle objects
protected:
	// Shape, size and color of the rectangle
	sf::RectangleShape shape;
	sf::Vector2f size;

public:
	// Constructor for the rectangle class that stores the given location, size and color for the rectangle
	rectangle(sf::Vector2f location, sf::Vector2f size, std::string color);

	// Constructor for rectangle using drawable pointer
	rectangle(drawable* input);


	// Function that draws the rectangle
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns color
	std::string drawable_get_visual() override;

	// Update the rectangle
	void drawable_update() override;
};


class picture : public drawable {
// Subclass of drawable for picture objects
protected:
	// The sprite, texture and link to the texture for the object
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
	std::string link;

public:
	// Constructor that stores the given location and link to the texture
	picture(sf::Vector2f location, sf::Vector2f size, std::string link);

	// Constructor that uses a drawable pointer
	picture(drawable* input);


	// Draws the picture
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns the link that the picture uses as texture
	std::string drawable_get_visual() override;

	// Update the picture
	void drawable_update() override;
};

#endif