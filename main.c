//v0.1
//Create map

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "map.h"

#define WINDOW_WIDTH (1200)
#define WINDOW_HEIGHT (800)


void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[]);

int WinMain(void){
    
    // Setup
    //-------------------------------------------
    // Setup

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Pixel Zombie",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
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
    SDL_Rect gTiles[16];
   
  
   



    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop 

    // set to 1 when window close button is pressed
    int close_requested = 0;

    loadMedia(renderer, &mTiles, gTiles);

    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            }

        }
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    renderBackground(renderer, mTiles, gTiles);
    SDL_RenderPresent(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTiles, SDL_Rect gTiles[]){
    SDL_Rect possition;
    possition.y = 0;
    possition.x = 0;
    possition.h = getTileHeight();
    possition.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++) {
        for (int j = 0; j<getTileRows(); j++) {
            possition.y = i*getTileHeight();
            possition.x = j*getTileWidth();
            SDL_RenderCopyEx(renderer, mTiles, &gTiles[getTileGrid(i,j)],&possition , 0, NULL, SDL_FLIP_NONE);
        }
    }
}

void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[]){

    SDL_Surface* gTilesSurface = IMG_Load("resources/TILES.PNG");
    *mTiles = SDL_CreateTextureFromSurface(renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    } 
    
}





