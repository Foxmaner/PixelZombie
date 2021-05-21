#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "gameQuit.h"
#include "gameInit.h"
#include "gameMedia.h"

void quitGame(){
    Mix_FreeMusic(music.bgGameMusic);
    Mix_FreeMusic(music.bgMenuMusic);

    Mix_FreeChunk(sounds.sfxPistolShot);
    Mix_FreeChunk(sounds.sfxPlayerDie);
    Mix_FreeChunk(sounds.sfxPlayerHurt);
    Mix_FreeChunk(sounds.sfxZombieAttack);
    Mix_FreeChunk(sounds.sfxZombieBrain);
    Mix_FreeChunk(sounds.sfxZombieDie);

    SDL_DestroyTexture(StartInit.mstartbutton);
    SDL_DestroyTexture(backTiles.mTiles);
    SDL_DestroyTexture(ZombInit.mZombie);
    SDL_DestroyTexture(PlayerInit.mPlayer);
    SDL_DestroyTexture(b.mBullet);
    SDL_DestroyTexture(h.mHeart);

    SDL_DestroyWindow(iSDL.win);
    SDL_DestroyRenderer(iSDL.renderer);

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}