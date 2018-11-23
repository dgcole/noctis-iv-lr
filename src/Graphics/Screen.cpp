#include "Screen.h"

Screen::Screen() {
	frontBuffer = (uint8_t huge*) 0xDC000;
	backBuffer = (uint8_t huge*) 0xF2000;
}

uint8_t huge* Screen::getFrontBuffer() {
	return frontBuffer;
}

uint8_t huge* Screen::getBackBuffer() {
	return backBuffer;
}
