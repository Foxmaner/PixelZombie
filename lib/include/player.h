#ifndef player_h
#define player_h

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct player_type{
    int PLAYER_POSITION_X;
    int PLAYER_POSITION_Y;
};typedef struct player_type *Player;

struct Player_Init{
    int nrOfPlayers;
    SDL_Texture *mPlayer;
    SDL_Texture *mPlayerBlack;
    SDL_Rect gPlayer[16];
    Player p[4];
    SDL_Rect pPosition[4];
    int pFrame[4];
    SDL_RendererFlip flip[4];
    int hitPoint[4];
    int playerID;
    bool alive[4];
};typedef struct Player_Init Player_Init;
Player_Init PlayerInit;

//returns player's specific X position
int getPlayerPositionX(Player a);

//returns player's specific Y position
int getPlayerPositionY(Player a);

Player createPlayer(int x, int y);

//sets player position to specific Y value
void setPlayerPositionY(Player a, int y);

//sets player position to specific X value
void setPlayerPositionX(Player a, int x);

//returns player's specific width of texture
int getPlayerWidth();

//returns player's specific height of texture
int getPlayerHeight();

//returns player´s specific current health
int getPlayerHitpoint(int playerID);

//Create all player with their own spawnpoint
void createAllPlayers();

//Decides what X value the player will spawn on
int getSpawnPointX(int a);

//Decides what Y value the player will spawn on
int getSpawnPointY(int a);

#endif /* Player_h */