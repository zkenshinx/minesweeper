#include <stdlib.h>
#include <string.h>
#include "grid.h"

static layer_t** allocateLayer(int width, int height) {
    layer_t** layer_ptr = malloc(height * sizeof(layer_t *));
    for (int i = 0; i < height; ++i) {
        layer_ptr[i] = malloc(width * sizeof(layer_t));
        memset(layer_ptr[i], 0, width * sizeof(layer_t));
    }
    return layer_ptr;
}

static void deallocateLayer(layer_t** layer_ptr, int height) {
    for (int i = 0; i < height; ++i) {
        free(layer_ptr[i]);
    }
    free(layer_ptr);
}

// Currently dummy version
static void placeMines(layer_t** back_layer, int width, int height, int mine_count) {
    for (int i = 0; i < mine_count; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        while (back_layer[x][y] == TILE_MINE) {
            x = rand() % width;
            y = rand() % height;
        }
        back_layer[x][y] = TILE_MINE;
    }
}

void initRandomGrid(struct Grid* grid, int width, int height, int mine_count) {
    grid->width = width;
    grid->height = height;
    grid->back_layer = allocateLayer(width, height);
    grid->front_layer = allocateLayer(width, height);
    placeMines(grid->back_layer, width, height, mine_count);
}

void destroyGrid(struct Grid* grid) {
    deallocateLayer(grid->back_layer, grid->height);
    deallocateLayer(grid->front_layer, grid->height);
}