#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Screen.h"
#include "Mouse.h"

class Game {
public:
    static Game& getInstance();

	Screen* getScreen();
    Mouse* getMouse();

private:
    Game();
    Game(Game const &);

    void operator=(Game const &);

	Screen screen;
    Mouse mouse;
};

#endif
