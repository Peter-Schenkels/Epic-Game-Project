#pragma once


#ifndef SETTINGS_HPP
#define SETTINGS_HPP


//#define WINDOW_SIZE_X 1000
//#define WINDOW_SIZE_Y 750
#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define SAVE_FILE_LOCATION "objects.json"

#define FRAME_RATE 60

inline int rand_range(int start, int end) {
    return start + (std::rand() % (end - start + 1));
}

struct tile_priority {
    std::string tile;
    unsigned int priority;

    tile_priority(std::string t, int p) :
        tile(t) /* ,
        priority(priority) */
    {
        /* if (p < 0) {
            priority = 0;
        }
        else {
            priority = p;
        } */
        p < 0 ? priority = 0 : priority = p;
    }
};

#endif