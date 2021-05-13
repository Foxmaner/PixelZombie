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

struct Heart{
    SDL_Texture *mHeart;
    SDL_Rect gHeart[1];
    SDL_Rect hPosition[3];
};typedef struct Heart Heart;
Heart h;
Heart createHeart();

struct isGameInitOrOver{
    bool initedGame;
    bool gameOver;
};typedef struct isGameInitOrOver IGIO;
IGIO GIO;

void initSDL();
void initWindow();
void initRenderer(SDL_Window* pWin);
void initAudio();
void initGame();

#endif