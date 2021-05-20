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

int startrender=2;
int lobby=2;
int credits=2;
int back=2;

void setStartRender(int a){
    startrender = a;
}

void SetRenderDrawColor(){
    SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void clearRenderer(){
    SDL_RenderClear(iSDL.renderer);
}

void renderMenu(){
        char IPaddress[12]="\0";
        SDL_RenderCopyEx(iSDL.renderer, StartInit.mstartbutton, &StartInit.gstartbutton[0],&StartInit.gstartbutton[0], 0, NULL, SDL_FLIP_NONE);
        GetString(IPaddress, 12 );
        //printf( "%s", IPaddress );
        int buttonPos[4]={40,155,40,85};
        int buttonStartGamePos[4]={40,155,80,125};
        int backbutton[4]={40,190,600,750};
        int StartbuttonPos[4]={40,155,800,845};
        //Beginning menu
        if (lobby!=1 && credits!=1){
            createTextbox(iSDL.renderer, 40, 40, "START", 36);
            createTextbox(iSDL.renderer, 40, 80, "Credits", 36); 
            lobby=checkmousestate(&buttonPos[0],&buttonPos[1],&buttonPos[2],&buttonPos[3]);
            credits=checkmousestate(&buttonStartGamePos[0],&buttonStartGamePos[1],&buttonStartGamePos[2],&buttonStartGamePos[3]);
            back=2;
        }

        //Entering IPadress
        if (lobby==1){
            createTextbox(iSDL.renderer, 40, 40, "Enter IPadress:", 36); 
            createTextbox(iSDL.renderer, 300, 40,  IPaddress, 36); 

            createTextbox(iSDL.renderer, 40, 600, "Back", 36);

            back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
            if (back==1){
                lobby=2;
                credits=2;
            }

            createTextbox(iSDL.renderer, 800, 40, "Start game", 36); 
            startrender=checkmousestate(&buttonStartGamePos[0],&buttonStartGamePos[1],&buttonStartGamePos[2],&buttonStartGamePos[3]);
        }

        if (credits==1)
        {
            createTextbox(iSDL.renderer, 40, 600, "Back", 36);
            //Creators
            createTextbox(iSDL.renderer, 40, 80, "Made by Anton C, Carl G, Eskil B, Markus H, Marcus M", 36); 
            //Heart pixel art
            createTextbox(iSDL.renderer, 40, 120, "Heart pixel art: DanSevenStar.xyz", 30); 
            //Spelare
            createTextbox(iSDL.renderer, 40, 160, "Player: thekingphoenix & Bonsaiheldin", 30); 
            //Zombie
            createTextbox(iSDL.renderer, 40, 200, "Zombie: Kazzador & Enterbrain", 30); 
            //Musik
            createTextbox(iSDL.renderer, 40, 240, "Music: March of Midnight by Scott Buckley ", 30); 

            back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
            if (back==1){
                lobby=2;
                credits=2;
            }
        }
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
    for(int i = 0; i < PlayerInit.nrOfPlayers; i++)
        SDL_RenderCopyEx(iSDL.renderer, PlayerInit.mPlayer, &PlayerInit.gPlayer[PlayerInit.pFrame[i]], &PlayerInit.pPosition[i], 0, NULL, PlayerInit.flip[i]);
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
    if (startrender!=1) {renderMenu();}
    if (startrender==1){
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