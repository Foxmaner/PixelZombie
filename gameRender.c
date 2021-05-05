#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"

void renderBackground(InitSDL* iSDL, SDL_Texture *mTiles, SDL_Rect gTiles[]){
    SDL_Rect position;
    position.y = 0;
    position.x = 0;
    position.h = getTileHeight();
    position.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++){
        for (int j = 0; j<getTileRows(); j++){
            position.y = i*getTileHeight();
            position.x = j*getTileWidth();
            SDL_RenderCopyEx(iSDL->renderer, mTiles, &gTiles[getTileGrid(i,j)],&position , 0, NULL, SDL_FLIP_NONE);
        }
    }
}