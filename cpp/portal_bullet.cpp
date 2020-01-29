#include <SFML/Graphics.hpp>
#include "portal_bullet.hpp"
#include "player_hitbox.hpp"
#include <iostream>
#include <string>
#include "portal_error.hpp"
#include <exception>

void Portal_Bullet::drawable_draw(sf::RenderWindow& window) {
	return;
}

std::string Portal_Bullet::drawable_get_visual() {
	return color;
}

void Portal_Bullet::drawable_update() {
	return;
}


// Function to calculate if a object will be hit in the bullet's trajectory and returns the coordinates of the impact and the orientation of the portal
std::pair<sf::Vector2f, std::string>  Portal_Bullet::portal_bullet_impact_calc(const std::vector<Drawable*>& drawables) {
	//check if a sf::FloatRect collides with the right  or left side of the hitbox
	std::cout << "location " << std::to_string(location.x) + " " + std::to_string(location.y) + "\n";
	std::cout << "window " << std::to_string(window.x) << " " << std::to_string(window.y) << "\n";
	sf::Vector2f location = start_pos;
	// While the bullet is in the view check for collision
	while (((location.x > start_pos.x - window.x/2) && (location.x < start_pos.x + window.x / 2)) && ((location.y > start_pos.y - window.y / 2) && (location.y < start_pos.y + window.y / 2)))
	{
		// Check every rectangle object
		for (auto object : drawables) {
			if (object->drawable_get_type() == std::string("RECTANGLE")) {
				// Check if a sf::FloatRect collides with the right or left side of the hitbox

				//if (object->drawable_get_hitbox().intersects(hitbox)) {
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
				//}
			}
		}
		// Change the location of the hitbox and the location of the bullet
		location += angle;
		hitbox.left = location.x*10;
		hitbox.top = location.y*10;
		collision_box.Player_Hitbox_update(location);
	}
	throw No_impact();
}