#ifndef gameInit_h
#define gameInit_h

#include <stdio.h>
#include <stdbool.h>
#include "menu.h"

//Struct that holds window and renderer varieble
struct InitSDL{
    SDL_Window* win;
    SDL_Renderer* renderer;
};typedef struct InitSDL InitSDL;
InitSDL iSDL;

//Struct that holds varibles for the game timer
struct GameTimer{
    int second;
    int minute;
    int hour;
    int now;
    int before;
};typedef struct GameTimer GameTimer;
GameTimer timer;
//Creates the initiall time values
GameTimer initTime();

int getSeconds();

//Struct that holds varibles for background textures
struct Background_Tiles{
    SDL_Texture *mTiles;
    SDL_Rect gTiles[32];
}; typedef struct Background_Tiles Background_Tiles;
Background_Tiles backTiles;

//Struct that holds variables for the bullet
struct Bullet{
    SDL_Texture *mBullet;
    SDL_Rect gBullet[1];
    SDL_Rect bPosition;
    bool shot;
    int lastShotTime , currentShotTime;
    int bVelX, bVelY, bUpDown;
};typedef struct Bullet Bullet;
Bullet b;
//Creates the bullet
Bullet createBullet();

//Struct that holds variables for healthbar
struct Heart{
    SDL_Texture *mHeart;
    SDL_Rect gHeart[1];
    SDL_Rect hPosition[3];
};typedef struct Heart Heart;
Heart h;
//Creates the healthbar
Heart createHeart();

//Struct that holds varibles that tracks if the game 
//has been initially initilized and if the game is over
struct isGameInitOrOver{
    bool initedGame;
    bool gameOver;
};typedef struct isGameInitOrOver IGIO;
IGIO GIO;

//Initilizes SDL VIDEO, TIMER & AUDIO
void initSDL();

//Initilizes window and calls to initilize renderer
void initWindow();

//Initilizes renderer
void initRenderer(SDL_Window* pWin);

//Initilizes audio frequency, format, channels & chunk
void initAudio();

//Starts the heads-up-display game timer
//Values from 00h 00m 00s - 24h 59m 59s
void startGameTimer();


//Calls all initilizers
void initGame();

#endif