// portal_bullet.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the Portal_Bullet class


#include <SFML/Graphics.hpp>
#include "portal_bullet.hpp"


// Constructor
Portal_Bullet::Portal_Bullet(sf::Vector2f& pos_player, sf::Vector2u windowSize, sf::Vector2f& pos_mouse) :
	Drawable(pos_player, sf::Vector2f(8.00, 8.00), "BULLET", "white"),
	start_pos(pos_player),
	window(windowSize),
	collision_box(pos_player, sf::Vector2f(8.00, 8.00)),
	hitbox(sf::FloatRect(pos_player, sf::Vector2f(8.00, 8.00)))
{
	sf::Vector2f aimdir = pos_mouse - pos_player;
	angle = aimdir / sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
}

// Draw the bullet; don't
void Portal_Bullet::drawable_draw(sf::RenderWindow& window) {
	return;
}

// Return the visual of the bullet
std::string Portal_Bullet::drawable_get_visual() {
	return color;
}

// Update the bullet; don't
void Portal_Bullet::drawable_update() {
	return;
}

// Function to calculate if a object will be hit in the bullet's trajectory and 
// return the coordinates of the impact and the orientation of the portal
std::pair<sf::Vector2f, std::string>  Portal_Bullet::portal_bullet_impact_calc(const std::vector<Drawable*>& drawables) {
	// Check if a sf::FloatRect collides with the right  or left side of the hitbox
	std::cout << "location " << std::to_string(location.x) + " " + std::to_string(location.y) + "\n";
	std::cout << "window " << std::to_string(window.x) << " " << std::to_string(window.y) << "\n";
	sf::Vector2f location = start_pos;
	// While the bullet is in the view check for collision
	while (((location.x > start_pos.x - window.x/2) && (location.x < start_pos.x + window.x / 2)) && ((location.y > start_pos.y - window.y / 2) && (location.y < start_pos.y + window.y / 2)))
	{
		// Check every rectangle object
		for (auto object : drawables) {
			auto object_location = object->drawable_get_location();
			if (((object_location.x > start_pos.x - window.x / 2) && (object_location.x < start_pos.x + window.x / 2)) && 
				((object_location.y > start_pos.y - window.y / 2) && (object_location.y < start_pos.y + window.y / 2))) {
				// Check whether the bullet and object intersect at all, if so then search more specifically for the angle of impact
				if (object->drawable_get_hitbox().intersects(hitbox)) {
					std::string object_name = object->drawable_get_name();

					// A surface were portals can't be created
					if (object_name == "filling" or object_name == "map" or
						object_name == "fishstick" or object_name == "spike" or
						object_name == "text1" or object_name == "text2" or
						object_name == "text3" or object_name == "text4" or 
						object_name == "datapad" or object_name == "arrow left" or 
						object_name == "arrow right" or object_name == "arrow up" or
						object_name == "arrow down" or object_name == "cross") {
						return { {0,0}, "NONE" };
					}

					// Check if a sf::FloatRect collides with the right or left side of the hitbox
					if (collision_box.Player_Hitbox_left_side_intersect(object->drawable_get_hitbox()))
					{
						std::cout << "collision detected left\n";
							return  std::pair<sf::Vector2f, std::string> {location, "RIGHT"};
					}
					else if (collision_box.Player_Hitbox_right_side_intersect(object->drawable_get_hitbox()))
					{
						std::cout << "collision detected right\n";
							return  std::pair<sf::Vector2f, std::string> {location, "LEFT"};
					}
					// Check if a sf::FloatRect collides with the bottom or top of the hitbox
					else if (collision_box.Player_Hitbox_bottom_side_intersect(object->drawable_get_hitbox()))
					{
						std::cout << "collision detected bot\n";
						return  std::pair<sf::Vector2f, std::string> {location, "TOP"};
					}
					else if (collision_box.Player_Hitbox_top_side_intersect(object->drawable_get_hitbox())) {
						std::cout << "collision detected top\n";
						return  std::pair<sf::Vector2f, std::string> {location, "BOTTOM"};
					}
				}
			}
		}
		// Change the location of the hitbox and the location of the bullet
		location += angle;
		hitbox.left = location.x;
		hitbox.top = location.y;
		collision_box.Player_Hitbox_update(location);
	}
	throw No_Impact();
}
