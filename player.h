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

int getPlayerPositionX(Player a);
int getPlayerPositionY(Player a);
Player createPlayer(int x, int y);
void setPlayerPositionY(Player a, int y);
void setPlayerPositionX(Player a, int x);
int getPlayerWidth();
int getPlayerHeight();
int getPlayerHitpoint(int playerID);
void createAllPlayers();
int getSpawnPointX(int a);
int getSpawnPointY(int a);
void hurtPlayer(int *a);


#endif /* Player_h */