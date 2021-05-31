#ifndef ttf_h
#define ttf_h

#define TEXTSIZE 10

#include <stdio.h>
#include <SDL2/SDL.h>


void createTextbox(SDL_Renderer *renderer, int x, int y, char *text, int size);
//Tar en ensiffrig int och gör om den till en char
void createTextFromInt(SDL_Renderer *renderer, int x, int y, int variable, int size);
//Skapar en timer specifikt för att rendera tiden på skärmen.
void createTimer();
#endif