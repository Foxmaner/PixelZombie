#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"

void renderBackground(InitSDL* iSDL, Background_Tiles backTiles){
    SDL_Rect position;
    position.y = 0;
    position.x = 0;
    position.h = getTileHeight();
    position.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++){
        for (int j = 0; j<getTileRows(); j++){
            position.y = i*getTileHeight();
            position.x = j*getTileWidth();
            SDL_RenderCopyEx(iSDL->renderer, backTiles.mTiles, &backTiles.gTiles[getTileGrid(i,j)],&position , 0, NULL, SDL_FLIP_NONE);
        }
    }
}
/*
void SetRenderDrawColor(){
    SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void clearRenderer(){
    SDL_RenderClear(iSDL.renderer);
}

void renderAllZombies(){
    for(int i = 0; i < nrOfZombies; i++){
        SDL_RenderCopyEx(iSDL.renderer, mZombie, &gZombie[zFrame[i].frame], &zPosition[i], 0, NULL, SDL_FLIP_NONE);
    }
}

void renderAllPlayers(){
    for(int i = 0; i < nrOfPlayers; i++){
        SDL_RenderCopyEx(iSDL.renderer, mPlayer, &gPlayer[pFrame], &pPosition[i], 0, NULL, flip);
    }
}

void renderBullet(){
    if(shot)
        SDL_RenderCopyEx(iSDL.renderer, mBullet, &gBullet[0], &bPosition, bUpDown, NULL, SDL_FLIP_NONE);
}

void renderPreset(){
    SDL_RenderPresent(iSDL.renderer);
}


void renderEverything(){
    SetRenderDrawColor();
    clearRenderer();
    renderBackground(&iSDL, mTiles, gTiles);
    renderAllZombies();
    renderAllPlayers();
    renderBullet();
    renderPreset();

    SDL_Delay(1000/60);
}
*/