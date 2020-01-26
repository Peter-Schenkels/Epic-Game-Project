#pragma once
#ifndef LINKED_TELEPORTERS_HPP
#define LINKED_TELEPORTERS_HPP

#include "player.hpp"
#include "portal.hpp"

// Class that consists of 2 portals and handles all interactions between these 2
class Linked_Portals {
protected:
	Portal& portal_1;
	Portal& portal_2;

	// The first std::string keys are all of the possible orientations for the entry portal
	// The second std::string keys are all of the possible orientations for the exit portal
	// By calling on the map using 2 strings, a lambda function will be ran that edits the momentum of the player
	// according to the entered portal orientations
	std::map<std::string, std::map<std::string, std::function< void(Player&) >>> change_momentum;

public:
	// Constructor
	Linked_Portals(Portal& first, Portal& second) :
		portal_1(first),
		portal_2(second)
	{
		std::array<std::string, 4> orientations = { "TOP", "LEFT", "BOTTOM", "RIGHT" };
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				// Select the correct multiplier for all possible combinations of 
				// 0 = TOP, 1 = LEFT, 2 = BOTTOM, 3 = RIGHT
				sf::Vector2f multiplier;
				// Combinations that invert the x-speed:
				// TOP to LEFT, LEFT to LEFT, BOTTOM to LEFT, RIGHT to RIGHT
				if ((i >+ 0 && i <= 2 && j == 1) || (i == 3 && j == 3)) {
					multiplier = { -1, 1 };
				}
				// Combinations that invert the y-speed:
				// TOP to TOP, LEFT to BOTTOM, BOTTOM to BOTTOM, RIGHT to BOTTOM
				else if ((i >= 1 && i <= 3 && j == 2) || (i == 0 && j == 0)) {
					multiplier = { 1, -1 };
				}
				// Combinations that don't change the x- or y-axis
				// All the other ones
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

	// Replace an existing portal
	void linked_portals_portal_set(sf::Vector2f loc, std::string entrance, bool order, bool overworld) {
		std::cout << "overworld = "<< overworld << "\n";
		// Set portal_1 if this is the portal that has changed locations
		if (order) {
			portal_1.drawable_set_dimension(overworld);
			portal_1.drawable_set_position(loc);
			portal_1.portal_set_entrance(entrance);
			portal_1.portal_align();
		}
		// Set portal-2 if this is the portal that has changed locations
		else {
			portal_2.drawable_set_dimension(overworld);
			portal_2.drawable_set_position(loc);
			portal_2.portal_set_entrance(entrance);
			portal_2.portal_align();
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

		// Place the player just on top of the portal
		if (exit_entrance == "TOP") {
			player.drawable_move(sf::Vector2f{ 0, -player.drawable_get_size().y - 32 });
		}
		// Place the player just on the left and on the same height as the portal
		else if (exit_entrance == "LEFT") {
			player.drawable_move(sf::Vector2f{ -player.drawable_get_size().x - 32, -64 });
		}
		// Place the player just below the portal
		else if (exit_entrance == "BOTTOM") {
			player.drawable_move(sf::Vector2f{ 0, 32 });
		}
		// Place the player just on the right and on the same height as the porta;
		else {
			player.drawable_move(sf::Vector2f{ exit.drawable_get_hitbox().width, -64 });
		}
		//std::cout << exit_entrance << "\n";
	}

	// Teleport the player in between portals
	void linked_portals_teleport(Player& player, Portal entry) {
		bool portal = entry.portal_get_order();

		// Select which portal to teleport to; if entry is true the point of entry is portal_1, otherwise it's portal_2
		if (portal) { // Player teleports from p1 to p2
			player.drawable_set_position(portal_2.drawable_get_location());

			// Change momentum of the player to match the difference in angles between the portals
			change_momentum[portal_1.portal_get_entrance()][portal_2.portal_get_entrance()](player);

			// Teleport next to destination instead of inside of the other portal to prevent endless teleporting loops
			linked_portals_set_offset(player, portal_2);
		}
		else { // Player teleports from p2 to p1
			player.drawable_set_position(portal_1.drawable_get_location());

			// Change momentum of the player to match the difference in angles between the portals
			change_momentum[portal_2.portal_get_entrance()][portal_1.portal_get_entrance()](player);

			// Teleport next to destination instead of inside of the other portal to prevent endless teleporting loops
			linked_portals_set_offset(player, portal_1);
		}
	}
};


#endif