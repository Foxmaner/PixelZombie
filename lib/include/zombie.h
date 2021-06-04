#ifndef zombie_h
#define zombie_h

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct zombie_type{
    int ZOMBIE_POSITION_X;
    int ZOMBIE_POSITION_Y;
    int hitPoint;
    bool alive;
};typedef struct zombie_type *Zombie;
Zombie z[100];

struct zombie_frame{
    int frame;
    int diagonal;
    int counter;
    int skin;
};typedef struct zombie_frame ZombieFrame;
ZombieFrame zFrame[100];

struct Zombie_Init{
    SDL_Texture *mZombie;
    SDL_Rect gZombie[32];
    int nrOfZombies;
    SDL_Rect zPosition[100];
};typedef struct Zombie_Init ZombieInit;
ZombieInit ZombInit;

int getZombiePositionX(Zombie a);
int getZombiePositionY(Zombie a);

//Allocate memory to create a zombie, must make free when done.
Zombie createZombie(int x, int y);

void setZombiePositionY(Zombie a, int y);
int getZombieWidth();
int getZombieHeight();
int getZombieHP(Zombie a);

//Gives and spawn zombies at "random" spawnpoint and give random skin
void createAllZombies();
int getCurrentLevel();
int getZSpawnPointX(int a);
int getZSpawnPointY(int a);

//Changes the zombie frame making it appear like its walking
void changeZFrameX(int frameA, int frameB, int i); 
void changeZFrameY(int frameA, int frameB, int i);

//Check if zombies collide with eachother
bool checkZCollisionWithZ(SDL_Rect zombie1, SDL_Rect zombie2);

//Check if zombies collide with player
bool checkZCollisionWithP(SDL_Rect zombie, SDL_Rect player);

void killZombie(Zombie a, int i, int playerID);

//if all zombies are dead, create a "new" wave + 2 more zombies.
void respawnZombie();

//Wait x ms.
int msTimer(int *pCurrentTime, int *pLastRecordedTime, int ms); 

#endif /* Zombie_h */