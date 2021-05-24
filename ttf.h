#ifndef ttf_h
#define ttf_h

#define TEXTSIZE 10

#include <stdio.h>
#include <SDL2/SDL.h>


void createTextbox(SDL_Renderer *renderer, int x, int y, char *text, int size);
#endif