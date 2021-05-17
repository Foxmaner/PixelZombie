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

void SetRenderDrawColor(){
    SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void clearRenderer(){
    SDL_RenderClear(iSDL.renderer);
}

void renderMenu(){
        char IPaddress[12]="...\0";
        
        GetString(IPaddress, 12 );
        //printf( "%s", IPaddress );
        char *font_path;    
        font_path = "resources/fonts/OpenSans-Bold.ttf";
        TTF_Init();

        TTF_Font *font = TTF_OpenFont(font_path, 36);
        if (font == NULL) {
            printf("error: font not found\n");
            exit(EXIT_FAILURE);
        }
        SDL_Rect rect1, rect2, rect3, rect4, rect5, rect6; 
        SDL_Texture *texture1, *texture2, *texture3, *texture4, *texture5, *texture6;
        int buttonPos[4]={40,155,40,85};
        int buttonStartGamePos[4]={40,155,80,125};
        int backbutton[4]={40,190,600,750};
        //Beginning menu
        if (lobby!=1 && credits!=1){
            get_text_and_rect(iSDL.renderer, 40, 40, "START", font, &texture1, &rect1);
            SDL_RenderCopy(iSDL.renderer, texture1, NULL, &rect1);
            get_text_and_rect(iSDL.renderer, 40, rect1.y + rect1.h, "Credits", font, &texture2, &rect2); 
            SDL_RenderCopy(iSDL.renderer, texture2, NULL, &rect2);
            lobby=checkmousestate(&buttonPos[0],&buttonPos[1],&buttonPos[2],&buttonPos[3]);
            credits=checkmousestate(&buttonStartGamePos[0],&buttonStartGamePos[1],&buttonStartGamePos[2],&buttonStartGamePos[3]);
            back=2;
        }

        //Entering IPadress
        if (lobby==1){
            get_text_and_rect(iSDL.renderer, 40, 40, "Enter IPadress:", font, &texture3, &rect3); 
            SDL_RenderCopy(iSDL.renderer, texture3, NULL, &rect3);
            get_text_and_rect(iSDL.renderer, 340, 40,  IPaddress, font, &texture2, &rect2); 
            SDL_RenderCopy(iSDL.renderer, texture2, NULL, &rect2);

            get_text_and_rect(iSDL.renderer, 40, 600, "Back", font, &texture1, &rect1);
            SDL_RenderCopy(iSDL.renderer, texture1, NULL, &rect1);

            back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
            if (back==1){
                lobby=2;
                credits=2;
            }

            get_text_and_rect(iSDL.renderer, 40, 80, "Start game", font, &texture4, &rect4); 
            SDL_RenderCopy(iSDL.renderer, texture4, NULL, &rect4);
            startrender=checkmousestate(&buttonStartGamePos[0],&buttonStartGamePos[1],&buttonStartGamePos[2],&buttonStartGamePos[3]);
        }

        if (credits==1)
        {
            get_text_and_rect(iSDL.renderer, 40, 600, "Back", font, &texture1, &rect1);
            SDL_RenderCopy(iSDL.renderer, texture1, NULL, &rect1);
            //Creators
            get_text_and_rect(iSDL.renderer, 40, 80, "Made by Anton C, Carl G, Eskil B, Markus H, Marcus M", font, &texture2, &rect2); 
            SDL_RenderCopy(iSDL.renderer, texture2, NULL, &rect2);
            //Heart pixel art
            get_text_and_rect(iSDL.renderer, 40, rect2.y + rect2.h, "Heart pixel art: DanSevenStar.xyz", font, &texture3, &rect3); 
            SDL_RenderCopy(iSDL.renderer, texture3, NULL, &rect3);
            //Spelare
            get_text_and_rect(iSDL.renderer, 40, rect3.y + rect3.h, "Player: thekingphoenix & Bonsaiheldin", font, &texture4, &rect4); 
            SDL_RenderCopy(iSDL.renderer, texture4, NULL, &rect4);
            //Zombie
            get_text_and_rect(iSDL.renderer, 40, rect4.y + rect4.h, "Zombie: Kazzador & Enterbrain", font, &texture5, &rect5); 
            SDL_RenderCopy(iSDL.renderer, texture5, NULL, &rect5);
            //Musik
            get_text_and_rect(iSDL.renderer, 40, rect5.y + rect5.h, "Music: March of Midnight by Scott Buckley ", font, &texture6, &rect6); 
            SDL_RenderCopy(iSDL.renderer, texture6, NULL, &rect6);

            back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
            if (back==1){
                lobby=2;
                credits=2;
            }
        }
  

    
    //SDL_RenderCopyEx(iSDL.renderer, StartInit.mstartbutton, &StartInit.gstartbutton[0],&StartInit.gstartbutton[0], 0, NULL, SDL_FLIP_NONE);
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
        renderAllZombies();
        renderBullet();
        renderAllPlayers();
    }
    renderPreset();
    SDL_Delay(1000/60);
}