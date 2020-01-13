
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "sprite.hpp"
#include <SFML/Graphics.hpp>

class Player : public Object
{

private:
    sf::Vector2f speed = {0, 0};
    Sprite *body;
    Player_Hitbox collision_box;
    float gravity = 0.5;
    float resistance = 2;
    bool floating = false;
    bool on_ground = false;

public:
    Player(sf::Vector2f position, sf::Vector2f size) : 
        Object(position, size),
        collision_box(position, size) 
 
    {

    }

    Player(sf::Vector2f position, sf::Vector2f size, Sprite *sprite) : 
        Object(position, size),
        collision_box(position, size) 
    {
        init(sprite);
    }

    void init(Sprite *sprite)
    {
        body = sprite;
        body->set_sprite_size(size);
        body->set_position(position);
    }

    void draw(sf::RenderWindow &window)
    {
        body->draw(window);
    }

    void update()
    {
        if (!floating){
            speed.y += gravity;
            position += speed;
        }

        collision_box.update(position);
        body->set_position(position);
        body->update();
    }


    void set_static(bool boolean){
        floating = boolean;
    }


    //handles all input events
    void input(sf::Event event){
        //if key up is pressed: jump!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && speed.y == -0.5){
            speed.y = -20.01;
        } 
        //if key left is pressed: move left!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            speed.x = -7;
        } else if (speed.x < 0) {
            speed.x += 7;
            if (speed.x > 0){
                speed.x = 0;
            }
        }
        //if key right is pressed: move right!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            speed.x = 7;
        } else if (speed.x > 0) {
            speed.x -= 7;
            if (speed.x < 0){
                speed.x = 0;
            }
        }
    }

    //collision detection between a player and a sf::FloatRect
    void collision(Object* object)
    {
        //check if a sf::FloatRect collides with the right  or left side of the hitbox
        if (collision_box.leftSideIntersect(object->get_boundaries()))
        {
            speed.x = -0.5;
            position.x = object->get_boundaries().left + object->get_boundaries().width;

        }
        else if (collision_box.rightSideIntersect(object->get_boundaries()))
        {
            speed.x = -0;
            position.x = object->get_boundaries().left - size.x;

        }
        //check if a sf::FloatRect collides with the bottom  or top of the hitbox
        else if (collision_box.bottomSideIntersect(object->get_boundaries()) or
            collision_box.topSideIntersect(object->get_boundaries()))
        {
            position.y = object->get_boundaries().top - size.y;
            speed.y = -0.5;
            on_ground = true;
        } else {
            on_ground = false;
        }

    }

    json export_to_json(json object) { return ""; }
};

#endif