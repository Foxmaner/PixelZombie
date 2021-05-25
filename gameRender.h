#ifndef gameRender_h
#define gameRender_h

#include <stdio.h>
#include "gameInit.h"

void renderBackground(InitSDL* iSDL, Background_Tiles backTiles);
void renderHealthBar();
void renderMenu();


//Draws white canvas

void SetRenderDrawColor();

void clearRenderer();
//Render menu and all menu options with buttons to navigate
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