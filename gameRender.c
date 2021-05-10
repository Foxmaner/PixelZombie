#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "gameInit.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "menu.h"
#include "server/udpClient.h"

void openTextBox(){

    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 12); //this opens a font style and sets a size

    SDL_Color Black = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(iSDL.renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 20; // controls the width of the rect
    Message_rect.h = 20; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(iSDL.renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Tar bort
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}

void SetRenderDrawColor(){
    SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void clearRenderer(){
    SDL_RenderClear(iSDL.renderer);
}

void renderMenu(){
    SDL_RenderCopyEx(iSDL.renderer, StartInit.mstartbutton, &StartInit.gstartbutton[0],&StartInit.gstartbutton[0], 0,NULL, SDL_FLIP_NONE);
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
    for(int i = 0; i < PlayerInit.nrOfPlayers; i++){
        SDL_RenderCopyEx(iSDL.renderer, PlayerInit.mPlayer, &PlayerInit.gPlayer[PlayerInit.pFrame[i]], &PlayerInit.pPosition[i], 0, NULL, PlayerInit.flip[i]);
    }
}

void renderAllZombies(){
    for(int i = 0; i < ZombInit.nrOfZombies; i++){
        SDL_RenderCopyEx(iSDL.renderer, ZombInit.mZombie, &ZombInit.gZombie[zFrame[i].frame],&ZombInit.zPosition[i], 0, NULL, SDL_FLIP_NONE);
    }
}



void renderBullet(){
    if(b.shot)
        SDL_RenderCopyEx(iSDL.renderer, b.mBullet, &b.gBullet[0], &b.bPosition, b.bUpDown, NULL, SDL_FLIP_NONE);
}

void renderPreset(){
    SDL_RenderPresent(iSDL.renderer);
}


void renderGame(){
    SetRenderDrawColor();
    clearRenderer();
    //renderMenu();
    openTextBox();
    //renderBackground(&iSDL, backTiles);
    //renderAllZombies();
    //renderAllPlayers();
    //renderBullet();
    renderPreset();

    SDL_Delay(1000/60);
}