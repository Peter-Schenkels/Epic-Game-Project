#include "level_selector.hpp"

Level_Selector::Level_Selector(std::vector<Level> levels) :
	levels(levels)
{
	for (auto level : levels) {
		amount_of_levels++;
	}
}

// Get the file location of the void and overworld of current level
Level Level_Selector::get_current_level() {
	return levels[current_level - 1];
}

// set current level to next level
void Level_Selector::next_level() {
	if (current_level != amount_of_levels) {
		current_level++;
	}
}
// set current level to previous level
void Level_Selector::previous_level() {
	if (current_level - 1 != 0) {
		current_level--;
	}
}

int Level_Selector::get_level_index() {
	return current_level;
}