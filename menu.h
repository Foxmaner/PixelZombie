#ifndef menu_h
#define menu_h
#include <stdio.h>
#include <SDL2/SDL.h>
#include "gameInit.h"
struct menubackground{
    int MENUBACKGROUND_POSITION_X;
    int MENUBACKGROUND_POSITION_Y;
}; typedef struct menubackground *MenuBackground;

struct menusync{
    SDL_Texture *mBackgroundMenu;
    SDL_Rect gMenubackground[1];
};typedef struct menusync Menu_Init;
Menu_Init MenuInit;

void mainMenu(SDL_Renderer *renderer,int *lookingforgame,int *hostinggame, int *credits, int *back);
void creditMenu(SDL_Renderer *renderer, int *credits, int *back);
void findinggameLobby(SDL_Renderer *renderer, int *back, int *lookingforgame,int *startrender ,char* IPaddress);
void hostinglobby(SDL_Renderer *renderer, int *back, int *hostinggame, int *startrender,char* AmountPlayer);
void setStartRender(int a);
int CheckIfHost();
int checkIfGamestarted();
void theMenu(SDL_Renderer *renderer);
#endif /* menu_h */