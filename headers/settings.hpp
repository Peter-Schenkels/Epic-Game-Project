#pragma once


#ifndef SETTINGS_HPP
#define SETTINGS_HPP


#define WINDOW_SIZE_X 1000/*1920*/
#define WINDOW_SIZE_Y 750/*1080*/
#define SAVE_FILE_LOCATION "objects.json"

#define FRAME_RATE 60

inline int rand_range(int start, int end) {
    return start + (std::rand() % (end - start + 1));
}

#endif