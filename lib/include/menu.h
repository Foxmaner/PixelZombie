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
//Renders main menu
void mainMenu(SDL_Renderer *renderer,int *lookingforgame,int *hostinggame, int *credits, int *back);
//Renders credit screen
void creditMenu(SDL_Renderer *renderer, int *credits, int *back);
//Renders game lobby for non host
void findinggameLobby(SDL_Renderer *renderer, int *back, int *lookingforgame,int *startrender ,char* IPaddress);
//Renders lobby for host
void hostinglobby(SDL_Renderer *renderer, int *back, int *hostinggame, int *startrender,char* AmountPlayer);
//Sets startrenderer to specific value, to stop game
void setStartRender(int a);
//checks if connecting player is host
int CheckIfHost();
//Checks if person is non host
int CheckIfLooking();
//Used to check if person has initiated to start game
int checkIfGamestarted();
//Contains whole menu and all menu options
void theMenu(SDL_Renderer *renderer);
#endif /* menu_h */