/*
* Rules:
	1. Any alive cell with fewer than two live neighbors dies, as if by underpopulation.
	2. Any alive cell with two or three live neighbors lives on to the next generation.
	3. Any alive cell with more than three live neighbors dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

#include <iostream>
#include <vector>
#include <optional>
#include <SDL.h>

struct Float_Point {
	float x;
	float y;
};

class Game {
private:
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Event event;

	SDL_Point gridSize;
	SDL_Point windowSize;
	
	Float_Point focusPoint;

	int cellSize; // can be changed by zooming in / out
	int gameSpeed; // how many game cycles per second
	int gameFPS; // fps limit

	bool isPaused = true; // when paused, changes can be made to the grid, but the game is not running
	bool exitGame = true;

	std::vector <std::vector <bool>> grid;

	SDL_Point What_Cell_Am_I_In(SDL_Point p) {
		if (p.x < 0 || p.y < 0 || p.x >= windowSize.x || p.y >= windowSize.y) return {-1, -1};
		
		SDL_Point cell;
		cell.x = (int(focusPoint.x * float(cellSize)) + (p.x - (windowSize.x / 2))) / cellSize;
		cell.y = (int(focusPoint.y * float(cellSize)) + (p.y - (windowSize.y / 2))) / cellSize;

		if (cell.x < 0 || cell.y < 0 || cell.x >= gridSize.x || cell.y >= gridSize.y) return {-1, -1};

		return cell;
	}

	SDL_Point Get_Cell_Top_Left_Coord(SDL_Point cell) {
		if (cell.x < 0 || cell.y < 0 || cell.x >= gridSize.x || cell.y >= gridSize.y) return { -1, -1 };

		SDL_Point p;
		p.x = int((float(cell.x) - focusPoint.x) * float(cellSize)) + (windowSize.x / 2);
		p.y = int((float(cell.y) - focusPoint.y) * float(cellSize)) + (windowSize.y / 2);

		return p;
	}

	void Draw_Game() {
		//clear window
		SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF);
		SDL_RenderClear(renderer);

		



		SDL_RenderPresent(this->renderer);
	}

	void Handle_Events() {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				exitGame = true;
				break;
			}
		}
	}

public:
	Game(int windowWidth, int windowHeight, int gridWidth, int gridHeight, int cellSize, int speed, int fps) {
		this->windowSize.x = windowWidth;
		this->windowSize.y = windowHeight;
		this->cellSize = cellSize;
		this->gameSpeed = speed;
		this->gameFPS = fps;
		this->gridSize.x = gridWidth;
		this->gridSize.y = gridHeight;

		this->focusPoint.x = float(this->gridSize.x) / 2;
		this->focusPoint.y = float(this->gridSize.y) / 2;


		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cerr << "SDL Init error: " << SDL_GetError() << "\n";
			return;
		}

		this->window = SDL_CreateWindow(
			"Game of Life | PAUSED",
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

		this->grid.resize(this->gridSize.x);
		for (auto& row : this->grid) row.resize(this->gridSize.y, false);

		this->Draw_Game();

		SDL_ShowSimpleMessageBox(
			NULL,
			"Welcome!",
			u8"Welcome to my implementation of the Conway's Game of Life.\n\nInstructions:\n - Use the spacebar to pause and unpause\n - You can make changes to the grid when the game is paused by clicking on the cells\n - When paused, use the P key to go step by step\n - You can zoom in and out using the +, - buttons\n - Use the arrow keys on your keyboard to move around the board\n\nHave fun!\nMade by Łukasz Borówka",
			this->window
		);

		this->exitGame = false;
	}

	~Game() {
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}

	void Game_Loop() {
		while (!this->exitGame) {
			this->Handle_Events();
			this->Draw_Game();
		}
	}
};

int main(int argc, char* args[]) {
	{
		Game game(1000, 750, 1000, 1000, 15, 5, 60);
		game.Game_Loop();
	}
	return EXIT_SUCCESS;
}