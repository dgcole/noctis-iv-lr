#include "Mouse.h"

void Mouse::poll() {
    union REGS regs;
    regs.x.ax = MOUSE_READ_MOTION;
    int86(INTERRUPT_MOUSE, &regs, &regs);

    xDelta = regs.x.cx;
    yDelta = regs.x.dx;

    xPos += xDelta;
    yPos += yDelta;

    regs.x.ax = MOUSE_READ_PRESS;
    int86(INTERRUPT_MOUSE, &regs, &regs);

    if (regs.x.ax != 0) {
        buttonState = regs.x.ax;
    } else {
        buttonState = 0;
    }
}

/*
    Check that the mouse is present and supported, and initialize the driver by
    emptying the movement driver.
 */

int8_t Mouse::init() {
    union REGS regs;
    regs.x.ax = MOUSE_READ_STATUS;
    int86(INTERRUPT_MOUSE, &regs, &regs);

    if (regs.x.ax == 0) {
        return 0;
    } else {
        // Here we read in the mouse data to reset it for the first real poll.
        regs.x.ax = MOUSE_READ_MOTION;
        int86(INTERRUPT_MOUSE, &regs, &regs);
        regs.x.ax = MOUSE_READ_PRESS;
        int86(INTERRUPT_MOUSE, &regs, &regs);
        return 1;
    }
}

int16_t Mouse::getXPos() {
    return xPos;
}

int16_t Mouse::getYPos() {
    return yPos;
}

int16_t Mouse::getXDelta() {
    return xDelta;
}

int16_t Mouse::getYDelta() {
    return yDelta;
}

int16_t Mouse::getButtonState() {
    return buttonState;
}
