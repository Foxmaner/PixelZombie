#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "zombie.h"
#include "player.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

Bullet createBullet(){
    b.bPosition.x = 100;
    b.bPosition.y = 100;
    b.bPosition.w = 15;
    b.bPosition.h = 5;
    b.shot = false;
    b.lastShotTime = 0, b.currentShotTime = 0;
    b.bVelX = 1, b.bVelY = 1, b.bUpDown = 0;
}

void initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
}

void initWindow(){
    iSDL.win = SDL_CreateWindow("Pixel Zombie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!iSDL.win){
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
    }
    initRenderer(iSDL.win);
}

void initRenderer(SDL_Window* pWin){
    iSDL.renderer = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(iSDL.renderer, 0, 0, 0, 0);
}

void initGame(){
    initSDL();
    initWindow();
    ZombInit.nrOfZombies = 6;
    createAllZombies();
    PlayerInit.nrOfPlayers = 4;
    createAllPlayers();
    createBullet();
}