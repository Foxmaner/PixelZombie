
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/ttf.h"
#include "../include/gameInit.h"

#define PUBLIC /* empty */
#define PRIVATE static

PUBLIC void createTextbox(SDL_Renderer *renderer, int x, int y, char *text, int size){
    char *font_path;
    font_path = "resources/fonts/OpenSans-BoldItalic.ttf";
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, size);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture;
    SDL_Rect rect;
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
}

//Takes one digit and makes it a char
PUBLIC void createTextFromInt(SDL_Renderer *renderer, int x, int y, int variable, int size){
    char charValue[2] = "X";
    charValue[0] = variable + '0';
    createTextbox(renderer, x, y, charValue, size);
}

//Creates gametimer in HUD
PUBLIC void createTimer(){
    int Minutes = 0, TwoletterMinutes = 0, Seconds, TwoletterSeconds = 0;
    if (10 > getSeconds()){
        Seconds = getSeconds();
    }
    else if(10 <= getSeconds()){
        Seconds = getSeconds() % 10;
        TwoletterSeconds = (getSeconds() - Seconds) / 10;
    }
    else{
        Seconds = 0;
    }

    createTextbox(iSDL.renderer, 875, 0, "S:", 40);
    createTextFromInt(iSDL.renderer, 950, 0, Seconds, 40);
    createTextFromInt(iSDL.renderer, 925, 0, TwoletterSeconds, 40);

    Minutes = timer.minute;
    if(timer.minute > 10){
        Minutes = timer.minute % 10;
        TwoletterMinutes = (timer.minute - Minutes) / 10;
    }

    createTextbox(iSDL.renderer, 725, 0, "M:", 40);
    createTextFromInt(iSDL.renderer, 825, 0, Minutes, 40);
    createTextFromInt(iSDL.renderer, 800, 0, TwoletterMinutes, 40);
    createTextbox(iSDL.renderer, 625, 0, "H:", 40);
    createTextFromInt(iSDL.renderer, 685, 0, timer.hour, 40);
}