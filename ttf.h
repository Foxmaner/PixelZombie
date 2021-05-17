#ifndef ttf_h
#define ttf_h

#define TEXTSIZE 10

#include <stdio.h>
#include <SDL2/SDL.h>


void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect); 
#endif