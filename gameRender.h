#ifndef gameRender_h
#define gameRender_h

#include <stdio.h>
#include "gameInit.h"

//Sets startrender in order to make game over
void setStartRender(int a);

//Draws white canvas
void SetRenderDrawColor();

void clearRenderer();

void renderMenu();

void renderBackground(InitSDL* iSDL, Background_Tiles backTiles);

//Renders 0-3 hearts depending on players hitpoints
void renderHealthBar();

//Renders all alive players
void renderAllPlayers();

//Renders all alive zombies
void renderAllZombies();

//Renders bullet if shot
void renderBullet();

void renderPreset();

//Renders menu at start and game over...
//...when game start renders game
void renderGame();

#endif