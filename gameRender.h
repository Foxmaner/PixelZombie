#ifndef gameRender_h
#define gameRender_h

#include <stdio.h>

void renderBackground(InitSDL* iSDL, Background_Tiles backTiles);
void renderMenu();
void SetRenderDrawColor();
void clearRenderer();
void renderAllZombies();
void renderAllPlayers();
void renderBullet();
void renderPreset();

void renderGame();

#endif