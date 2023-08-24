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

static int isInBounds(struct Grid* grid, int cell_x, int cell_y) {
    return cell_x >= 0 && cell_y >= 0 && cell_x < grid->width && cell_y < grid->height;
}

static int isBomb(struct Grid* grid, int cell_x, int cell_y) {
    return grid->back_layer[cell_x][cell_y] == BACK_TILE_MINE;
}

// Currently dummy version
static void placeMines(layer_t** back_layer, int width, int height, int mine_count) {
    for (int i = 0; i < mine_count; ++i) {
        int x = rand() % width;
        int y = rand() % height;
        while (back_layer[x][y] == BACK_TILE_MINE) {
            x = rand() % width;
            y = rand() % height;
        }
        back_layer[x][y] = BACK_TILE_MINE;
    }
}

void initRandomGrid(struct Grid* grid, int width, int height, int mine_count) {
    grid->width = width;
    grid->height = height;
    grid->back_layer = allocateLayer(width, height);
    grid->front_layer = allocateLayer(width, height);
    for (int i = 0; i < width; ++i) 
        for (int j = 0; j < height; ++j) 
            grid->front_layer[i][j] = FRONT_TILE_AVAILABLE;
    placeMines(grid->back_layer, width, height, mine_count);
}

void destroyGrid(struct Grid* grid) {
    deallocateLayer(grid->back_layer, grid->height);
    deallocateLayer(grid->front_layer, grid->height);
}

int countBombsAround(struct Grid* grid, int cell_x, int cell_y) {
    int bomb_count = 0;
    for (int i = cell_x - 1; i <= cell_x + 1; ++i) {
        for (int j = cell_y - 1; j <= cell_y + 1; ++j) {
            if (!isInBounds(grid, i, j) || (i == cell_x && j == cell_y))
                continue;
            bomb_count += isBomb(grid, i, j);
        }
    }
    return bomb_count;
}

static int dir_x[4] = {-1, 1, 0, 0};
static int dir_y[4] = {0, 0, -1, 1};

void gridExpandRecursive(struct Grid* grid, int cell_x, int cell_y, int depth) {
    grid->front_layer[cell_x][cell_y] = countBombsAround(grid, cell_x, cell_y);
    for (int dir = 0; dir < 4; ++dir) {
        int next_cell_x = cell_x + dir_x[dir];
        int next_cell_y = cell_y + dir_y[dir];
        if (isInBounds(grid, next_cell_x, next_cell_y) && 
            !isBomb(grid, next_cell_x, next_cell_y) &&
            grid->front_layer[next_cell_x][next_cell_y] == FRONT_TILE_AVAILABLE && 
            depth > 1)
            gridExpandRecursive(grid, next_cell_x, next_cell_y, rand() % (depth - 1));
    }
}

void clickGrid(struct Grid* grid, int cell_x, int cell_y) {
    if (grid->back_layer[cell_x][cell_y] == BACK_TILE_MINE) {
        grid->front_layer[cell_x][cell_y] = FRONT_TILE_EXPLODED;
    } else {
        int depth = rand() % 15;
        gridExpandRecursive(grid, cell_x, cell_y, depth);
    }
}