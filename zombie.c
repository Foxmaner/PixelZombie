#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "zombie.h"

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ZOMBIE_WIDTH = 54;
PRIVATE int ZOMBIE_HEIGTH = 54;

PRIVATE int zSpawnPointX0 = 50;
PRIVATE int zSpawnPointY0 = 425;
PRIVATE int zSpawnPointX1 = 400;
PRIVATE int zSpawnPointY1 = 925;
PRIVATE int zSpawnPointX2 = 950;
PRIVATE int zSpawnPointY2 = 425;

PUBLIC Zombie createZombie(int x, int y){
    Zombie z = malloc(sizeof(struct zombie_type));
    z->ZOMBIE_POSITION_Y = y;
    z->ZOMBIE_POSITION_X = x;
    z->hitPoint = 1;
    return z;
}

PUBLIC void setZombiePositionY(Zombie a, int y){
    a->ZOMBIE_POSITION_Y = y;
}

PUBLIC int getZombiePositionX(Zombie a){
    return a->ZOMBIE_POSITION_X;
}


PUBLIC int getZombiePositionY(Zombie a){
    return a->ZOMBIE_POSITION_Y;
}

PUBLIC int getZombieWidth(){
    return ZOMBIE_WIDTH;
}

PUBLIC int getZombieHeight(){
    return ZOMBIE_HEIGTH;
}

PUBLIC int getZombieHitPoint(Zombie a){
    return a->hitPoint;
}

PUBLIC int getZSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0 + (rand() % 200);
    else if(a == 1)
        return zSpawnPointX1 + (rand() % 50);
    else if(a == 2)
        return zSpawnPointX2 + (rand() % 200);
}

PUBLIC int getZSpawnPointY(int a){
    if(a == 0)
        return zSpawnPointY0 + (rand() % 50);
    else if(a == 1)
        return zSpawnPointY1 + (rand() % 200);
    else if(a == 2)
        return zSpawnPointY2 + (rand() % 50);
}

PUBLIC void changeZFrameX(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal){
    *pDiagonal = 0;
    if(*pCurrentFrame == frameA && *pFrameCounter >= 25){
        *pCurrentFrame = frameB;
        *pFrameCounter = 0;
    }
    else if(*pCurrentFrame == frameB){
        if(*pFrameCounter >= 25){
            *pCurrentFrame = frameA;
            *pFrameCounter = 0;
        }
        else (*pFrameCounter)++;
    }
    else{
        *pCurrentFrame = frameA;
        (*pFrameCounter)++;
    }
}

PUBLIC void changeZFrameY(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal){
    if((*pDiagonal)++ > 0){
        if(*pCurrentFrame == frameA && *pFrameCounter >= 25){
            *pCurrentFrame = frameB;
            *pFrameCounter = 0;
        }
        else if(*pCurrentFrame == frameB){
            if(*pFrameCounter >= 25){
                *pCurrentFrame = frameA;
                *pFrameCounter = 0;
            }
            else (*pFrameCounter)++;
        }
        else{
            *pCurrentFrame = frameA;
            (*pFrameCounter)++;
        }
    }
}

PUBLIC bool checkZCollisionWithP(SDL_Rect zombie, SDL_Rect player){
    int zLeft, zRight, zTop, zBottom;
    int plLeft, plRight, plTop, plBottom;
    
    //Calculate zombie hitbox
    zLeft = zombie.x;
    zRight = zombie.x + zombie.w;
    zTop = zombie.y;
    zBottom = zombie.y + zombie.h;

    //Calculate player hitbox
    plLeft = player.x;
    plRight = player.x + player.w;
    plTop = player.y;
    plBottom = player.y + player.h;
    
    //Check if sides collide with eachother
    if(zTop > plBottom) return false;
    if(zBottom < plTop) return false;
    if(zLeft > plRight) return false;
    if(zRight < plLeft) return false;
    //if sides are not outside eachother(aka collision), then return true
    return true;
}