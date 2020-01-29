#ifndef LEVEL_SELECTOR_HPP
#define LEVEL_SELECTOR_HPP

#include <string>
#include <vector>

// Level class to hold overwolrd file location and void file location
class Level {

public:
	std::string voidworld;
	std::string overworld;

	Level(std::string overworld, std::string voidworld) :
		overworld(overworld),
		voidworld(voidworld)
	{}

};


// Class to load and choose levels easily
class Level_Selector {

	std::vector<Level> levels;
	unsigned int current_level = 1;
	int amount_of_levels = 0;

public: 

	// Level Selector constructor
	Level_Selector(std::vector<Level> levels):
		levels(levels)
	{
		for (auto level : levels) {
			amount_of_levels++;
		}
	}

	// Get the file location of the void and overworld of current level
	Level get_current_level() {
		return levels[current_level-1];
	}

	// set current level to next level
	void next_level() {
		if (current_level != amount_of_levels) {
			current_level++;
		}
	}
	// set current level to previous level
	void previous_level() {
		if (current_level-1 != 0) {
			current_level--;
		}
	}

	int get_level_index() {
		return current_level;
	}

};

#endif