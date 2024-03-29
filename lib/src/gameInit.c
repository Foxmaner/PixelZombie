#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../include/gameEvent.h"
#include "../include/gameInit.h"
#include "../include/gameMedia.h"
#include "../include/zombie.h"
#include "../include/player.h"
#include "../include/menu.h"
#include "../../server/udpClient.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

int tempID = -1; 
int tempCreate = 1;

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
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
}

//Initilizes window and calls to initilize renderer
void initWindow(){
    iSDL.win = SDL_CreateWindow("Pixel Zombie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(!iSDL.win){
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
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("Error: %s", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
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

int getSeconds(){
    return timer.second;
}

//Calls all initilizers
void initGame(){
    PlayerInit.playerID;
    //Only initilizes once
    if(!GIO.initedGame){
        initSDL();
        initWindow();
        initAudio();
        ZombInit.nrOfZombies = 6;
        GIO.initedGame = true;
    }
    
    ///Initilizes at start of game and at every game over
    initTime();
    createHeart();
    createAllZombies();
    createAllPlayers();
    tempCreate=0;

    //Initilizes a connection to server
    sendData(10,0,0,"127.0.0.1" ,PlayerInit.playerID);
    PlayerInit.nrOfPlayers = 4;
    printf("Player ID  %d \n", PlayerInit.playerID);

    createBullet();
    loadMedia(&iSDL, &backTiles, &ZombInit, &PlayerInit, &b, &h, &MenuInit);
    Mix_HaltMusic();
    playBgMenuMusic();
    GIO.gameOver = false;

    //Sets player ID and makes sure that it stays as that id 
    if(tempID == -1){
        PlayerInit.playerID = reciveID("127.0.0.1");
        tempID = PlayerInit.playerID;
    }
    else{
        PlayerInit.playerID = tempID;
    }
}