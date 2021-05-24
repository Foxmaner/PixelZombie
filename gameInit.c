#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "gameEvent.h"
#include "gameInit.h"
#include "gameMedia.h"
#include "zombie.h"
#include "player.h"
#include "menu.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

GameTimer initTime(){
    timer.second = 0;
    timer.minute = 0;
    timer.hour = 0;
    timer.now = 0;
    timer.before = 0;
}

Bullet createBullet(){
    b.bPosition.x = 100;
    b.bPosition.y = 100;
    b.bPosition.w = 15;
    b.bPosition.h = 5;
    b.shot = false;
    b.lastShotTime = 0, b.currentShotTime = 0;
    b.bVelX = 1, b.bVelY = 1, b.bUpDown = 0;
}

Heart createHeart(){
    for(int i = 0; i < 3; i++){
        h.hPosition[i].x = 432 + (i * 55);
        h.hPosition[i].y = 5;
        h.hPosition[i].w = 50;
        h.hPosition[i].h = 50;
    }
}

void initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) != 0){
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

void initAudio(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        printf("Error: %s", Mix_GetError());
}

void startGameTimer(){
    if(msTimer(&timer.now, &timer.before, 1000)){
        timer.second++;
        if(timer.second == 60){
            timer.second = 0;
            timer.minute += 1;
        }
        if(timer.minute == 60){
            timer.minute = 0;
            timer.hour += 1;
        }
        if(timer.hour == 24){
            timer.second = 0;
            timer.minute = 0;
            timer.hour = 0;
        }
    }
}

void initGame(){
    if(!GIO.initedGame){
        initSDL();
        initWindow();
        initAudio();
        GIO.initedGame = true;
    }
    initTime();
    createHeart();
    ZombInit.nrOfZombies = 6;
    createAllZombies();

    PlayerInit.nrOfPlayers = 4;


    createAllPlayers();
    createBullet();
    loadMedia(&iSDL, &backTiles, &ZombInit, &PlayerInit, &b, &h, &MenuInit);
    Mix_HaltMusic();
    playBgMenuMusic();
    GIO.gameOver = false;
}