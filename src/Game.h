#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Screen.h"

class Game {
public:
    static Game& getInstance();
	
	Screen* getScreen();

private:
    Game();
    Game(Game const &);
    
    void operator=(Game const &);
	
	Screen screen;
};

#endif