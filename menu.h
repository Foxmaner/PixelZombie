#ifndef menu_h
#define menu_h
#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameInit.h"
struct startbutton{
    int MENUBACKGROUND_POSITION_X;
    int MENUBACKGROUND_POSITION_Y;
    int INITSTART;
}; typedef struct startbutton *Startbutton;

struct menusync{
    SDL_Texture *mBackgroundMenu;
    SDL_Rect gMenubackground[1];
};typedef struct menusync Menu_Init;
Menu_Init MenuInit;

void mainMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back);
void creditMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back);
void playerLobby(SDL_Renderer *renderer,int *startrender, int *lobby, int *credits, int *back, char* IPaddress);
#endif /* menu_h */