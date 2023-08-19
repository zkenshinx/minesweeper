#ifndef MINESWEEPER_GRID_H
#define MINESWEEPER_GRID_H

#include <stdint.h>

typedef uint8_t layer_t;

#define TILE_EMPTY 0
#define TILE_MINE 1

#define TILE_AVAILABLE 50
#define TILE_FLAG 51

struct Grid {
	int width;
	int height;
	layer_t** back_layer;
	layer_t** front_layer;
};

/**
 * Randomly generates Grid with the given amount of mines.
 * 
 * @param Grid The grid struct to be filled
 * @param width Width of the grid
 * @param height Height of the grid
 * @param mine_count Number of mines places on the grid
*/
void initRandomGrid(struct Grid* grid, int width, int height, int mine_count);

/**
 * Frees all the memory associated with the grid
 * 
 * @param Grid The grid struct to be destroyed
*/
void destroyGrid(struct Grid* grid);

#endif