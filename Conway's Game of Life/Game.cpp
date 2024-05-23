#include "Game.h"

void Game::loop() {
	while (!this->quit) {

	}
}

Game::Game(int width, int height, int cellSize, int speed, int fps) {
	this->width = width;
	this->height = height;
	this->cellSize = cellSize;
	this->speed = speed;
	this->fps = fps;
	cGrid.resize(height, std::vector<bool>(width, false));
	this->loop();
}