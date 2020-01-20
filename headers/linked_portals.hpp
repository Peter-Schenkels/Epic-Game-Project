#pragma once
#ifndef LINKED_TELEPORTERS_HPP
#define LINKED_TELEPORTERS_HPP

#include "player.hpp"

class Linked_Portals {
protected:
	Portal& void_world;
	Portal& over_world;
	std::map<std::string, std::map<std::string, std::function< void(Player&) >>> change_momentum;
	std::map<std::array<int, 2>, std::array<int, 2>> variables;

public:
	// Constructor
	Linked_Portals(Portal& void_world, Portal& over_world) :
		void_world(void_world),
		over_world(over_world)
	{
		// Lambda function for changing the players momentum
		std::function< void(Player&, sf::Vector2f) > edit_momentum = [](Player& player, sf::Vector2f momentum)
		{player.player_set_speed(sf::Vector2f(player.player_get_speed().x * momentum.x,
			player.player_get_speed().y * momentum.y)); };

		// Loop for creating a different effect on the momentum depending on the portals orientation
		std::array<std::string, 4> orientations = { "TOP", "LEFT", "BOTTOM", "RIGHT" };
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				// Select the correct multiplorientationsier for the combination of 
				// 0 = TOP, 1 = LEFT, 2 = BOTTOM, 3 = RIGHT
				sf::Vector2f multipliers;
				// Combinations that invert the y-speed:
				// TOP > LEFT, LEFT > BOTTOM, BOTTOM > RIGHT, RIGHT > TOP
				if ((i <= 2 && j - 1 == i) || (i == 3 && j == 0)) {
					multipliers = { 1, -1 };
				}
				// Combinations that invert the x-speed:
				// TOP > RIGHT, LEFT > TOP, BOTTOM > LEFT, RIGHT > BOTTOM
				else if ((i >= 1 && j + 1 == i) || (i == 0 && j == 3)) {
					multipliers = { -1, 1 };
				}
				// Combinations that invert both the y- and x-speeds:
				// TOP > TOP, LEFT > LEFT, BOTTOM > BOTTOM, RIGHT > RIGHT
				else if (i == j) {
					multipliers = { -1, -1 };
				}
				// Combinations that do not change the y- and x-speeds:
				// TOP > BOTTOM, LEFT > RIGHT, BOTTOM > TOP, RIGHT > LEFT
				else {
					multipliers = { 1, 1 };
				}
				// Save a lambda function that passes the correct player and multipliers to the edit_momentum function
				change_momentum[orientations[i]][orientations[j]] = std::function< void(Player&) >([&edit_momentum, multipliers]
				(Player& player) {edit_momentum(player, multipliers); });
			}
		}
	}


	// Set a new portal in a given world
	void portal_set(Portal& given, std::string world) {
		if (world == "OVERWORLD") {
			over_world = given;
		}
		else {
			void_world = given;
		}
	}

	void teleport(Player& player) {
		bool world = player.drawable_get_dimension();

		// Change player location
		if (world) {
			player.drawable_set_position(void_world.drawable_get_location());

			// Change momentum
			change_momentum[over_world.portal_get_doorway()][void_world.portal_get_doorway()](player);

			// Teleport next to destination instead of inside of the other portal
			sf::Vector2f size = void_world.drawable_get_size();
			std::string doorway = void_world.portal_get_doorway();
		}
		else {
			player.drawable_set_position(over_world.drawable_get_location());

			// Change momentum
			change_momentum[void_world.portal_get_doorway()][over_world.portal_get_doorway()](player);
		}
		player.drawable_set_dimension(!world);

		// Teleport next to destination instead of inside
	}
};


#endif