#ifndef zombie_h
#define zombie_h

#include <stdio.h>

typedef struct zombie_type *Zombie;

struct zombie_frame{
    int frame;
    int diagonal;
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
void changeZFrameX(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal);
void changeZFrameY(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal);

#endif /* Zombie_h */

