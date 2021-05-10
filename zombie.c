#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "zombie.h"
#include "gameInit.h"

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ZOMBIE_WIDTH = 54;
PRIVATE int ZOMBIE_HEIGTH = 54;

PRIVATE int zSpawnPointX0 = -200;
PRIVATE int zSpawnPointY0 = 360;
PRIVATE int zSpawnPointX1 = 335;
PRIVATE int zSpawnPointY1 = 1224;
PRIVATE int zSpawnPointX2 = 1224;
PRIVATE int zSpawnPointY2 = 360;

PUBLIC Zombie createZombie(int x, int y){
    Zombie z = malloc(sizeof(struct zombie_type));
    z->ZOMBIE_POSITION_Y = y;
    z->ZOMBIE_POSITION_X = x;
    z->hitPoint = 1;
    z->alive = 1;
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

PUBLIC void createAllZombies(){
    for(int i = 0; i < ZombInit.nrOfZombies; i++){
        z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
        ZombInit.zPosition[i].x = getZombiePositionX(z[i]);
        ZombInit.zPosition[i].y = getZombiePositionY(z[i]);
        ZombInit.zPosition[i].w = 43;
        ZombInit.zPosition[i].h = 54;
        zFrame[i].skin = ((rand() % 4 + 1) * 8) - 8;
    }
}

PUBLIC int getZSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0 + (rand() % 200);
    else if(a == 1)
        return zSpawnPointX1 + (rand() % 115);
    else if(a == 2)
        return zSpawnPointX2 - (rand() % 200);
}

PUBLIC int getZSpawnPointY(int a){
    if(a == 0)
        return zSpawnPointY0 + (rand() % 65);
    else if(a == 1)
        return zSpawnPointY1 - (rand() % 200);
    else if(a == 2)
        return zSpawnPointY2 + (rand() % 65);
}

PUBLIC void changeZFrameX(int frameA, int frameB, int i){
    zFrame[i].diagonal = 0;
    if(zFrame[i].frame == frameA && zFrame[i].counter >= 25){
        zFrame[i].frame = frameB;
        zFrame[i].counter = 0;
    }
    else if(zFrame[i].frame == frameB){
        if(zFrame[i].counter >= 25){
            zFrame[i].frame = frameA;
            zFrame[i].counter = 0;
        }
        else (zFrame[i].counter)++;
    }
    else{
        zFrame[i].frame = frameA;
        (zFrame[i].counter)++;
    }
}

PUBLIC void changeZFrameY(int frameA, int frameB, int i){
    if((zFrame[i].diagonal)++ > 0){
        if(zFrame[i].frame == frameA && zFrame[i].counter >= 25){
            zFrame[i].frame = frameB;
            zFrame[i].counter = 0;
        }
        else if(zFrame[i].frame == frameB){
            if(zFrame[i].counter >= 25){
                zFrame[i].frame = frameA;
                zFrame[i].counter = 0;
            }
            else (zFrame[i].counter)++;
        }
        else{
            zFrame[i].frame = frameA;
            (zFrame[i].counter)++;
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

PUBLIC void killZombie(Zombie a){
    a->alive = 0;
}

PUBLIC int msTimer(int *pCurrentTime, int *pLastRecordedTime, int ms){
    *pCurrentTime = SDL_GetTicks();
    if(*pCurrentTime >= *pLastRecordedTime + ms){
        *pLastRecordedTime = *pCurrentTime;
        return 1;
    }
    else return 0;
}