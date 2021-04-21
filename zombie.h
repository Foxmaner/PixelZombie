#ifndef zombie_h
#define zombie_h

#include <stdio.h>

typedef struct zombie_type *Zombie;

int getZombiePositionX(Zombie a);
int getZombiePositionY(Zombie a);
Zombie createZombie(int x, int y);
void setZombiePositionY(Zombie a, int y);
void setY(Zombie a, int y);
int getZombieWidth();
int getZombieHeight();
int getZombieFrame(Zombie a);
int getSpawnPointX(int a);
int getSpawnPointY(int a);

#endif /* Zombie_h */

