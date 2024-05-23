/*
* Rules:
	1. Any alive cell with fewer than two live neighbors dies, as if by underpopulation.
	2. Any alive cell with two or three live neighbors lives on to the next generation.
	3. Any alive cell with more than three live neighbors dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

#include "Game.h"

int main(int argc, char* args[]) {
	{
		Game game(50, 30, 15, 5, 60);
	}

	return EXIT_SUCCESS;
}