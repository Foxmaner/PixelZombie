#ifndef gameMedia_h
#define gameMedia_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameInit.h"

void loadMedia(InitSDL* iSDL, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mZombie, SDL_Rect gZombie[], SDL_Texture **mPlayer, SDL_Rect gPlayer[], SDL_Texture **mBullet, SDL_Rect gBullet[]);

#endif