#include <stdlib.h>
#include "zombie.h"


#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ZOMBIE_WIDTH = 15;
PRIVATE int ZOMBIE_HEIGTH = 15;

struct zombie_type{
    int ZOMBIE_POSITION_X;
    int ZOMBIE_POSITION_Y;
    int ZOMBIE_FRAME;
    int slow;
};

PUBLIC Zombie createZombie(int x, int y){
    Zombie s = malloc(sizeof(struct zombie_type));
    s->ZOMBIE_POSITION_Y = y;
    s->ZOMBIE_POSITION_X = x;
    s->ZOMBIE_FRAME = 0;
    s->slow = 1;
    return s;
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
