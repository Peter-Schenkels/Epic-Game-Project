#include "hitbox.hpp"


hitbox::hitbox(sf::Vector2f position, sf::Vector2f size):
		position(position),
		size(size),
		left(sf::Vector2f{0, size.y-5}),
		right{sf::Vector2f{0, size.y-5}},
		top({size.x - 2, 0}),
		bottom({size.x - 2, 0}),
		box(size)
	{
		left.setPosition(position);
		right.setPosition({position.x + 1 + size.x, position.y});
		top.setPosition(position);
		bottom.setPosition({position.x + 1, position.y + size.y});
		box.setPosition(position);

		left.setOutlineThickness(1.f);
		right.setOutlineThickness(1.f);
		top.setOutlineThickness(1.f);
		bottom.setOutlineThickness(1.f);
	}

void hitbox::update(sf::Vector2f pposition){
    position = pposition;
    left.setPosition(position);
    right.setPosition({position.x+ size.x, position.y});
    top.setPosition(position);
    bottom.setPosition({position.x, position.y + size.y});
    box.setPosition(position);
}

void hitbox::draw(sf::RenderWindow & window){
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
}

bool hitbox::leftSideIntersect(sf::FloatRect collider){
    return left.getGlobalBounds().intersects(collider);
}

bool hitbox::rightSideIntersect(sf::FloatRect collider){
    return right.getGlobalBounds().intersects(collider);
}

bool hitbox::topSideIntersect(sf::FloatRect collider){
    return top.getGlobalBounds().intersects(collider);
}

bool hitbox::bottomSideIntersect(sf::FloatRect collider){
    return bottom.getGlobalBounds().intersects(collider);
}

sf::FloatRect hitbox::getOuterbounds(){
    return box.getGlobalBounds();
}


Player_Hitbox::Player_Hitbox(sf::Vector2f position, sf::Vector2f size):
		position(position),
		size(size),
		left(sf::Vector2f{0, size.y/2}),
		right{sf::Vector2f{0, size.y/2}},
		top({size.x - size.x/8, 0}),
		bottom({size.x - size.x/8, 0}),
		box(size)
	{
		left.setPosition(position);
		right.setPosition({position.x + 1 + size.x, position.y});
		top.setPosition(position);
		bottom.setPosition({position.x + 1, position.y + size.y});
		box.setPosition(position);

		left.setOutlineThickness(1.f);
		right.setOutlineThickness(1.f);
		top.setOutlineThickness(1.f);
		bottom.setOutlineThickness(1.f);
	}

void Player_Hitbox::update(sf::Vector2f pposition){
    position = pposition;
    left.setPosition(position);
    right.setPosition({position.x+ size.x, position.y});
    top.setPosition(position);
    bottom.setPosition({position.x, position.y + size.y});
    box.setPosition(position);
}

void Player_Hitbox::draw(sf::RenderWindow & window){
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
}

bool Player_Hitbox::leftSideIntersect(sf::FloatRect collider){
    return left.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::rightSideIntersect(sf::FloatRect collider){
    return right.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::topSideIntersect(sf::FloatRect collider){
    return top.getGlobalBounds().intersects(collider);
}

bool Player_Hitbox::bottomSideIntersect(sf::FloatRect collider){
    return bottom.getGlobalBounds().intersects(collider);
}

sf::FloatRect Player_Hitbox::getOuterbounds(){
    return box.getGlobalBounds();
}

