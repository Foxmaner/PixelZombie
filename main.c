//v0.1
//Project start: 2021-04-15
//Created by Eskil B, Marcus M, Carl G, Anton C and Markus H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "gameRender.h"

int WinMain(void){
    srand(time(NULL));
    int close = 0;
    GIO.initedGame = false;
    GIO.gameOver = true;
    do{
        if(GIO.gameOver) initGame();
        close = mainGameEvent();
        renderGame();
    }while(close != 1);

    SDL_Quit();
}