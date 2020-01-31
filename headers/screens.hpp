#ifndef SCREENS_HPP
#define SCREENS_HPP

// screens.hpp
// Check if a sf::FloatRect collides with the right or left side of the hitbox
// Contains the Screens class


// Superclass of both Game and Main_Menu that allows to display them alternatively
class Screens {
public:
	// Virtual function for running the current screen
	virtual int run() = 0;
};

#endif