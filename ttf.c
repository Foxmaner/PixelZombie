
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ttf.h"

#define PUBLIC /* empty */
#define PRIVATE static

/*PUBLIC Textbox createTextBox( int x, int y, int size,char text[]){
    textboxInit->posY = y;
    textboxInit->posX = x;
    strcpy(textboxInit->Text,text);
    SDL_Color textColor = {0, 0, 0, 0};
    
    return textboxInit;
}*/

PUBLIC void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}