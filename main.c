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

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

void renderBackground(SDL_Renderer *renderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[], SDL_Texture **mBullet, SDL_Rect gBullet[]);

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
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //Initilize background
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
        zPosition[i].w = 43;
        zPosition[i].h = 54;
    }

    //Player initilizer
    SDL_Texture *mPlayer = NULL;
    SDL_Rect gPlayer[10];
    int nrOfPlayers=1;
    Player p[nrOfPlayers];
    SDL_Rect pPosition[nrOfPlayers];
    for(int i = 0; i < nrOfPlayers; i++){
        p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        pPosition[i].x = getPlayerPositionX(p[i]);
        pPosition[i].y = getPlayerPositionY(p[i]);
        pPosition[i].w = 64;
        pPosition[i].h = 64;
    }
    unsigned int lastDmgTakenTime = 0, currentDmgTakenTime = 0; //Used to limit taken damage to 1hp/s
    int pFrame=0; //in gPlayer[] to show which state the player is in, which sprite is being used

    //Bullet initilizer
    SDL_Texture *mBullet;
    SDL_Rect gBullet[1];
    SDL_Rect bPosition;
    bPosition.x = 100;
    bPosition.y = 100;
    bPosition.w = 15;
    bPosition.h = 5;
    bool shot = false;
    int lastShotTime = 0, currentShotTime = 0;
    int bVelX = 1, bVelY = 1, bUpDown = 0;

    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop
    loadMedia(renderer, &mTiles, gTiles, &mZombie, gZombie, &mPlayer, gPlayer, &mBullet, gBullet);

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
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_w:
                            pPosition->y -= 6;
                            bVelY = -1;
                            bVelX = 0;
                            bUpDown = 90;
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
                            bVelY = 1;
                            bVelX = 0;
                            bUpDown = 90;
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
                            bVelX = -1;
                            bVelY = 0;
                            bUpDown = 0;
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
                            bVelX = 1;
                            bVelY = 0;
                            bUpDown = 0;
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
                        case SDLK_LCTRL:
                            if(msTimer(&currentShotTime, &lastShotTime, 500))  //13 rps
                                shot = true;
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

            //Collision detection X with other zombies
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
            //Collision detection Y with other zombies
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
            if(checkZCollisionWithP(zPosition[i],pPosition[0])){
                if(msTimer(&currentDmgTakenTime, &lastDmgTakenTime, 1000)){
                    respawnPlayer(p[0], &pPosition[0]);
                }
            }

            //Map collision detection ZOMBIE
            //TOP
            if(zPosition[i].y < 15){
                zPosition[i].y = 15;
            }
            //BOTTOM
            if(zPosition[i].y > 1224) zPosition[i].y = 1224;
            if(zPosition[i].y > 905 && (zPosition[i].x < 330 || zPosition[i].x > 455))
                zPosition[i].y = 905;
            else if(zPosition[i].y > 905 && zPosition[i].x < 335)
                zPosition[i].x = 335;
            else if(zPosition[i].y > 905 && zPosition[i].x > 450)
                zPosition[i].x = 450;
            //LEFT
            if(zPosition[i].x < -200) zPosition[i].x = -200;
            if(zPosition[i].x < 64 && (zPosition[i].y < 355 || zPosition[i].y > 430))
                zPosition[i].x = 64;
            else if(zPosition[i].x < 64 && zPosition[i].y < 360)
                zPosition[i].y = 360;
            else if(zPosition[i].x < 64 && zPosition[i].y > 425)
                zPosition[i].y = 425;
            //RIGHT
            if(zPosition[i].x > 1224) zPosition[i].x = 1224;
            if(zPosition[i].x > 930 && (zPosition[i].y < 355 || zPosition[i].y > 430))
                zPosition[i].x = 930;
            else if(zPosition[i].x > 930 && zPosition[i].y < 360)
                zPosition[i].y = 360;
            else if(zPosition[i].x > 930 && zPosition[i].y > 425)
                zPosition[i].y = 425;
        }

        //Map collision detection PLAYER
        //TOP
        if(pPosition[0].y < 15) pPosition[0].y = 15;
        //BOTTOM
        if(pPosition[0].y > 905) pPosition[0].y = 905;
        //LEFT
        if(pPosition[0].x < 30) pPosition[0].x = 30;
        //RIGHT
        if(pPosition[0].x > 930) pPosition[0].x = 930;

        //Bullet positioning
        if(!shot){
            bPosition.x = pPosition[0].x + 20;
            bPosition.y = pPosition[0].y + 17;
        }
        else{
            if(!bVelY) bPosition.x += bVelX * 75;
            else bPosition.y += bVelY * 75;
            if(bPosition.x < 0 || bPosition.x > 1024 || bPosition.y < 0 || bPosition.y > 1024){
                pFrame = 9;
                shot = false;
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
        SDL_RenderCopyEx(renderer, mPlayer, &gPlayer[pFrame], &pPosition[0], 0, NULL, flip);
        //Render bullet
        if(shot)
            SDL_RenderCopyEx(renderer, mBullet, &gBullet[0], &bPosition, bUpDown, NULL, SDL_FLIP_NONE);
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

void loadMedia(SDL_Renderer *renderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[], SDL_Texture **mBullet, SDL_Rect gBullet[]){
    //Map
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
    for(int i = 0; i < 8; i++){
        gZombie[i].x = 108 * (i % 2) + 6;
        if(i % 2 == 0) gZombie[i].y = (54 * i) / 2;
        else gZombie[i].y = gZombie[i-1].y;
        gZombie[i].w = 43;
        gZombie[i].h = 54;
    }

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

    gPlayer[9].x = 97;
    gPlayer[9].y = 399;
    gPlayer[9].w = 69;
    gPlayer[9].h = 64;

    //Bullet
    SDL_Surface* gBulletSurface = IMG_Load("resources/bullet.png");
    *mBullet = SDL_CreateTextureFromSurface(renderer, gBulletSurface);
    gBullet[0].x = 0;
    gBullet[0].y = 0;
    gBullet[0].w = 15;
    gBullet[0].h = 5;
}