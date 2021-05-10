#ifndef gameInit_h
#define gameInit_h

#include <stdio.h>
#include <stdbool.h>
#include "menu.h"

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

struct Bullet{
    SDL_Texture *mBullet;
    SDL_Rect gBullet[1];
    SDL_Rect bPosition;
    bool shot;
    int lastShotTime , currentShotTime;
    int bVelX, bVelY, bUpDown;
};typedef struct Bullet Bullet;
Bullet b;

Bullet createBullet();
int renderMenu(int Buttonpressed);
void initSDL();
void initWindow();
void initRenderer(SDL_Window* pWin);
void initGame();

#endif