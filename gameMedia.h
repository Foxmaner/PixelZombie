#ifndef gameMedia_h
#define gameMedia_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "gameInit.h"
#include "zombie.h"
#include "player.h"
#include "menu.h"

struct MusicFiles{
    Mix_Music *bgGameMusic;
    Mix_Music *bgMenuMusic;
};typedef struct MusicFiles MusicFiles;
MusicFiles music;

struct SoundEffects{
    Mix_Chunk *sfxPistolShot;
    Mix_Chunk *sfxPlayerHurt;
    Mix_Chunk *sfxPlayerDie;
    Mix_Chunk *sfxZombieDie;
    Mix_Chunk *sfxZombieAttack;
    Mix_Chunk *sfxZombieBrain;
};typedef struct SoundEffects SoundEffects;
SoundEffects sounds;

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