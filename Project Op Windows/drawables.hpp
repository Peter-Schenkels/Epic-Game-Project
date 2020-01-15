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
	sf::Vector2f position;
	sf::FloatRect hitbox;
	bool selected;
	std::string type;
	std::string color;
	sf::RectangleShape visual_hitbox; // for debuggen

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


class circle : public drawable {
// Subclass of drawable for circle objects
protected:
	// Shape of the circle, radius of the circle and the color of the circle that is read from the file
	sf::CircleShape shape;
	float radius;

public:
	// Constructor for circle that stores the given location, radius and color of the circle
	circle(sf::Vector2f location, float radius, std::string color);


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


	// Draws the picture
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns the link that the picture uses as texture
	std::string drawable_get_visual() override;

	// Update the picture
	void drawable_update() override;
};


class portal : public picture {
protected:
	std::string orientation;
	std::string doorway;

public:
	portal(sf::Vector2f location, sf::Vector2f size, std::string link, std::string orientation) :
		picture(location, size, link),
		orientation(orientation)
	{
		float rotation;
		std::array<std::string, 4> orientations{ "TOP", "RIGHT", "BOTTOM", "LEFT" };
		
		for (unsigned int i = 0; i < 4; i++) {
			if (orientations[i] == orientation) {
				rotation = float(i * 90);
				if (i <= 1) {
					doorway = orientations[i + 2];
				}
				else {
					doorway = orientations[i - 2];
				}
			}
		}
		sprite.setRotation(rotation);
	}
};


class linked_portals {
protected:
	portal& void_world;
	portal& over_world;

public:
	linked_portals(portal& void_world, portal& over_world):
		void_world(void_world),
		over_world(over_world)
	{}


	void portal_set(portal& given, std::string world) {
		if (world == "OVERWORLD") {
			over_world = given;
		}
		else {
			void_world = given;
		}
	}

	void teleport(drawable* player, std::string destination_world) {
		if (destination_world == "OVERWORLD") {
			player->drawable_set_position(over_world.drawable_get_location());
		}
		else {
			player->drawable_set_position(void_world.drawable_get_location());
		}
		// Change player momentum
		// Teleport next to other portal, not inside of it
	}
};

#endif