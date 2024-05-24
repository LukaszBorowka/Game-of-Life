#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

class Game {
private:

	SDL_Point gridSize;
	SDL_Point windowSize;

	std::vector<std::vector<bool>> cGrid;	// current grid
	std::vector<std::vector<bool>> pGrid;	// previous grid

	int cellSize;	// side length of each cell	

	int speed;		// max game refreshes per second (not fps)
	int fps;		// max loops per second

	bool running;	// 
	bool paused;	// when true, the player can make changes but the game is not running

	bool clicking = false;

	int prevClickedX = -1, prevClickedY = -1;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Point mousePoint;
	SDL_Event event;

	void renderCells();
	void renderGrid();
	void handleEvents();
	void loop();

public:
	Game(int width, int height, int cellSize, int speed, int fps);
};