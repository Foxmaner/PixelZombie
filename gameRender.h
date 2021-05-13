#ifndef gameRender_h
#define gameRender_h

#include <stdio.h>
#include "gameInit.h"

void setMenuInitiaited(int a);
void renderBackground(InitSDL* iSDL, Background_Tiles backTiles);
void renderHealthBar();
void renderMenu();
void SetRenderDrawColor();
void clearRenderer();
void renderAllZombies();
void renderAllPlayers();
void renderBullet();
void renderPreset();

void renderGame();

#endif