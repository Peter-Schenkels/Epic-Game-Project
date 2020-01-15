#pragma once
#ifndef LINKED_TELEPORTERS_HPP
#define LINKED_TELEPORTERS_HPP

#include "player.hpp"

class Linked_Portals {
protected:
	Portal& void_world;
	Portal& over_world;

public:
	// Constructor
	Linked_Portals(Portal& void_world, Portal& over_world) :
		void_world(void_world),
		over_world(over_world)
	{}

	// Set a new portal in a given world
	void portal_set(Portal& given, std::string world) {
		if (world == "OVERWORLD") {
			over_world = given;
		}
		else {
			void_world = given;
		}
	}

	void teleport(Player player) {
		// Change player location, momentum and make sure they dont spawn in the other portal
		if (player.drawable_get_dimension()) {
			player.drawable_set_position(void_world.drawable_get_location());
			if (void_world.portal_get_doorway() == "BOTTOM") {
				auto old_spd = player.player_get_speed();

			}
		}
		else {
			player.drawable_set_position(over_world.drawable_get_location());
		}
	}
};


#endif