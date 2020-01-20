#pragma once
#include "drawables.hpp"
#include "player_hitbox.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>


//class to calculate the trajectory of the bullet and the orientation the portal should have
class Portal_bullet : public Drawable {
private:
	sf::Vector2f start_pos;
	sf::Vector2u window;
	Player_Hitbox collision_box;
	sf::Vector2f angle;

public:
	Portal_bullet(sf::Vector2f& pos_player, sf::Vector2u windowSize, sf::Vector2f& pos_mouse) :
		Drawable(pos_player, sf::Vector2f( 20.00, 20.00 ), "BULLET", "white"),
		start_pos(pos_player),
		window(windowSize),
		collision_box(pos_player, sf::Vector2f(20.00, 20.00))
	{
		sf::Vector2f aimdir = pos_mouse - pos_player;
		angle = aimdir / sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
		std::cout << std::to_string(angle.x) << " " << std::to_string(angle.y) << "\n";
	}

	// Function that draws the bullet
	void drawable_draw(sf::RenderWindow& window) override;

	// Returns color of the bullet
	std::string drawable_get_visual() override;

	// Update the bullet
	void drawable_update() override;


	//function to calculate if a object will be hit in the bullet's trajectory and returns the coordinates of the impact and the orientation of the portal
	std::pair<sf::Vector2f, std::string> portal_bullet_impact_calc(const std::vector<Drawable*>& drawables, sf::RenderWindow& windowref);


};