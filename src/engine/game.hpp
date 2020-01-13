#include <iostream>
#include "factory.hpp"
#include "settings.hpp"
#include <SFML/Graphics.hpp>
#include "objects/background_tile.hpp"
#include "player.hpp"

#ifndef GAME_HPP
#define GAME_HPP

class Game{

///Essentials for rendering the game
private:

    sf::RenderWindow window;
    bool edit_mode;
    Factory factory;
    std::vector<Sprite*> resources;
    sf::Event event;

//Constructor
public:

    Game():
        window({WINDOW_SIZE_X, WINDOW_SIZE_Y}, "window"), 
        factory("factory/save.json"),
        ///Player start position, player size
        player({100,100}, {50,50})

    
    {
        factory.load();
        // factory.toggle_mode();
        window.setFramerateLimit(60);

        resources.push_back(new Sprite({0, 0}, {1, 2}, "img/ding1.png", "background tile 1"));
        resources.push_back(new Sprite({0, 0}, {2, 2}, "img/ding2.png", "background tile 2"));
        resources.push_back(new Sprite({0, 0}, {2, 2}, "img/ding3.png", "background tile 3"));
        resources.push_back(new Sprite({0, 0}, {2, 2}, "img/ding4.png", "background tile 4"));
        resources.push_back(new Sprite({0, 0}, {2, 2}, "img/test2.jpg", "hond 1"));
        resources.push_back(new Sprite({0, 0}, {2, 2}, "img/test3.jpeg", "hond 2"));

        background.init(resources, {100,100}, {
            "background tile 1",
            "background tile 2",
            "background tile 3",
            "background tile 4"
        });
        
        player.init(resources[4]);

    }

//Objects to be drawn inside the frame
private:
    random_background_tiles background;
    Player player;


//Main gameloop
public:

    void get_input(){
        

        while (window.pollEvent(event))
        {
            factory.select(event);
            player.input(event);
            if (event.type == sf::Event::Closed)
            {
                factory.save();
                window.close();
            }
        }

    }

    void update(){

        factory.update();
        player.update();
        player.collision(factory.get_object(0)); 
        player.collision(factory.get_object(1)); 
        
    }

    void draw(){

        window.clear();
        background.draw(window);
        player.draw(window);

        factory.draw(window);
        window.display();

    }





};




#endif