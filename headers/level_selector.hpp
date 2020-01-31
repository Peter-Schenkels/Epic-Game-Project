#ifndef LEVEL_SELECTOR_HPP
#define LEVEL_SELECTOR_HPP

#include <string>
#include <vector>

// Level class to hold overwolrd file location and void file location
class Level {

public:
	std::string voidworld;
	std::string overworld;

	// Takes in a string to the corresponding json file location of the overworld and voidworld
	Level(std::string overworld, std::string voidworld);

};


// Class to load and choose levels easily
class Level_Selector {

	std::vector<Level> levels;
	unsigned int current_level = 1;
	int amount_of_levels = 0;

public:

	// Level Selector constructor
	Level_Selector(std::vector<Level> levels);

	// Get the file location of the void and overworld of current level
	Level get_current_level();

	// set current level to next level
	void next_level();

	// set current level to previous level
	void previous_level();

	// Returns the current level number
	int get_level_index();

};

#endif