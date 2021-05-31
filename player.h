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

int getPlayerPositionX(Player a); //returns player's specific X position
int getPlayerPositionY(Player a); //returns player's specific Y position
Player createPlayer(int x, int y);
void setPlayerPositionY(Player a, int y); //sets player position to specific Y value
void setPlayerPositionX(Player a, int x); //sets player position to specific X value
int getPlayerWidth(); //returns player's specific width of texture
int getPlayerHeight(); //returns player's specific height of texture
int getPlayerHitpoint(int playerID); //returns player´s specific current health
void createAllPlayers(); //Create all player with their own spawnpoint
int getSpawnPointX(int a); //Decides what X value the player will spawn on
int getSpawnPointY(int a); //Decides what Y value the player will spawn on



#endif /* Player_h */