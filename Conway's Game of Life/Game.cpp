#include "Game.h"

void Game::renderGrid() {
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->renderer);

	SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	// vertical lines
	for (int i = 1; i < this->gridSize.x; i++)
		SDL_RenderDrawLine(
			this->renderer,
			i * (this->cellSize + 1) - 1, 0,
			i * (this->cellSize + 1) - 1, this->windowSize.y - 1);
	// horizontal lines
	for (int i = 1; i < this->gridSize.y; i++)
		SDL_RenderDrawLine(
			this->renderer,
			0, i * (this->cellSize + 1) - 1,
			this->windowSize.x - 1, i * (this->cellSize + 1) - 1);
}

void Game::handleEvents() {
	while (SDL_PollEvent(&this->event)) {
		switch (this->event.type) {
		case SDL_QUIT:
			this->running = false;
			break;

		default:
			break;
		}
	}
}

void Game::loop() {
	while (this->running) {
		this->handleEvents();
		this->renderGrid();
		SDL_RenderPresent(this->renderer);
	}
}

Game::Game(int width, int height, int cellSize, int speed, int fps) {
	this->gridSize.x = width;
	this->gridSize.y = height;
	this->cellSize = cellSize;
	this->speed = speed;
	this->fps = fps;
	cGrid.resize(height, std::vector<bool>(width, false));

	this->windowSize.x = width * (cellSize + 1) - 1;
	this->windowSize.y = height * (cellSize + 1) - 1;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Init error: " << SDL_GetError() << "\n";
		return;
	}

	this->window = SDL_CreateWindow(
		"Conway's Game of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		this->windowSize.x,
		this->windowSize.y,
		SDL_WINDOW_SHOWN);
	if (this->window == nullptr) {
		std::cerr << "SDL Create Window error: " << SDL_GetError() << "\n";
		SDL_Quit();
		return;
	}

	this->renderer = SDL_CreateRenderer(
		this->window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == nullptr) {
		std::cerr << "SDL Create Renderer error: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		return;
	}

	SDL_ShowSimpleMessageBox(
		NULL,
		"Game started",
		"Use space to play/pause and right arrow to go step by step when paused.",
		this->window);

	this->running = true;
	this->paused = true;

	this->loop();

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}