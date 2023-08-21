#include "textures.h"

#define TEXTURES_COUNT 13

SDL_Texture** loadTextures(SDL_Renderer* renderer) {
    SDL_Texture** textures = malloc(TEXTURES_COUNT * sizeof(SDL_Texture*));
    textures[0] = IMG_LoadTexture(renderer, "../assets/0.png");
    textures[1] = IMG_LoadTexture(renderer, "../assets/1.png");
    textures[2] = IMG_LoadTexture(renderer, "../assets/2.png");
    textures[3] = IMG_LoadTexture(renderer, "../assets/3.png");
    textures[4] = IMG_LoadTexture(renderer, "../assets/4.png");
    textures[5] = IMG_LoadTexture(renderer, "../assets/5.png");
    textures[6] = IMG_LoadTexture(renderer, "../assets/6.png");
    textures[7] = IMG_LoadTexture(renderer, "../assets/7.png");
    textures[8] = IMG_LoadTexture(renderer, "../assets/8.png");

    textures[9] = IMG_LoadTexture(renderer, "../assets/available.png");
    textures[10] = IMG_LoadTexture(renderer, "../assets/flag.png");
    textures[11] = IMG_LoadTexture(renderer, "../assets/mine.png");
    textures[12] = IMG_LoadTexture(renderer, "../assets/mine_exploded.png");
    
    return textures;
}

void destroyTextures(SDL_Texture** textures) {
    for (int i = 0; i < TEXTURES_COUNT; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
    free(textures);
}