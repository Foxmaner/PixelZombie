
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ttf.h"

#define PUBLIC /* empty */
#define PRIVATE static

PUBLIC void createTextbox(SDL_Renderer *renderer, int x, int y, char *text, int size) {
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
    SDL_FreeSurface(surface);
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}