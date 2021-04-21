//v0.1
//Project start: 2021-04-15
//Created by Eskil B, Marcus M, Carl G, Anton C and Markus H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "map.h"


#include "player.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)


void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mPlayer, SDL_Rect gPlayer[]);

int WinMain(void){
    // Setup
    //-------------------------------------------
    // Setup

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Pixel Zombie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win){
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    //Initilize renderer
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Initilize background
    SDL_Texture *mTiles = NULL;
    SDL_Rect gTiles[32];
   
    //Player
    SDL_Texture *mPlayer = NULL;
    SDL_Rect gPlayer[8];
    int nrOfPlayers=2;
    Player p[nrOfPlayers];
    SDL_Rect pPosition[nrOfPlayers];
    for(int i = 0; i < nrOfPlayers; i++){
        p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        pPosition[i].x = getPlayerPositionX(p[i]);
        pPosition[i].y = getPlayerPositionY(p[i]);
        pPosition[i].w = 54;
        pPosition[i].h = 54;
    }

    int pFrame = 1;



    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop
    loadMedia(renderer, &mTiles, gTiles, &mPlayer, gPlayer);
    
    // set to 1 when window close button is pressed
    int close_requested = 0;
    //Game event
    while (!close_requested){
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                switch( event.key.keysym.sym )
                {
                    case SDLK_w:
                        // should be in game logic
                        pPosition->y -= 2;
                        //flip = SDL_FLIP_NONE;
                        if(pFrame == 4)
                            pFrame = 5;
                        else
                            pFrame = 4;
                        break;
                    case SDLK_s:
                        pPosition->y += 2;
                        //flip = SDL_FLIP_NONE;
                        if(pFrame == 0)
                            pFrame = 1;
                        else
                            pFrame = 0;
                        break;
                    case SDLK_a:
                        pPosition->x -= 2;
                        //flip = SDL_FLIP_HORIZONTAL;
                        if(pFrame == 2)
                            pFrame = 3;
                        else
                            pFrame = 2;
                        break;
                    case SDLK_d:
                        pPosition->x += 2;
                        //flip = SDL_FLIP_NONE;
                        if(pFrame == 2)
                            pFrame = 3;
                        else
                            pFrame = 2;
                        break;
                    default:
                        break;
        
                break;


                case SDL_QUIT:
                    close_requested = 1;
                break;
            }
        }
    }

        //Game logic


        //Game rendering
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        renderBackground(renderer, mTiles, gTiles);
        SDL_RenderCopyEx(renderer, mPlayer, &gPlayer[0], &pPosition[0], 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, mPlayer, &gPlayer[pFrame], &pPosition[1], 0, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }


   // SDL_DestroyWindow(win);
   // SDL_Quit();
}

void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTiles, SDL_Rect gTiles[]){
    SDL_Rect position;
    position.y = 0;
    position.x = 0;
    position.h = getTileHeight();
    position.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++){
        for (int j = 0; j<getTileRows(); j++){
            position.y = i*getTileHeight();
            position.x = j*getTileWidth();
            SDL_RenderCopyEx(renderer, mTiles, &gTiles[getTileGrid(i,j)],&position , 0, NULL, SDL_FLIP_NONE);
        }
    }
}

void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mPlayer, SDL_Rect gPlayer[]){

    SDL_Surface* gTilesSurface = IMG_Load("resources/Textur32x32V4.PNG");
    *mTiles = SDL_CreateTextureFromSurface(renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }

    SDL_Surface* gPlayerSurface = IMG_Load("resources/girlPlayer.png");
    *mPlayer = SDL_CreateTextureFromSurface(renderer, gPlayerSurface);


    //Ståendes med kroppen mot skärmen med pistol
    gPlayer[0].x = 7;
    gPlayer[0].y = 399;
    gPlayer[0].w = 63;
    gPlayer[0].h = 63;

    //Ej i bruk
    gPlayer[1].x = 0;
    gPlayer[1].y = 54;
    gPlayer[1].w = 48;
    gPlayer[1].h = 48;

    //Ej i bruk
    gPlayer[2].x = 108;
    gPlayer[2].y = 54;
    gPlayer[2].w = 48;
    gPlayer[2].h = 48;
}