#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "grid.h"
#include "textures.h"

#define TILE_SIZE 15
#define GRID_WIDTH 9
#define GRID_HEIGHT 9
#define GRID_PX 30

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		GRID_WIDTH * GRID_PX,
		GRID_HEIGHT * GRID_PX,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, 
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (renderer == NULL) {
		fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	struct Grid grid;
	initRandomGrid(&grid, GRID_WIDTH, GRID_HEIGHT, 10);
	SDL_Texture** textures = loadTextures(renderer);

	bool game_finished = false;
	SDL_Event event;
	while (!game_finished) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_finished = true;
			}
		}
		SDL_RenderClear(renderer);

		for (int i = 0; i < grid.width; ++i) {
			for (int j = 0; j < grid.height; ++j) {
				SDL_Rect dstrect;
				dstrect.x = i * GRID_PX;
				dstrect.y = j * GRID_PX;
				dstrect.w = GRID_PX;
				dstrect.h = GRID_PX;
				SDL_RenderCopy(renderer, textures[grid.front_layer[i][j]], NULL, &dstrect);
			}
		}

		SDL_RenderPresent(renderer);
	}

	destroyTextures(textures);
	destroyGrid(&grid);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
