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
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[]);

int WinMain(void){
    
    // Setup
    //-------------------------------------------
    // Setup
    SDL_RendererFlip flip = SDL_FLIP_NONE;

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
    int nrOfZombies=6;
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
    //int mousex, mousey;         //For GetMouseState to simulate survivor walking
    
    //Player
    int playerID=-1;
    SDL_Texture *mPlayer = NULL;
    SDL_Rect gPlayer[9];
    int nrOfPlayers=4;
    Player p[nrOfPlayers];
    SDL_Rect pPosition[nrOfPlayers];
    for(int i = 0; i < nrOfPlayers; i++){
        p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        pPosition[i].x = getPlayerPositionX(p[i]);
        pPosition[i].y = getPlayerPositionY(p[i]);
        pPosition[i].w = 54;
        pPosition[i].h = 54;
    }

    int pFrame=0; //in gPlayer[] to show which state the player is in, which sprite is being used

    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop

    loadMedia(renderer, &mTiles, gTiles, &mZombie, gZombie, &mPlayer, gPlayer);

    // set to 1 when window close button is pressed
    int close_requested = 0;
    int kordLista[2];
    //Game event
    while (!close_requested){
        // process events
        ////

        if(playerID == -1){
        playerID = reciveID("192.168.56.1");
        }
        reciveData("192.168.56.1", kordLista);

        if(kordLista[0] != -1000){
            //printf("Satta kordinater %d %d \n", kordLista[0], kordLista[1]);
            pPosition[1].x = kordLista[0];
            pPosition[1].y = kordLista[1];
        }
        ///
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            
            switch (event.type){
                case SDL_QUIT:
                    close_requested = 1;
                    break;
                case SDL_KEYDOWN:
                sendData(pPosition->x, pPosition->y, "192.168.56.1");
                    switch( event.key.keysym.sym ){
                        case SDLK_w:            
                            pPosition->y -= 6;
                            if(pFrame == 0 || pFrame==8)//2
                                pFrame = 1;//3
                            else if(pFrame==1)
                                pFrame = 2;
                            else if(pFrame==2)
                                pFrame=3;
                            else if(pFrame==3)
                                pFrame=4;
                            else if(pFrame==4)
                                pFrame=5;
                            else if(pFrame==5)
                                pFrame=6;
                            else if(pFrame==6)
                                pFrame=7;
                            else
                                pFrame=8;
                            break;
                        case SDLK_s:
                            pPosition->y += 6;
                            if(pFrame == 0 || pFrame==8)//2
                                pFrame = 1;//3
                            else if(pFrame==1)
                                pFrame = 2;
                            else if(pFrame==2)
                                pFrame=3;
                            else if(pFrame==3)
                                pFrame=4;
                            else if(pFrame==4)
                                pFrame=5;
                            else if(pFrame==5)
                                pFrame=6;
                            else if(pFrame==6)
                                pFrame=7;
                            else
                                pFrame=8;
                            break;
                        case SDLK_a:
                            pPosition->x -= 6;//2
                            flip = SDL_FLIP_NONE; //If image should flip or not
                            if(pFrame == 0 || pFrame==8)//2
                                pFrame = 1;//3
                            else if(pFrame==1)
                                pFrame = 2;
                            else if(pFrame==2)
                                pFrame=3;
                            else if(pFrame==3)
                                pFrame=4;
                            else if(pFrame==4)
                                pFrame=5;
                            else if(pFrame==5)
                                pFrame=6;
                            else if(pFrame==6)
                                pFrame=7;
                            else
                                pFrame=8;
                            break;
                        case SDLK_d:
                            pPosition->x += 6;
                            flip = SDL_FLIP_HORIZONTAL;
                            if(pFrame == 0 || pFrame==8)//2
                                pFrame = 1;//3
                            else if(pFrame==1)
                                pFrame = 2;
                            else if(pFrame==2)
                                pFrame=3;
                            else if(pFrame==3)
                                pFrame=4;
                            else if(pFrame==4)
                                pFrame=5;
                            else if(pFrame==5)
                                pFrame=6;
                            else if(pFrame==6)
                                pFrame=7;
                            else
                                pFrame=8;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    pFrame=0;
                    break;
            }
        }

        //Game logic 
        //SDL_GetMouseState(&mousex, &mousey);        //Simulate the survivor walking

        //Zombie following the Survivor X
        for(int i = 0; i < nrOfZombies; i++){
            if((zPosition[i].x - pPosition->x) > 20){
                zPosition[i].x -= 1;
                //Frame change LEFT
                changeZFrameX(&zFrame[i].frame, 2, 3, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            else if((zPosition[i].x - pPosition->x) < -20){
                zPosition[i].x += 1;
                //Frame change RIGHT
                changeZFrameX(&zFrame[i].frame, 4, 5, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            //Zombie following the Survivor Y
            if((zPosition[i].y - pPosition->y) > 20){
                zPosition[i].y -= 1;
                //Frame change UP
                changeZFrameY(&zFrame[i].frame, 6, 7, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            else if ((zPosition[i].y - pPosition->y) < -20){
                zPosition[i].y += 1;
                //Frame change DOWN
                changeZFrameY(&zFrame[i].frame, 0, 1, &zFrame[i].counter, &zFrame[i].diagonal);
            }

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
        //Renders player
        for(int i = 0; i < nrOfPlayers; i++){
            SDL_RenderCopyEx(renderer, mPlayer, &gPlayer[pFrame], &pPosition[i], 0, NULL, flip);
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

void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[]){
    SDL_Surface* gTilesSurface = IMG_Load("resources/Textur32x32V8.PNG");
    *mTiles = SDL_CreateTextureFromSurface(renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }

    //Zombie
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
    
    //Player
    SDL_Surface* gPlayerSurface = IMG_Load("resources/girlPlayer.png");
    *mPlayer = SDL_CreateTextureFromSurface(renderer, gPlayerSurface);

    //Ståendes med kroppen mot skärmen med pistol
    gPlayer[0].x = 8;
    gPlayer[0].y = 400;
    gPlayer[0].w = 64;
    gPlayer[0].h = 64;

    gPlayer[1].x = 8; //Det är 96 mellan varje bild sidleds
    gPlayer[1].y = 210;//80 mellan varje rad
    gPlayer[1].w = 64;
    gPlayer[1].h = 64;
 
    gPlayer[2].x = 104;
    gPlayer[2].y = 210;
    gPlayer[2].w = 64;
    gPlayer[2].h = 64;

    gPlayer[3].x = 200;
    gPlayer[3].y = 210;
    gPlayer[3].w = 64;
    gPlayer[3].h = 64;

    gPlayer[4].x = 296;
    gPlayer[4].y = 210;
    gPlayer[4].w = 64;
    gPlayer[4].h = 64;

    gPlayer[5].x = 392;
    gPlayer[5].y = 210;
    gPlayer[5].w = 64;
    gPlayer[5].h = 64;

    gPlayer[6].x = 488;
    gPlayer[6].y = 210;
    gPlayer[6].w = 64;
    gPlayer[6].h = 64;

    gPlayer[7].x = 584;
    gPlayer[7].y = 210;
    gPlayer[7].w = 64;
    gPlayer[7].h = 64;

    gPlayer[8].x = 680;
    gPlayer[8].y = 210;
    gPlayer[8].w = 64;
    gPlayer[8].h = 64; 
}