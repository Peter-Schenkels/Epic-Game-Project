//
// Created by pieper on 01-01-20.
//

#ifndef SFML_TEMPLATES_OBJECT_HPP
#define SFML_TEMPLATES_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "jsonsfml.hpp"
#include "hitbox.hpp"
#include <iostream>

using namespace nlohmann;





///\brief 
/// an abstract base class of multiple drawable shapes
class Object {

protected:

    sf::Vector2f position; 
    sf::Vector2f size;
    bool selected = false;

    std::string id;

public:

    Object(sf::Vector2f position, sf::Vector2f size);

    virtual void update() = 0;

    virtual void draw(sf::RenderWindow & window) = 0;

    void move(sf::Vector2f new_position){ position += new_position; }

    void set_position(sf::Vector2f new_position){ position = new_position; }

    sf::Vector2f get_position(){ return position; }

    sf::Vector2f get_size(){ return size; }

    sf::FloatRect get_boundaries();

    bool get_selected(){ return selected; };

    void select(sf::Event event);
    


    virtual json export_to_json(json object) = 0;

};



#endif //SFML_TEMPLATES_OBJECT_HPP
