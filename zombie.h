#ifndef zombie_h
#define zombie_h

#include <stdio.h>
#include <stdbool.h>

struct zombie_type{
    int ZOMBIE_POSITION_X;
    int ZOMBIE_POSITION_Y;
    int hitPoint;
    bool alive;
};typedef struct zombie_type *Zombie;

struct zombie_frame{
    int frame;
    int diagonal;
    int counter;
}; typedef struct zombie_frame ZombieFrame;

int getZombiePositionX(Zombie a);
int getZombiePositionY(Zombie a);
Zombie createZombie(int x, int y);
void setZombiePositionY(Zombie a, int y);
int getZombieWidth();
int getZombieHeight();
int getZombieHP(Zombie a);
int getZSpawnPointX(int a);
int getZSpawnPointY(int a);
void changeZFrameX(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal);
void changeZFrameY(int *pCurrentFrame, int frameA, int frameB, int *pFrameCounter, int *pDiagonal);
bool checkZCollisionWithP(SDL_Rect zombie, SDL_Rect player);
void killZombie(Zombie a);

#endif /* Zombie_h */

