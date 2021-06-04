#ifndef ttf_h
#define ttf_h

#include <stdio.h>
#include <SDL2/SDL.h>

#define TEXTSIZE 10

void createTextbox(SDL_Renderer *renderer, int x, int y, char *text, int size);

//Takes a digit and makes it a char
void createTextFromInt(SDL_Renderer *renderer, int x, int y, int variable, int size);

//Creates timer for HUD
void createTimer();

#endif