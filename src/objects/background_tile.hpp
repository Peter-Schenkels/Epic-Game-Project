#ifndef background_tile_hpp
#define background_tile_hpp

#include "object.hpp"
#include "settings.hpp"
#include "sprite.hpp"

class background_tiles : public Object {
    Sprite body;

   public:
    background_tiles();

    background_tiles(std::string location, sf::Vector2f sprite_size) : Object(position, {WINDOW_SIZE_X, WINDOW_SIZE_Y}),
                                                                       body({0, 0}, {1, 1}, location, "background tile")

    {
        body.set_sprite_size(sprite_size);
    }

    void draw(sf::RenderWindow &window) {
        sf::Vector2i current_position;

        for (float x = 0; x < WINDOW_SIZE_X; x += body.get_size().x) {
            for (float y = 0; y < WINDOW_SIZE_Y; y += body.get_size().y) {
                body.set_position({x, y});
                body.update();
                body.draw(window);
            }
        }

        body.set_position({0, 0});
    }

    void update(){};

    json export_to_json(json object) { return "a"; };
};



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
///++++++++++++++++++++++++++++++++++++++++
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////


class random_background_tiles : public Object {
    std::vector<Sprite *> tiles;
    int seed[WINDOW_SIZE_X * WINDOW_SIZE_Y];

   public:
    random_background_tiles() : 
        Object({0, 0}, {WINDOW_SIZE_X, WINDOW_SIZE_Y}) {}

    random_background_tiles(std::vector<Sprite *> &resources, sf::Vector2f sprite_size, std::vector<std::string> names) : 
        Object({0, 0}, {WINDOW_SIZE_X, WINDOW_SIZE_Y})

    {
        init(resources, sprite_size, names);
    }

    void init(std::vector<Sprite *> &resources, sf::Vector2f sprite_size, std::vector<std::string> names) {
        //get all resources
        for (auto sprite : resources) {
            for (auto name : names) {
                if (sprite->get_id() == name) {
                    //also changes the size of global size, might be a problem for later
                    //short term solution is to change every sprite size before drawing per object
                    //TODO: check if it's more effecient to use 2 sprites instead of updating the sprite size
                    sprite->set_sprite_size(sprite_size);
                    tiles.push_back(sprite);
                }
            }
        }
        //generate random tilemap
        int iterations = WINDOW_SIZE_X * WINDOW_SIZE_Y;
        for (int i = 0; i < iterations; i++) {
            seed[i] = rand_range(0, tiles.size() - 1);
        }
    }

    void draw(sf::RenderWindow &window) {
        sf::Vector2i current_position;
        int nr = 0;
        for (float x = 0; x < WINDOW_SIZE_X; x += tiles[0]->get_size().x) {
            for (float y = 0; y < WINDOW_SIZE_Y; y += tiles[0]->get_size().y) {
                tiles[seed[nr]]->set_position({x, y});
                tiles[seed[nr]]->update();
                tiles[seed[nr]]->draw(window);
                nr++;
            }
            nr++;
        }
    }

    void update(){};

    json export_to_json(json object) { return "a"; };
};

#endif