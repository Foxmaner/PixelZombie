#ifndef gameMedia_h
#define gameMedia_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "zombie.h"
#include "player.h"
#include "menu.h"

void loadMedia(InitSDL* iSDL, Background_Tiles* backTiles, ZombieInit* ZombInit, Player_Init* PlayerInit, Bullet* b, Start_Init* StartInit);
void playBgGameMusic();
void playBgMenuMusic();
void playPistolShot();
void playPlayerHurt();
void playPlayerDie();
void playZombieDie();
void playZombieAttack();
void playZombieBrain();

#endif