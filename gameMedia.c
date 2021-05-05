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