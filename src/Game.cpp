#include "Game.h"

Game::Game() {}

Game& Game::getInstance() {
	static Game instance;

	return instance;
}

Screen* Game::getScreen() {
	return &screen;
}

Mouse* Game::getMouse() {
    return &mouse;
}
