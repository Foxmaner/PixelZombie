#ifndef zombie_h
#define zombie_h

#include <stdio.h>
#include <stdbool.h>

typedef struct zombie_type *Zombie;

struct zombie_frame{
    int frame;
    bool diagonal;
}; typedef struct zombie_frame ZombieFrame;

int getZombiePositionX(Zombie a);
int getZombiePositionY(Zombie a);
Zombie createZombie(int x, int y);
void setZombiePositionY(Zombie a, int y);
void setY(Zombie a, int y);
int getZombieWidth();
int getZombieHeight();
int getZombieFrame(Zombie a);
int getZSpawnPointX(int a);
int getZSpawnPointY(int a);

#endif /* Zombie_h */

