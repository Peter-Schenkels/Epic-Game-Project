// level_selector.cpp
// Daniel van Eijk-Bos Bulkowski - Peter Schenkels - Rick van Mourik - Noah Titarsole, 31-Jan-2020, Version 3.4
// Contains all functions for the Level_Editor class

#include "level_selector.hpp"


// Constuctor
Level_Selector::Level_Selector(std::vector<Level> levels) :
	levels(levels),
	amount_of_levels(levels.size())
{}

// Get the file location of the void and overworld of current level
Level Level_Selector::get_current_level() {
	return levels[current_level - 1];
}

// Set current level to next level
void Level_Selector::next_level() {
	if (current_level != amount_of_levels) {
		current_level++;
	}
}
// Set current level to previous level
void Level_Selector::previous_level() {
	if (current_level - 1 != 0) {
		current_level--;
	}
}

// Return current level index
int Level_Selector::get_level_index() {
	return current_level;
}