#ifndef gameInit_h
#define gameInit_h

#include <stdio.h>

struct InitSDL{
    SDL_Window* win;
    SDL_Renderer* renderer;
};typedef struct InitSDL InitSDL;
InitSDL iSDL;

struct Background_Tiles{
    SDL_Texture *mTiles;
    SDL_Rect gTiles[32];
}; typedef struct Background_Tiles Background_Tiles;
Background_Tiles backTiles;

void initSDL();
void initWindow();
void initRenderer(SDL_Window* pWin);
void initGame();

#endif