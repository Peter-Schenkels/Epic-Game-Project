#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#define WINDOW_SIZE_X 1500
#define WINDOW_SIZE_Y 1000


inline int rand_range(int start, int end){
    return start + ( std::rand() % ( end - start + 1 ) );
}



#endif 