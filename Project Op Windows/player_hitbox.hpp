#pragma once

#ifndef PLAYER_HITBOX
#define PLAYER_HITBOX

#include "drawables.hpp"

class Player_Hitbox {

public:
	sf::Vector2f position, size;
	sf::RectangleShape left, right, top, bottom;
	sf::RectangleShape box;

	Player_Hitbox(sf::Vector2f position, sf::Vector2f size);

	void update(sf::Vector2f pposition);

	void draw(sf::RenderWindow& window);

	bool leftSideIntersect(sf::FloatRect collider);

	bool rightSideIntersect(sf::FloatRect collider);

	bool topSideIntersect(sf::FloatRect collider);

	bool bottomSideIntersect(sf::FloatRect collider);

	sf::FloatRect getOuterbounds();



};


#endif