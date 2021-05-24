#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "menu.h"
#include "ttf.h"
#include "server/udpClient.h"

int firstStart = 0;

void SetRenderDrawColor(){
    SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void clearRenderer(){
    SDL_RenderClear(iSDL.renderer);
}

void renderMenu(){
    theMenu(iSDL.renderer);
}


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
            SDL_RenderCopyEx(iSDL->renderer, backTiles.mTiles, &backTiles.gTiles[getTileGrid(i,j)], &position , 0, NULL,  SDL_FLIP_NONE);
        }
    }
}

void renderHealthBar(){
    for(int i = 0; i < PlayerInit.hitPoint[getPlayerID()]; i++){
        SDL_RenderCopy(iSDL.renderer, h.mHeart, &h.gHeart[0], &h.hPosition[i]);
    }
}

void renderAllPlayers(){
    for(int i = 0; i < PlayerInit.nrOfPlayers; i++){
        if(getPlayerID() == i){
            SDL_RenderCopyEx(iSDL.renderer, PlayerInit.mPlayer, &PlayerInit.gPlayer[PlayerInit.pFrame[i]], &PlayerInit.pPosition[i], 0, NULL, PlayerInit.flip[i]);
        }
        else{
            SDL_RenderCopyEx(iSDL.renderer, PlayerInit.mPlayerBlack, &PlayerInit.gPlayer[PlayerInit.pFrame[i]], &PlayerInit.pPosition[i], 0, NULL, PlayerInit.flip[i]);
        }
    }
}

void renderAllZombies(){
    for(int i = 0; i < ZombInit.nrOfZombies; i++){
        if(z[i]->alive)
            SDL_RenderCopyEx(iSDL.renderer, ZombInit.mZombie, &ZombInit.gZombie[zFrame[i].frame], &ZombInit.zPosition[i], 0, NULL, SDL_FLIP_NONE);
    }
}

void renderBullet(){
    if(b.shot) SDL_RenderCopyEx(iSDL.renderer, b.mBullet, &b.gBullet[0], &b.bPosition, b.bUpDown, NULL, SDL_FLIP_NONE);
}

void renderPreset(){
    SDL_RenderPresent(iSDL.renderer);
}
void renderGame(){
    SetRenderDrawColor();
    clearRenderer();

    if (checkIfGamestarted()!=1) {renderMenu();}
    
    if (checkIfGamestarted()==1){
        if(firstStart == 0){
            sendData(3,1,PlayerInit.nrOfPlayers,"127.0.0.1" ,PlayerInit.playerID); 
            firstStart = 1;
        }
        SDL_PumpEvents();
        renderBackground(&iSDL, backTiles);
        renderHealthBar();
        renderAllZombies();
        renderBullet();
        renderAllPlayers();
    }
    renderPreset();
    SDL_Delay(1000/60);
}