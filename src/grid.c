#include <stdlib.h>
#include "grid.h"

static layer_t** allocateLayer(int width, int height) {
    layer_t** layer_ptr = malloc(height * sizeof(layer_t *));
    for (int i = 0; i < height; ++i) {
        layer_ptr[i] = malloc(width * sizeof(layer_t));
    }
    return layer_ptr;
}

static void deallocateLayer(layer_t** layer_ptr, int height) {
    for (int i = 0; i < height; ++i) {
        free(layer_ptr[i]);
    }
    free(layer_ptr);
}

void initRandomGrid(struct Grid* grid, int width, int height, int mine_count) {
    grid->width = width;
    grid->height = height;
    grid->back_layer = allocateLayer(width, height);
    grid->front_layer = allocateLayer(width, height);
}

void destroyGrid(struct Grid* grid) {
    deallocateLayer(grid->back_layer, grid->height);
    deallocateLayer(grid->front_layer, grid->height);
}