#ifndef gameRender_h
#define gameRender_h

#include <stdio.h>

void renderBackground(InitSDL* iSDL, Background_Tiles backTiles);
int renderMenu(int Buttonpressed);
void SetRenderDrawColor();
void clearRenderer();
void renderAllZombies();
void renderAllPlayers();
void renderBullet();
void renderPreset();

void renderGame();

#endif