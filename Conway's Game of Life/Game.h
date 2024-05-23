#pragma once

#include <iostream>
#include <vector>

class Game {
private:

	int width;
	int height;

	std::vector<std::vector<bool>> cGrid;	// current grid
	std::vector<std::vector<bool>> pGrid;	// previous grid

	int cellSize;	// side length of each cell

	int speed;		// max game refreshes per second (not fps)
	int fps;		// max loops per second

	bool quit;		// 
	bool paused;	// when true, the player can make changes but the game is not running

	void loop();

public:
	Game(int width, int height, int cellSize, int speed, int fps);
};