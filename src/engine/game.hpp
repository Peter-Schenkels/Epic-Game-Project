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

    // Enable this tool to enable the edit and save function
    // of the factory pattern
    bool edit_mode;

    // Sfml window
    sf::RenderWindow window;

    // resource management
    std::map<std::string, Sprite*> resources;

    // event handler
    sf::Event event;

//Objects to be drawn inside the frame
private:

    // Random backbround tile class
    random_background_tiles background;
    Factory factory;
    Player player;

//Constructor
public:

    /// Game constructor (doesnt take any input arguments)
    /// Initialises all the startup events such as loading in the resources that
    Game():
        window({WINDOW_SIZE_X, WINDOW_SIZE_Y}, "window"), 
        factory("factory/save.json"),

        ///Player start position, player size
        player({100,100}, {50,50})

    
    {
        factory.load();
        // factory.toggle_mode();
        window.setFramerateLimit(60);

        std::cout << "Loading textures..." << std::endl;

        resources["Background tile 1"] = new Sprite({0, 0}, {1, 2}, "img/ding1.png");
        resources["Background tile 2"] = new Sprite({0, 0}, {2, 2}, "img/ding2.png");
        resources["Background tile 3"] = new Sprite({0, 0}, {2, 2}, "img/ding3.png");
        resources["Background tile 4"] = new Sprite({0, 0}, {2, 2}, "img/ding4.png");
        resources["hond 1"] = new Sprite({0, 0}, {2, 2}, "img/test2.jpg");
        resources["hond 2"] = new Sprite({0, 0}, {2, 2}, "img/test3.jpeg");

        std::cout << "Loading textures completed" << std::endl;

        
        background.init(resources, {100,100}, {
            "Background tile 1",
            "Background tile 2",
            "Background tile 3",
            "Background tile 4"
        });
        
        player.init(resources["hond 1"]);

        std::cout << "Game ready to launch..." << std::endl;


    }

public:

    /// This function is for handeling all the input 
    /// it parses all the input into an event vaiable
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

    /// This function is for updating all the object
    /// and for calculating any possible collisions
    void update(){

        factory.update();
        player.update();

        /// Checking collision with player for every factory object
        for (int i = 0; i < factory.get_object_count(); i++){
            player.collision(factory.get_object(i)); 
        }

        
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