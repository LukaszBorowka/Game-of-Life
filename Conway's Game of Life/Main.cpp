/*
* Rules:
	1. Any alive cell with fewer than two live neighbors dies, as if by underpopulation.
	2. Any alive cell with two or three live neighbors lives on to the next generation.
	3. Any alive cell with more than three live neighbors dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

#include <iostream>
#include <SDL.h>

class Game {
private:
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Event event;

	SDL_Point gridSize;
	SDL_Point windowSize;
	SDL_Point focusCenter;

	int cellSize; // can be changed by zooming in / out
	int gameSpeed; // how many game cycles per second
	int gameFPS; // fps limit

	bool isPaused; // when pased, changes can be made to the grid, but the game is not running
	bool exitGame = false;

public:
	Game(int windowWidth, int windowHeight, int cellSize, int speed, int fps) {
		this->windowSize.x = windowWidth;
		this->windowSize.y = windowHeight;
		this->cellSize = cellSize;
		this->gameSpeed = speed;
		this->gameFPS = fps;


		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cerr << "SDL Init error: " << SDL_GetError() << "\n";
			return;
		}

		this->window = SDL_CreateWindow(
			"Game of Life",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			this->windowSize.x,
			this->windowSize.y,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
		);

		if (this->window == nullptr) {
			std::cerr << "SDL Create Window Error: " << SDL_GetError() << "\n";
			SDL_Quit();
			return;
		}

		this->renderer = SDL_CreateRenderer(
			this->window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);

		if (this->renderer == nullptr) {
			std::cerr << "SDL Create Renderer Error: " << SDL_GetError() << "\n";
			SDL_DestroyWindow(this->window);
			SDL_Quit();
			return;
		}

		SDL_ShowSimpleMessageBox(
			NULL,
			"Welcome!",
			u8"Welcome to my implementation of the Conway's Game of Life.\n\nInstructions:\n - Use the spacebar to pause and unpause\n - You can make changes to the grid when the game is paused by clicking on the cells\n - When paused, use the P key to go step by step\n - You can zoom in and out using the +, - buttons\n - Use the arrow keys on your keyboard to move around the board\n\nHave fun!\nMade by Łukasz Borówka",
			this->window);


		// ...


		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}
};

int main(int argc, char* args[]) {
	{
		Game game(50, 30, 15, 5, 60);
	}
	return EXIT_SUCCESS;
}