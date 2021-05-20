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

//Creates inital time values for in-game clock
GameTimer initTime(){
    timer.second = 0;
    timer.minute = 0;
    timer.hour = 0;
    timer.now = 0;
    timer.before = 0;
}

//Creates positions for healthbar
Heart createHeart(){
    for(int i = 0; i < 3; i++){
        h.hPosition[i].x = 432 + (i * 55);
        h.hPosition[i].y = 5;
        h.hPosition[i].w = 50;
        h.hPosition[i].h = 50;
    }
}

//Creates inital values for the bullet
Bullet createBullet(){
    b.bPosition.x = 100;
    b.bPosition.y = 100;
    b.bPosition.w = 15;
    b.bPosition.h = 5;
    b.shot = false;
    b.lastShotTime = 0, b.currentShotTime = 0;
    b.bVelX = 1, b.bVelY = 1, b.bUpDown = 0;
}

//Initilizes SDL VIDEO, TIMER & AUDIO
void initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
}

//Initilizes window and calls to initilize renderer
void initWindow(){
    iSDL.win = SDL_CreateWindow("Pixel Zombie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!iSDL.win){
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
    }
    initRenderer(iSDL.win);
}

//Initilizes renderer
void initRenderer(SDL_Window* pWin){
    iSDL.renderer = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(iSDL.renderer, 0, 0, 0, 0);
}

//Initilizes audio frequency, format, channels & chunk
void initAudio(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        printf("Error: %s", Mix_GetError());
}

//Starts the heads-up-display game timer
//Values from 00h 00m 00s - 24h 59m 59s
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


//Calls all initilizers
void initGame(){
    //Only initilizes once
    if(!GIO.initedGame){
        initSDL();
        initWindow();
        initAudio();
        GIO.initedGame = true;
    }
    ///Initilizes at start of game and at every game over
    initTime();
    createHeart();
    ZombInit.nrOfZombies = 6;
    createAllZombies();
    PlayerInit.nrOfPlayers = 2;
    createAllPlayers();
    createBullet();
    loadMedia(&iSDL, &backTiles, &ZombInit, &PlayerInit, &b, &h, &StartInit);
    Mix_HaltMusic();
    playBgMenuMusic();
    GIO.gameOver = false;
}