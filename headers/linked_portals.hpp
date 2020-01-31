
#ifndef LINKED_PORTALS_HPP
#define LINKED_PORTALS_HPP

#include "player.hpp"
#include "portal.hpp"

// Class that consists of 2 portals and handles all interactions between these 2
class Linked_Portals {
protected:
	Portal& portal_1;
	Portal& portal_2;

	sf::Vector2f reset_location;

	// The first std::string keys are all of the possible orientations for the entry portal
	// The second std::string keys are all of the possible orientations for the exit portal
	// By calling on the map using 2 strings, a lambda function will be ran that edits the momentum of the player
	// according to the entered portal orientations
	std::map<std::string, std::map<std::string, std::function< void(Player&) >>> change_momentum;

public:

	// Constructor
	Linked_Portals(Portal& first, Portal& second);

	// Replace an existing portal
	void linked_portals_portal_set(sf::Vector2f loc, std::string entrance, bool order, bool overworld);

	void set_reset_location(sf::Vector2f new_reset_location);

	void reset();

	// Prints all portals coordinates
	void linked_portals_print_portals();

	//  Make sure the player doesn't teleport inside the portal
	void linked_portals_set_offset(Player& player, Portal exit);

	// Teleport the player in between portals
	void linked_portals_teleport(Player& player, Portal entry);
};


#endif