//v0.1
//Project start: 2021-04-15
//Created by Eskil B, Marcus M, Carl G, Anton C and Markus H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "gameRender.h"
#include "gameMedia.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"


//#define WINDOW_WIDTH (1024)
//#define WINDOW_HEIGHT (1024)

//void renderBackground(InitSDL* iSDL, SDL_Texture *mTile, SDL_Rect gTiles[]);
//void loadMedia(InitSDL* iSDL, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[], SDL_Texture **mBullet, SDL_Rect gBullet[]);

int WinMain(void){
    
    // Setup
    //-------------------------------------------
    // Setup
  /*  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
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
    */

    initGame();

    
    /*
    //Initilize background
    SDL_Texture *mTiles = NULL;
    SDL_Rect gTiles[32];
    
    //Zombie Initilizers
    SDL_Texture *mZombie = NULL;
    SDL_Rect gZombie[8];  //8 sprites per zombie
    int nrOfZombies=6;
    ZombieFrame zFrame[nrOfZombies];
    Zombie z[nrOfZombies];
    SDL_Rect zPosition[nrOfZombies];
    
    //Creates the zombies
    for(int i = 0; i < nrOfZombies; i++){
        z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
        ZombInit.zPosition[i].x = getZombiePositionX(z[i]);
        ZombInit.zPosition[i].y = getZombiePositionY(z[i]);
        ZombInit.zPosition[i].w = 43;
        ZombInit.zPosition[i].h = 54;
    }
    
    //Player initilizer
    int playerID=-1;
    int nrOfPlayers=4;
    SDL_Texture *mPlayer = NULL;
    SDL_Rect gPlayer[16];
    Player p[nrOfPlayers];
    SDL_Rect PlayerInit.pPosition[nrOfPlayers];
    for(int i = 0; i < nrOfPlayers; i++){
        p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        PlayerInit.pPosition[i].x = getPlayerPositionX(p[i]);
        PlayerInit.pPosition[i].y = getPlayerPositionY(p[i]);
        PlayerInit.pPosition[i].w = 64;
        PlayerInit.pPosition[i].h = 64;
    }
    
    
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
*/
    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop
    unsigned int lastDmgTakenTime = 0, currentDmgTakenTime = 0; //Used to limit taken damage to 1hp/s
    int pFrame=0; //in gPlayer[] to show which state the player is in, which sprite is being used
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    const Uint8 *state = SDL_GetKeyboardState(NULL); //Initierar hela skrivbordet. Det möjliggör att man konstant kan skanna in om en tangent är på eller av
    // set to 1 when window close button is pressed
    int close_requested = 0;
    int up_w,down_s,left_a,right_d,lctrl;
    int kordLista[2];
    int playerID=-1;
    loadMedia(&iSDL, &backTiles, &ZombInit, &PlayerInit, &b);
    
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
            PlayerInit.pPosition[1].x = kordLista[0];
            PlayerInit.pPosition[1].y = kordLista[1];
        }
        ///
        SDL_Event event;
        while (SDL_PollEvent(&event)){ 
                if (event.type== SDL_QUIT){
                close_requested = 1;
                }                    
                if (event.type== SDL_KEYDOWN){
                    sendData(PlayerInit.pPosition->x, PlayerInit.pPosition->y, "192.168.56.1", playerID);
                    if (up_w==1){
                        PlayerInit.pPosition->y -= 6;
                        b.bVelY = -1;
                        b.bVelX = 0;
                        b.bUpDown = 90;
                        if (pFrame!=9 && pFrame>=10) pFrame=9;
                        else pFrame++;    
                    }
                    if (down_s==1) {
                        PlayerInit.pPosition->y += 6;
                        b.bVelY = 1;
                        b.bVelX = 0;
                        b.bUpDown = 90;
                        if (pFrame!=12 && pFrame>=13) pFrame=12;
                        else pFrame++;    
                    }
                    if(left_a==1){ 
                        PlayerInit.pPosition->x -= 6;
                        b.bVelX = -1;
                        b.bVelY = 0;
                        b.bUpDown = 0;
                        flip = SDL_FLIP_NONE;
                        if (pFrame>=8) pFrame=1;
                        else pFrame++;    
                    }
                    if (right_d==1){
                        PlayerInit.pPosition->x += 6;
                        b.bVelX = 1;
                        b.bVelY = 0;
                        b.bUpDown = 0;
                        flip = SDL_FLIP_HORIZONTAL;                        
                        if (pFrame>=8) pFrame=1;
                        else pFrame++;
                    }
                    if (event.key.keysym.sym==SDLK_w){
                        up_w=1;
                    }
                    if (event.key.keysym.sym==SDLK_s){
                        down_s=1;
                    } 
                    if(event.key.keysym.sym==SDLK_a){
                        left_a=1;
                    }
                    if(event.key.keysym.sym==SDLK_d){
                        right_d=1;
                    }
                    if(event.key.keysym.sym==SDLK_LCTRL){
                        if(msTimer(&b.currentShotTime, &b.lastShotTime, 500))  //13 rps
                            b.shot = true;
                    }
                }
                if(event.type== SDL_KEYUP){
                    if(event.key.keysym.sym==SDLK_w){
                        up_w=0; 
                        pFrame=11;
                    } 
                    if(event.key.keysym.sym==SDLK_s){
                        down_s=0; 
                        pFrame=14;
                    }
                    if(event.key.keysym.sym==SDLK_a){
                        left_a=0; 
                        pFrame=0;
                    }
                    if(event.key.keysym.sym==SDLK_d){
                        right_d=0; 
                        pFrame=0;
                    }
                    if(event.key.keysym.sym==SDLK_LCTRL){
                        lctrl=0;
                    }
                }
        }
        //Game logic 

        //Zombie following the Survivor X
        for(int i = 0; i < ZombInit.nrOfZombies; i++){
            if((ZombInit.zPosition[i].x - PlayerInit.pPosition->x) > 20){
                ZombInit.zPosition[i].x -= 1;
                //Frame change LEFT
                changeZFrameX(&zFrame[i].frame, 2, 3, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            else if((ZombInit.zPosition[i].x - PlayerInit.pPosition->x) < -20){
                ZombInit.zPosition[i].x += 1;
                //Frame change RIGHT
                changeZFrameX(&zFrame[i].frame, 4, 5, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            //Zombie following the Survivor Y
            if((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) > 20){
                ZombInit.zPosition[i].y -= 1;
                //Frame change UP
                changeZFrameY(&zFrame[i].frame, 6, 7, &zFrame[i].counter, &zFrame[i].diagonal);
            }
            else if ((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) < -20){
                ZombInit.zPosition[i].y += 1;
                //Frame change DOWN
                changeZFrameY(&zFrame[i].frame, 0, 1, &zFrame[i].counter, &zFrame[i].diagonal);
            }

            //Collision detection X with other zombies
            for(int j = 0; j < ZombInit.nrOfZombies; j++){
                if(j==i){
                    break;
                }
                else if((ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) <= 19 && (ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) >=0){
                    ZombInit.zPosition[j].x -= 1;
                }
                else if((ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) >= -19 && (ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) <=0){
                    ZombInit.zPosition[i].x -=1;
                }
            }
            //Collision detection Y with other zombies
            for(int j = 0; j < ZombInit.nrOfZombies; j++){
                if(j==i){
                    break;
                }
                else if((ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) <= 27 && (ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) >= 0){
                    ZombInit.zPosition[j].y -= 1;
                }
                else if((ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) >= -27 && (ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) <= 0){
                    ZombInit.zPosition[i].y -=1;
                }
            }
            if(checkZCollisionWithP(ZombInit.zPosition[i],PlayerInit.pPosition[0])){
                if(msTimer(&currentDmgTakenTime, &lastDmgTakenTime, 1000)){
                    respawnPlayer(PlayerInit.p[0], &PlayerInit.pPosition[0]);
                }
            }

            //Map collision detection ZOMBIE
            //TOP
            if(ZombInit.zPosition[i].y < 15){
                ZombInit.zPosition[i].y = 15;
            }
            //BOTTOM
            if(ZombInit.zPosition[i].y > 1224) ZombInit.zPosition[i].y = 1224;
            if(ZombInit.zPosition[i].y > 905 && (ZombInit.zPosition[i].x < 330 || ZombInit.zPosition[i].x > 455))
                ZombInit.zPosition[i].y = 905;
            else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x < 335)
                ZombInit.zPosition[i].x = 335;
            else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x > 450)
                ZombInit.zPosition[i].x = 450;
            //LEFT
            if(ZombInit.zPosition[i].x < -200) ZombInit.zPosition[i].x = -200;
            if(ZombInit.zPosition[i].x < 64 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430))
                ZombInit.zPosition[i].x = 64;
            else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y < 360)
                ZombInit.zPosition[i].y = 360;
            else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y > 425)
                ZombInit.zPosition[i].y = 425;
            //RIGHT
            if(ZombInit.zPosition[i].x > 1224) ZombInit.zPosition[i].x = 1224;
            if(ZombInit.zPosition[i].x > 930 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430))
                ZombInit.zPosition[i].x = 930;
            else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y < 360)
                ZombInit.zPosition[i].y = 360;
            else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y > 425)
                ZombInit.zPosition[i].y = 425;
        }

        //Map collision detection PLAYER
        //TOP
        if(PlayerInit.pPosition[0].y < 15) PlayerInit.pPosition[0].y = 15;
        //BOTTOM
        if(PlayerInit.pPosition[0].y > 905) PlayerInit.pPosition[0].y = 905;
        //LEFT
        if(PlayerInit.pPosition[0].x < 30) PlayerInit.pPosition[0].x = 30;
        //RIGHT
        if(PlayerInit.pPosition[0].x > 930) PlayerInit.pPosition[0].x = 930;

        //Bullet positioning
        if(!b.shot){
            b.bPosition.x = PlayerInit.pPosition[0].x + 20;
            b.bPosition.y = PlayerInit.pPosition[0].y + 17;
        }
        else{
            if(!b.bVelY) b.bPosition.x += b.bVelX * 75;
            else b.bPosition.y += b.bVelY * 75;
            if(b.bPosition.x < 0 || b.bPosition.x > 1024 || b.bPosition.y < 0 || b.bPosition.y > 1024){
                b.shot = false;
            }
        }
        
        //Game rendering
        SDL_SetRenderDrawColor(iSDL.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(iSDL.renderer);
        renderBackground(&iSDL, backTiles);
        //Renders all zombies
        for(int i = 0; i < ZombInit.nrOfZombies; i++){
            SDL_RenderCopyEx(iSDL.renderer, ZombInit.mZombie, &ZombInit.gZombie[zFrame[i].frame], &ZombInit.zPosition[i], 0, NULL, SDL_FLIP_NONE);
        }
        //Renders player
        for(int i = 0; i < PlayerInit.nrOfPlayers; i++){
            SDL_RenderCopyEx(iSDL.renderer, PlayerInit.mPlayer, &PlayerInit.gPlayer[pFrame], &PlayerInit.pPosition[i], 0, NULL, flip);
        }
        //Render bullet
        if(b.shot)
            SDL_RenderCopyEx(iSDL.renderer, b.mBullet, &b.gBullet[0], &b.bPosition, b.bUpDown, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(iSDL.renderer);
        //Delay 1/60th second
        SDL_Delay(1000/60);
    }
   // SDL_DestroyWindow(win);
   // SDL_Quit();
}
/*
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

void loadMedia(InitSDL* iSDL, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[], SDL_Texture **mBullet, SDL_Rect gBullet[]){
    //Map
    SDL_Surface* gTilesSurface = IMG_Load("resources/Textur32x32V8.PNG");
    *mTiles = SDL_CreateTextureFromSurface(iSDL->renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }

    //Zombie
    SDL_Surface* gZombieSurface = IMG_Load("resources/ZombieSheetSizeX2.png");
    *mZombie = SDL_CreateTextureFromSurface(iSDL->renderer, gZombieSurface);
    for(int i = 0; i < 8; i++){
        gZombie[i].x = 108 * (i % 2) + 6;
        if(i % 2 == 0) gZombie[i].y = (54 * i) / 2;
        else gZombie[i].y = gZombie[i-1].y;
        gZombie[i].w = 43;
        gZombie[i].h = 54;
    }

    //Player
    SDL_Surface* gPlayerSurface = IMG_Load("resources/pixel-768x768-31.png");
    *mPlayer = SDL_CreateTextureFromSurface(iSDL->renderer, gPlayerSurface);

    //Ståendes med kroppen mot skärmen med pistol
    gPlayer[0].x = 8;
    gPlayer[0].y = 400;
    gPlayer[0].w = 64;
    gPlayer[0].h = 64;

    //left and right
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

    //Up player
    gPlayer[9].x = 488;
    gPlayer[9].y = 16;
    gPlayer[9].w = 64;
    gPlayer[9].h = 64;

    gPlayer[10].x = 565;
    gPlayer[10].y = 16;
    gPlayer[10].w = 64;
    gPlayer[10].h = 64; 

    gPlayer[11].x = 645;
    gPlayer[11].y = 16;
    gPlayer[11].w = 64;
    gPlayer[11].h = 64; 

    gPlayer[12].x = 565;
    gPlayer[12].y = 111;
    gPlayer[12].w = 64;
    gPlayer[12].h = 64; 

    gPlayer[13].x = 645;
    gPlayer[13].y = 111;
    gPlayer[13].w = 64;
    gPlayer[13].h = 64; 

    gPlayer[14].x = 645;
    gPlayer[14].y = 111;
    gPlayer[14].w = 64;
    gPlayer[14].h = 64; 

    gPlayer[15].x = 97;
    gPlayer[15].y = 399;
    gPlayer[15].w = 69;
    gPlayer[15].h = 64;

    //Bullet
    SDL_Surface* gBulletSurface = IMG_Load("resources/bullet.png");
    *mBullet = SDL_CreateTextureFromSurface(iSDL->renderer, gBulletSurface);
    gBullet[0].x = 0;
    gBullet[0].y = 0;
    gBullet[0].w = 15;
    gBullet[0].h = 5;

    //Window Icon
    SDL_Surface* gWindowIcon = IMG_Load("resources/icon.png");
    SDL_SetWindowIcon(iSDL->win, gWindowIcon);
}
*/