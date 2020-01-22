#pragma once
#ifndef LINKED_TELEPORTERS_HPP
#define LINKED_TELEPORTERS_HPP

#include "player.hpp"

class Linked_Portals {
protected:
	Portal& portal_1;
	Portal& portal_2;

	// The first std::string keys are the orientations of the entry portal
	// The second std::string keys are the orientations of the exit portal
	std::map<std::string, std::map<std::string, std::function< void(Player&) >>> change_momentum;

public:
	// Constructor
	Linked_Portals(Portal& first, Portal& second) :
		portal_1(first),
		portal_2(second)
	{
		// Loop for creating a different effect on the momentum depending on the portals orientation
		std::array<std::string, 4> orientations = { "TOP", "LEFT", "BOTTOM", "RIGHT" };
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				// Select the correct multiplorientationsier for the combination of 
				// 0 = TOP, 1 = LEFT, 2 = BOTTOM, 3 = RIGHT
				sf::Vector2f multiplier;
				// Combinations that invert the y-speed:
				// TOP > LEFT, LEFT > BOTTOM, BOTTOM > RIGHT, RIGHT > TOP
				if ((i <= 2 && j - 1 == i) || (i == 3 && j == 0)) {
					multiplier = { 1, -1 };
				}
				// Combinations that invert the x-speed:
				// TOP > RIGHT, LEFT > TOP, BOTTOM > LEFT, RIGHT > BOTTOM
				else if ((i >= 1 && j + 1 == i) || (i == 0 && j == 3)) {
					multiplier = { -1, 1 };
				}
				// Combinations that invert both the y- and x-speeds:
				// TOP > TOP, LEFT > LEFT, BOTTOM > BOTTOM, RIGHT > RIGHT
				else if (i == j) {
					multiplier = { -1, -1 };
				}
				// Combinations that do not change the y- and x-speeds:
				// TOP > BOTTOM, LEFT > RIGHT, BOTTOM > TOP, RIGHT > LEFT
				else {
					multiplier = { 1, 1 };
				}
				// Save a lambda function that passes the correct player and multipliers to the edit_momentum function
				change_momentum[orientations[i]][orientations[j]] = std::function< void(Player&) >([multiplier]
				(Player& player) { player.player_set_speed(sf::Vector2f(player.player_get_speed().x * multiplier.x, 
					player.player_get_speed().y * multiplier.y)); });
			}
		}
	}

	// Set a new portal in a given world
	void linked_portals_portal_set(sf::Vector2f loc, std::string entrance, bool order) {
		if (order) {
			portal_1.drawable_set_position(loc);
			portal_1.portal_set_entrance(entrance);
		}
		else {
			portal_2.drawable_set_position(loc);
			portal_2.portal_set_entrance(entrance);
		}
	}

	// Prints all portals coordinates
	void linked_portals_print_portals() {
		auto void_loc = portal_1.drawable_get_location();
		auto over_loc = portal_2.drawable_get_location();
		std::cout << void_loc.x << ", " << void_loc.y << " : " << over_loc.x << ", " << over_loc.y << "\n";
	}

	//  Make sure the player doesn't teleport inside the portal
	void linked_portals_set_offset(Player& player, Portal exit) {
		std::string exit_entrance = exit.portal_get_entrance();

		if (exit_entrance == "TOP") {
			player.drawable_move(sf::Vector2f{ 0, -player.drawable_get_size().y - 100 });
		}
		else if (exit_entrance == "LEFT") {
			player.drawable_move(sf::Vector2f{ -player.drawable_get_size().x - 100, 0 });
		}
		else if (exit_entrance == "BOTTOM") {
			player.drawable_move(sf::Vector2f{ 0, 100 });
		}
		else {
			player.drawable_move(sf::Vector2f{ 100, 0 });
		}
		std::cout << exit_entrance << "\n";
	}

	void linked_portals_teleport(Player& player, Portal entry) {
		bool world = player.drawable_get_dimension();
		bool portal = entry.portal_get_order();
		std::string exit_orientation;

		// Change player location
		if (portal) { // Player teleports from p1 to p2
			player.drawable_set_position(portal_2.drawable_get_location());
			
			// Change momentum
			change_momentum[portal_1.portal_get_entrance()][portal_2.portal_get_entrance()](player);

			// Teleport next to destination instead of inside of the other portal
			linked_portals_set_offset(player, portal_2);
		}
		else { // Player teleports from p2 to p1
			player.drawable_set_position(portal_1.drawable_get_location());

			// Change momentum
			change_momentum[portal_2.portal_get_entrance()][portal_1.portal_get_entrance()](player);

			// Teleport next to destination instead of inside of the other portal
			linked_portals_set_offset(player, portal_1);
		}
	}
};


#endif