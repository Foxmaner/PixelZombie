#ifndef ttf_h
#define ttf_h

#define TEXTSIZE 10

#include <stdio.h>
#include <SDL2/SDL.h>

struct text_box{
    char Text[TEXTSIZE];
    int posX;
    int posY;

};typedef struct text_box *Textbox;

struct Textbox_Init{
    SDL_Texture *mText;
    SDL_Rect gText[4];
}; typedef struct Textbox_Init Textbox_Init;
Textbox_Init textboxInit;

Textbox createTextBox( int x, int y, int size,char text[]);

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect); 
#endif