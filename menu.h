#ifndef menu_h
#define menu_h
#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameInit.h"

struct menubackground{
    int MBACKGROUND_POSITION_X;
    int MBACKGROUND_POSITION_Y;
    int INITMBACKGROUNDT;
}; typedef struct menubackground *Menubackground;

struct backgroundSync{
    SDL_Texture *mMenubackground;
    SDL_Rect gMenubackground[1];
    SDL_Rect WhichPlayer[4];
};typedef struct backgroundSync mBackground_Init;
mBackground_Init mBackgroundInit;

void mainMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back);
void creditMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back);
void playerLobby(SDL_Renderer *renderer,int *startrender, int *lobby, int *credits, int *back, char* IPaddress);
#endif /* menu_h */