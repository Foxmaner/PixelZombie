//v0.1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "gridSystem.h"

#define WINDOW_WIDTH (1600)
#define WINDOW_HEIGHT (800)

bool init(SDL_Renderer **gRenderer);
void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *gRenderer,SDL_Texture **mTiles, SDL_Rect gTiles[]);


int WinMain(void){
    
    // Setup
    //-------------------------------------------
    // Setup
    SDL_Renderer *gRenderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
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

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend){
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Rect gTiles[16];
    SDL_Texture *mTiles = NULL;
    // set to 1 when window close button is pressed
    int close_requested = 0;

    loadMedia(gRenderer, &mTiles, gTiles);

    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop 

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
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            renderBackground(gRenderer, mTiles, gTiles);
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


//
//Function which renders the whole game-field
//
void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTiles, SDL_Rect gTiles[]){
    
    SDL_Rect possition;
    possition.y = 0;
    possition.x = 0;
    possition.h = getTileHeight();
    possition.w = getTileWidth();
    
    for (int i = 0; i<getTileColumns(); i++) {
        for (int j = 0; j<getTileRows(); j++) {
            possition.y = i*getTileHeight();
            possition.x = j*getTileWidth();
            SDL_RenderCopyEx(gRenderer, mTiles, &gTiles[getTileGrid(i,j)],&possition , 0, NULL, SDL_FLIP_NONE);
        }
    }
}

void loadMedia(SDL_Renderer *gRenderer, SDL_Texture **mTiles, SDL_Rect gTiles[]){
    SDL_Surface* gTilesSurface = IMG_Load("resources/groundTextures/grass1.PNG");
    *mTiles = SDL_CreateTextureFromSurface(gRenderer, gTilesSurface);
    for (int i = 0; i < 16; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }
}

