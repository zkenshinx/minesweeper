#ifndef MINESWEEPER_TEXTURES_H
#define MINESWEEOER_TEXTURES_H

#include <SDL2/SDL_image.h>

SDL_Texture** loadTextures();
void destroyTextures(SDL_Texture** textures);

#endif