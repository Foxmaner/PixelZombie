#include <stdlib.h>
#include "zombie.h"


#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ZOMBIE_WIDTH = 54;
PRIVATE int ZOMBIE_HEIGTH = 54;

PRIVATE int zSpawnPointX0 = 500;
PRIVATE int zSpawnPointY0 = 500;
PRIVATE int zSpawnPointX1 = 1040;
PRIVATE int zSpawnPointY1 = 400;

struct zombie_type{
    int ZOMBIE_POSITION_X;
    int ZOMBIE_POSITION_Y;
    int ZOMBIE_FRAME;
    int slow;
};

PUBLIC Zombie createZombie(int x, int y){
    Zombie z = malloc(sizeof(struct zombie_type));
    z->ZOMBIE_POSITION_Y = y;
    z->ZOMBIE_POSITION_X = x;
    z->ZOMBIE_FRAME = 0;
    z->slow = 1;
    return z;
}

void setY(Zombie a, int y){
    a->ZOMBIE_POSITION_Y = y;
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

PUBLIC int getZombieFrame(Zombie a){
    return a->ZOMBIE_FRAME;
}

PUBLIC int getZSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0;
    else if(a == 1)
        return zSpawnPointX1;
}

PUBLIC int getZSpawnPointY(int a){
    if(a == 0)
        return zSpawnPointY0;
    else if(a == 1)
        return zSpawnPointY1;
}