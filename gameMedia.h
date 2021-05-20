#ifndef gameMedia_h
#define gameMedia_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "zombie.h"
#include "player.h"
#include "menu.h"

void loadMedia(InitSDL* iSDL, Background_Tiles* backTiles, ZombieInit* ZombInit, Player_Init* PlayerInit, Bullet* b, Heart* h, Start_Init* StartInit);

//Play background music
void playBgGameMusic();
void playBgMenuMusic();

//Play sound effects
void playPistolShot();
void playPlayerHurt();
void playPlayerDie();
void playZombieDie();
void playZombieAttack();
void playZombieBrain();

#endif