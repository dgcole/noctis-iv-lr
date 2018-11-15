#ifndef _INCLUDE_SCREEN
#define _INCLUDE_SCREEN

#include "noctis-d.h"

class Screen {
public:
    Screen();
    
    uint8_t huge* getFrontBuffer();
    uint8_t huge* getBackBuffer();
private:
    uint8_t huge* frontBuffer;
    uint8_t huge* backBuffer;
};

#endif
