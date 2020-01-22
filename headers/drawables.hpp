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


class Drawable {
// Superclass for all the of the objects that can be used
protected:
	// Location of the object and a bool to remember whether an object has been selected by the user
	sf::Vector2f location;
	sf::FloatRect hitbox;
	bool selected;
	std::string type;
	std::string color;
	bool in_over_world;
	sf::RectangleShape visual_hitbox; // for debuggen

public:
	// Default Constructor
	Drawable(){}

	// Constructor for drawable objects that use a size parameter
	Drawable(sf::Vector2f location, sf::Vector2f size, std::string type, std::string visual);

	// Constructor for drawable objects that use a radius parameter
	Drawable(sf::Vector2f location, float radius, std::string type, std::string visual);


	// Sets the drawable size
	void drawable_set_size(sf::Vector2f new_size);

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

	// Get dimension the object finds itself in
	bool drawable_get_dimension();

	// Set dimension the object finds itself in
	void drawable_set_dimension(bool set);

	// Returns the object color
	virtual std::string drawable_get_visual() = 0;

	// Draw the object
	virtual void drawable_draw(sf::RenderWindow& window) = 0;

	// Update the object
	virtual void drawable_update() = 0;
};


class Circle : public Drawable {
// Subclass of drawable for circle objects
protected:
	// Shape of the circle, radius of the circle and the color of the circle that is read from the file
	sf::CircleShape shape;
	float radius;

public:
	// Constructor for circle that stores the given location, radius and color of the circle
	Circle(sf::Vector2f location, float radius, std::string color);


	// Function that draws the circle
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns color of circle
	std::string drawable_get_visual() override;

	// Update the circle
	void drawable_update() override;
};


class Rectangle : public Drawable {
// Subclass of drawable for rectangle objects
protected:
	// Shape, size and color of the rectangle
	sf::RectangleShape shape;
	sf::Vector2f size;
public:
	// Constructor for the rectangle class that stores the given location, size and color for the rectangle
	Rectangle(sf::Vector2f location, sf::Vector2f size, std::string color);


	// Function that draws the rectangle
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns color
	std::string drawable_get_visual() override;

	// Update the rectangle
	void drawable_update() override;
};


class Picture : public Drawable {
// Subclass of drawable for picture objects
protected:
	// The sprite, texture and link to the texture for the object
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f size;
	std::string link;

	// How much the the sprite differs from his initial position
	sf::Vector2f offset = { 0,0 };

public:
	// Constructor that stores the given location and link to the texture
	Picture(sf::Vector2f location, sf::Vector2f size, std::string link);

	Picture(sf::Vector2f location, sf::Vector2f size, std::string link, std::string name);


	// Draws the picture
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns the link that the picture uses as texture
	std::string drawable_get_visual() override;

	// Update the picture
	void drawable_update() override;

	// Sets picture size
	void picture_set_size(sf::Vector2f new_size);

	// Sets picture scale
	void picture_set_scale(sf::Vector2f scale) { sprite.setScale(scale); }

	// Returns picture scale
	sf::Vector2f picture_get_scale() { return sprite.getScale(); }
	
	// Sets picture offset
	void picture_set_offset(sf::Vector2f new_offset) { offset = new_offset; };

	// Sets picture rotation
	void picture_set_rotation(float rotation) { sprite.setRotation(rotation); }

	// Set picture origin
	void picture_set_origin_to_middle() { 
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}

	// Get picture origin
	sf::Vector2f picture_get_origin() { return sprite.getOrigin(); }

	sf::Sprite picture_get_sprite();
};


// Class for each of the portals
class Portal : public Drawable {
protected:
	sf::RectangleShape shape;
	Picture* body;
	std::string entrance;
	bool order;

public:
	// Default constructor
	Portal() {}

	// Constructor
	Portal(sf::Vector2f position, sf::Vector2f size, Picture* sprite, std::string entrance, bool order) :
		Drawable(position, size, "PORTAL", "White"),
		body(sprite),
		entrance(entrance),
		order(order)
	{
		body->picture_set_size(size);
		shape.setPosition(position);
		shape.setSize(size);
		portal_align_rotation();
	}

	// Set rotation
	void portal_align_rotation() {
		shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
		body->picture_set_origin_to_middle();

		float rotation = 0;
		std::array<std::string, 4> orientations{ "TOP", "RIGHT", "BOTTOM", "LEFT" };

		for (unsigned int i = 0; i < 4; i++) {
			if (orientations[i] == entrance) {
				rotation = float(i * 90);
				break;
			}
		}
		body->picture_set_rotation(rotation);
		shape.setRotation(rotation);
		auto portal_hitbox = drawable_get_hitbox();
		std::cout << portal_hitbox.top << " " << portal_hitbox.left << " " << portal_hitbox.height << " " << portal_hitbox.width << "\n";
	}


	// Draw the portal
	void drawable_draw(sf::RenderWindow & window) override{
		body->drawable_draw(window);
		auto hitbox = body->drawable_get_hitbox();

		sf::RectangleShape draw_hitbox(sf::Vector2f{ hitbox.width, hitbox.height });
		draw_hitbox.setPosition(sf::Vector2f( hitbox.left, hitbox.top ));
		window.draw(draw_hitbox);
	}

	// Return the visual data of the portal
	std::string drawable_get_visual() { 
		return color;
	}

	// Update the portal
	void drawable_update() { 
		body->drawable_set_position(location); 
		body->drawable_update();
	}

	// Return doorway
	std::string portal_get_entrance() {
		return entrance;
	}

	// Return order
	bool portal_get_order() {
		return order;
	}

	// Set entrance
	void portal_set_entrance(std::string new_entrance) {
		entrance = new_entrance;
		portal_align_rotation();
	}
};


#endif