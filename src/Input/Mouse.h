#ifndef _INCLUDE_MOUSE
#define _INCLUDE_MOUSE

class Mouse {
public:
    void poll();

    int16_t getXPos();
    int16_t getYPos();

    int16_t getXDelta();
    int16_t getYDelta();

    int16_t getButtonState;
private:

    int16_t xPos, yPos, xDelta, yDelta;
    int16_t buttonState;
}

#endif
