
#include "game.hpp"

int main() {
    Game game;
    for(;;){
        game.get_input();
        game.update();
        game.draw();
    }
}