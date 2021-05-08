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

void loadMedia(InitSDL* iSDL, Background_Tiles* backTiles, ZombieInit* ZombInit, Player_Init* PlayerInit, Bullet* b){
    //Map
    SDL_Surface* gTilesSurface = IMG_Load("resources/Textur32x32V8.PNG");
    backTiles->mTiles = SDL_CreateTextureFromSurface(iSDL->renderer, gTilesSurface);
    for (int i = 0; i < 32; i++) {
        backTiles->gTiles[i].x = i*getTileWidth();
        backTiles->gTiles[i].y = 0;
        backTiles->gTiles[i].w = getTileWidth();
        backTiles->gTiles[i].h = getTileHeight();
    }

    //Zombie
    SDL_Surface* gZombieSurface = IMG_Load("resources/ZombieSheetSizeX2.png");
    ZombInit->mZombie = SDL_CreateTextureFromSurface(iSDL->renderer, gZombieSurface);
    //X O O O   <---Where in the sprite
    //O O O O
    for(int i = 0; i < 8; i++){
        ZombInit->gZombie[i].x = 108 * (i % 2) + 6;
        if(i % 2 == 0) ZombInit->gZombie[i].y = (54 * i) / 2;
        else ZombInit->gZombie[i].y = ZombInit->gZombie[i-1].y;
        ZombInit->gZombie[i].w = 43;
        ZombInit->gZombie[i].h = 54;
    }
    //O X O O
    //O O O O
    for(int i = 8; i < 16; i++){
        //ZombInit->gZombie[i].x = (108 * (i % 2)) + 166;       This line does not work for some fucking reason, even though the exakt same line reoccurs at line 57
        if(i % 2 == 0) ZombInit->gZombie[i].y = (54 * i) / 2;
        else ZombInit->gZombie[i].y = ZombInit->gZombie[i-1].y;
        ZombInit->gZombie[i].w = 43;
        ZombInit->gZombie[i].h = 54;
    }
    ZombInit->gZombie[8].x = 166;            //Because line 40 does not work, it had to be manually inputed...
    ZombInit->gZombie[9].x = 274;
    ZombInit->gZombie[10].x = 166;
    ZombInit->gZombie[11].x = 274;
    ZombInit->gZombie[12].x = 166;
    ZombInit->gZombie[13].x = 274;
    ZombInit->gZombie[14].x = 166;
    ZombInit->gZombie[15].x = 274;
    //O O O O
    //O X O O
    for(int i = 16; i < 24; i++){
        ZombInit->gZombie[i].x = (108 * (i % 2)) + 166;
        if(i % 2 == 0) ZombInit->gZombie[i].y = ((54 * i) / 2) + 213;
        else ZombInit->gZombie[i].y = ZombInit->gZombie[i-1].y;
        ZombInit->gZombie[i].w = 43;
        ZombInit->gZombie[i].h = 54;
    }
    //O O O O
    //O O X O       DOWN            It is possible to refine this code, not willing to spend that time now.
    for(int i = 24; i < 32; i++){
        ZombInit->gZombie[i].w = 45;
        ZombInit->gZombie[i].h = 54;
    }
    ZombInit->gZombie[24].x = 327;
    ZombInit->gZombie[24].y = 214;

    ZombInit->gZombie[25].x = 434;
    ZombInit->gZombie[25].y = 214;
    //LEFT
    ZombInit->gZombie[26].x = 327;
    ZombInit->gZombie[26].y = 267; //or 268

    ZombInit->gZombie[27].x = 434;
    ZombInit->gZombie[27].y = 267; //or 268
    //RIGHT
    ZombInit->gZombie[28].x = 322;
    ZombInit->gZombie[28].y = 320;

    ZombInit->gZombie[29].x = 429;
    ZombInit->gZombie[29].y = 320;
    //UP
    ZombInit->gZombie[30].x = 322;
    ZombInit->gZombie[30].y = 374;

    ZombInit->gZombie[31].x = 429;
    ZombInit->gZombie[31].y = 374;

    //Player
    SDL_Surface* gPlayerSurface = IMG_Load("resources/pixel-768x768-31.png");
    PlayerInit->mPlayer = SDL_CreateTextureFromSurface(iSDL->renderer, gPlayerSurface);

    //Ståendes med kroppen mot skärmen med pistol
    PlayerInit->gPlayer[0].x = 8;
    PlayerInit->gPlayer[0].y = 400;
    PlayerInit->gPlayer[0].w = 64;
    PlayerInit->gPlayer[0].h = 64;

    //left and right
    PlayerInit->gPlayer[1].x = 8; //Det är 96 mellan varje bild sidleds
    PlayerInit->gPlayer[1].y = 210;//80 mellan varje rad
    PlayerInit->gPlayer[1].w = 64;
    PlayerInit->gPlayer[1].h = 64;
 
    PlayerInit->gPlayer[2].x = 104;
    PlayerInit->gPlayer[2].y = 210;
    PlayerInit->gPlayer[2].w = 64;
    PlayerInit->gPlayer[2].h = 64;

    PlayerInit->gPlayer[3].x = 200;
    PlayerInit->gPlayer[3].y = 210;
    PlayerInit->gPlayer[3].w = 64;
    PlayerInit->gPlayer[3].h = 64;

    PlayerInit->gPlayer[4].x = 296;
    PlayerInit->gPlayer[4].y = 210;
    PlayerInit->gPlayer[4].w = 64;
    PlayerInit->gPlayer[4].h = 64;

    PlayerInit->gPlayer[5].x = 392;
    PlayerInit->gPlayer[5].y = 210;
    PlayerInit->gPlayer[5].w = 64;
    PlayerInit->gPlayer[5].h = 64;

    PlayerInit->gPlayer[6].x = 488;
    PlayerInit->gPlayer[6].y = 210;
    PlayerInit->gPlayer[6].w = 64;
    PlayerInit->gPlayer[6].h = 64;

    PlayerInit->gPlayer[7].x = 584;
    PlayerInit->gPlayer[7].y = 210;
    PlayerInit->gPlayer[7].w = 64;
    PlayerInit->gPlayer[7].h = 64;

    PlayerInit->gPlayer[8].x = 680;
    PlayerInit->gPlayer[8].y = 210;
    PlayerInit->gPlayer[8].w = 64;
    PlayerInit->gPlayer[8].h = 64; 

    //Up player
    PlayerInit->gPlayer[9].x = 488;
    PlayerInit->gPlayer[9].y = 16;
    PlayerInit->gPlayer[9].w = 64;
    PlayerInit->gPlayer[9].h = 64;

    PlayerInit->gPlayer[10].x = 565;
    PlayerInit->gPlayer[10].y = 16;
    PlayerInit->gPlayer[10].w = 64;
    PlayerInit->gPlayer[10].h = 64; 

    PlayerInit->gPlayer[11].x = 645;
    PlayerInit->gPlayer[11].y = 16;
    PlayerInit->gPlayer[11].w = 64;
    PlayerInit->gPlayer[11].h = 64; 

    PlayerInit->gPlayer[12].x = 565;
    PlayerInit->gPlayer[12].y = 111;
    PlayerInit->gPlayer[12].w = 64;
    PlayerInit->gPlayer[12].h = 64; 

    PlayerInit->gPlayer[13].x = 645;
    PlayerInit->gPlayer[13].y = 111;
    PlayerInit->gPlayer[13].w = 64;
    PlayerInit->gPlayer[13].h = 64; 

    PlayerInit->gPlayer[14].x = 645;
    PlayerInit->gPlayer[14].y = 111;
    PlayerInit->gPlayer[14].w = 64;
    PlayerInit->gPlayer[14].h = 64; 

    PlayerInit->gPlayer[15].x = 97;
    PlayerInit->gPlayer[15].y = 399;
    PlayerInit->gPlayer[15].w = 69;
    PlayerInit->gPlayer[15].h = 64;

    //Bullet
    SDL_Surface* gBulletSurface = IMG_Load("resources/bullet.png");
    b->mBullet = SDL_CreateTextureFromSurface(iSDL->renderer, gBulletSurface);
    b->gBullet[0].x = 0;
    b->gBullet[0].y = 0;
    b->gBullet[0].w = 15;
    b->gBullet[0].h = 5;

    //Window Icon
    SDL_Surface* gWindowIcon = IMG_Load("resources/icon.png");
    SDL_SetWindowIcon(iSDL->win, gWindowIcon);
}