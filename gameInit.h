#ifndef gameInit_h
#define gameInit_h

#include <stdio.h>

struct InitSDL{
    SDL_Window* win;
    SDL_Renderer* renderer;
    int ok;
};typedef struct InitSDL InitSDL;

InitSDL iSDL;

void initSDL();
void initWindow();
void initRenderer(SDL_Window* pWin);
void initGame();

#endif