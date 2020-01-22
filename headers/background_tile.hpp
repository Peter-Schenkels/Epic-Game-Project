#ifndef background_tile_hpp
#define background_tile_hpp

#include "settings.hpp"
#include "drawables.hpp"

class background_tiles {
    Picture * body;

   public:
    background_tiles();

    background_tiles(Picture* body, sf::Vector2f sprite_size):
        body(body)

    {
        body->picture_set_size(sprite_size);
    }

    void draw(sf::RenderWindow &window) {
        sf::Vector2i current_position;

        for (float x = 0; x < WINDOW_SIZE_X; x += body->drawable_get_size().x) {
            for (float y = 0; y < WINDOW_SIZE_Y; y += body->drawable_get_size().y) {
                body->drawable_set_position({x, y});
                body->drawable_update();
                body->drawable_draw(window);
            }
        }

        body->drawable_set_position({0, 0});
    }

    
};



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
///++++++++++++++++++++++++++++++++++++++++
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////


class random_background_tiles {
    std::vector<Picture *> tiles;
    /*int seed[(WINDOW_SIZE_X * WINDOW_SIZE_Y) / 1000];*/
    int seed[1001];

public:
    random_background_tiles() {}


    random_background_tiles(std::map<std::string, Picture *>  &resources, sf::Vector2f sprite_size, std::vector<tile_priority> names) 
    {
        std::cout << "Initialising background tiles..." << std::endl;

        //get all resources
        for (auto name : names) {
            //also changes the size of global size, might be a problem for later
            //short term solution is to change every sprite size before drawing per object
            //TODO: check if it's more effecient to use 2 sprites instead of updating the sprite size
            for (unsigned int i = 0; i < name.priority; i++) {
                resources[name.tile]->picture_set_size(sprite_size);
                tiles.push_back(resources[name.tile]);
            }

        }
        //generate random tilemap
        /*int iterations = ( WINDOW_SIZE_X * WINDOW_SIZE_Y) / 1000;*/
        int iterations = 1000;
        for (int i = 0; i < iterations; i++) {
            seed[i] = rand_range(0, tiles.size() - 1);
        }
        std::cout << "Initialising background tiles completed" << std::endl;
    }


    void draw(sf::RenderWindow &window) {
        sf::Vector2i current_position;
        int nr = 0;
        for (float x = 0; x < 3000; x += tiles[0]->drawable_get_size().x) {
            for (float y = 0; y < 1080; y += tiles[0]->drawable_get_size().y) {

                tiles[seed[nr]]->drawable_set_position({x, y});
                tiles[seed[nr]]->drawable_update();
                tiles[seed[nr]]->drawable_draw(window);
                nr++;
            }
            nr++;
        }
    }

    void set_color(sf::Color color) {
        for (auto& tile : tiles) {
            tile->picture_set_color(color);
        }
    }

    void update(){};

};


#endif
