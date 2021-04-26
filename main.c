//v0.1
//Project start: 2021-04-15
//Created by Eskil B, Marcus M, Carl G, Anton C and Markus H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "zombie.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[]);

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
   
    //Alien Initilizers
    SDL_Texture *mZombie = NULL;
    SDL_Rect gZombie[8];  //8 sprites per zombie
    int nrOfZombies=7;
    int zFrameCounter = 0;
    ZombieFrame zFrame[nrOfZombies];
    Zombie z[nrOfZombies];
    SDL_Rect zPosition[nrOfZombies];
    //Creates the zombies
    for(int i = 0; i < nrOfZombies; i++){
        z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
        zPosition[i].x = getZombiePositionX(z[i]);
        zPosition[i].y = getZombiePositionY(z[i]);
        zPosition[i].w = 54;
        zPosition[i].h = 54;
    }

    int mousex, mousey;         //For GetMouseState to simulate survivor walking
    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop
    loadMedia(renderer, &mTiles, gTiles, &mZombie, gZombie);

    // set to 1 when window close button is pressed
    int close_requested = 0;
    //Game event
    while (!close_requested){
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    close_requested = 1;
                break;
            }
        }

        //Game logic 
        SDL_GetMouseState(&mousex, &mousey);        //Simulate the survivor walking

        //Zombie following the Survivor X
        for(int i = 0; i < nrOfZombies; i++){
            if((zPosition[i].x - mousex) > 20){        //change to getSurvivorX()
                zPosition[i].x -= 1;
                //Frame change LEFT
                zFrame[i].diagonal = 0;
                if(zFrame[i].frame == 2 && zFrameCounter >= 25){
                    zFrame[i].frame = 3;
                    zFrameCounter = 0;
                }
                else if(zFrame[i].frame == 3){
                    if(zFrameCounter >= 25){
                        zFrame[i].frame = 2;
                        zFrameCounter = 0;
                    }
                    else{
                        zFrameCounter++;
                    }
                }
                else{
                    zFrame[i].frame = 2;
                    zFrameCounter++;
                }
            }
            else if((zPosition[i].x - mousex) < -20){              //change to getSurvivorX()
                zPosition[i].x += 1;
                //Frame change RIGHT
                zFrame[i].diagonal = 0;
                if(zFrame[i].frame == 4 && zFrameCounter >= 25){
                    zFrame[i].frame = 5;
                    zFrameCounter = 0;
                }
                else if(zFrame[i].frame == 5){
                    if(zFrameCounter >= 25){
                        zFrame[i].frame = 4;
                        zFrameCounter = 0;
                    }
                    else{
                        zFrameCounter++;
                    }
                }
                else{
                    zFrame[i].frame = 4;
                    zFrameCounter++;
                }
            }
            //Zombie following the Survivor Y
            if((zPosition[i].y - mousey) > 20){        //change to getSurvivorY()
                zPosition[i].y -= 1;
                //Frame change UP
                if(zFrame[i].diagonal++ > 0){
                    if(zFrame[i].frame == 6 && zFrameCounter >= 25){
                        zFrame[i].frame = 7;
                        zFrameCounter = 0;
                    }
                    else if(zFrame[i].frame == 7){
                        if(zFrameCounter >= 25){
                            zFrame[i].frame = 6;
                            zFrameCounter = 0;
                        }
                        else{
                            zFrameCounter++;
                        }
                    }
                    else{
                        zFrame[i].frame = 6;
                        zFrameCounter++;
                    }
                }
            }
            else if ((zPosition[i].y - mousey) < -20){         //change to getSurvivorY()
                zPosition[i].y += 1;
                //Frame change DOWN
                if(zFrame[i].diagonal++ > 0){
                    if(zFrame[i].frame == 0 && zFrameCounter >= 25){
                        zFrame[i].frame = 1;
                        zFrameCounter = 0;
                    }
                    else if(zFrame[i].frame == 1){
                        if(zFrameCounter >= 25){
                            zFrame[i].frame = 0;
                            zFrameCounter = 0;
                        }
                        else{
                            zFrameCounter++;
                        }
                    }
                    else{
                        zFrame[i].frame = 0;
                        zFrameCounter++;
                    }
                }
            }
            //Resets zFramecounter (Resolves problem that kept int going above 25 when changing direction when int was =25)
            //if(zFrameCounter>25)               IN ORDER TO USE THIS, REMOVE ">" WHEN COMPARING zFrameCounter TO 25
            //    zFrameCounter = 0;
            
            //Collision detection X
            for(int j = 0; j < nrOfZombies; j++){
                if(j==i){
                    break;
                }
                else if((zPosition[i].x - zPosition[j].x) <= 19 && (zPosition[i].x - zPosition[j].x) >=0){
                    zPosition[j].x -= 1;
                }
                else if((zPosition[i].x - zPosition[j].x) >= -19 && (zPosition[i].x - zPosition[j].x) <=0){
                    zPosition[i].x -=1;
                }
            }
            //Collision detection Y
            for(int j = 0; j < nrOfZombies; j++){
                if(j==i){
                    break;
                }
                else if((zPosition[i].y - zPosition[j].y) <= 27 && (zPosition[i].y - zPosition[j].y) >= 0){
                    zPosition[j].y -= 1;
                }
                else if((zPosition[i].y - zPosition[j].y) >= -27 && (zPosition[i].y - zPosition[j].y) <= 0){
                    zPosition[i].y -=1;
                }
            }
        }

        //Game rendering
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        renderBackground(renderer, mTiles, gTiles);
        //Renders all zombies
        for(int i = 0; i < nrOfZombies; i++){
            SDL_RenderCopyEx(renderer, mZombie, &gZombie[zFrame[i].frame], &zPosition[i], 0, NULL, SDL_FLIP_NONE);
        }
        SDL_RenderPresent(renderer);
        //Delay 1/60th second
        SDL_Delay(1000/60);
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

void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[]){
    SDL_Surface* gTilesSurface = IMG_Load("resources/Textur32x32V8.PNG");
    *mTiles = SDL_CreateTextureFromSurface(renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }

    SDL_Surface* gZombieSurface = IMG_Load("resources/ZombieSheetSizeX2.png");
    *mZombie = SDL_CreateTextureFromSurface(renderer, gZombieSurface);
    
    //Down
    gZombie[0].x = 0;
    gZombie[0].y = 0;
    gZombie[0].w = 54;
    gZombie[0].h = 54;

    gZombie[1].x = 108;
    gZombie[1].y = 0;
    gZombie[1].w = 54;
    gZombie[1].h = 54;

    //Left
    gZombie[2].x = 0;
    gZombie[2].y = 54;
    gZombie[2].w = 54;
    gZombie[2].h = 54;

    gZombie[3].x = 108;
    gZombie[3].y = 54;
    gZombie[3].w = 54;
    gZombie[3].h = 54;

    //Right
    gZombie[4].x = 0;
    gZombie[4].y = 108;
    gZombie[4].w = 54;
    gZombie[4].h = 54;

    gZombie[5].x = 108;
    gZombie[5].y = 108;
    gZombie[5].w = 54;
    gZombie[5].h = 54;

    //Up
    gZombie[6].x = 0;
    gZombie[6].y = 162;
    gZombie[6].w = 54;
    gZombie[6].h = 54;

    gZombie[7].x = 108;
    gZombie[7].y = 162;
    gZombie[7].w = 54;
    gZombie[7].h = 54;
}