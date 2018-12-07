#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Screen.h"
#include "Mouse.h"

class Game {
public:
    /** Initializes a Game object if one has not
    *   already been initialized, and returns it */
    static Game& getInstance();

    /// Returns a pointer to the \ref Screen.
	Screen* getScreen();
    /// Returns a pointer to the \ref Mouse.
    Mouse* getMouse();

private:
    Game();
    Game(Game const &);

    void operator=(Game const &);

	Screen screen;
    Mouse mouse;
};

#endif
