#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main() {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
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

	bool game_finished = false;
	SDL_Event event;
	while (!game_finished) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_finished = true;
			}
		}
	}

	return 0;
}
