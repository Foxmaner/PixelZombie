  
#ifndef player_h
#define player_h

#include <stdio.h>
#include <SDL2/SDL.h>

struct player_type{
    int PLAYER_POSITION_X;
    int PLAYER_POSITION_Y;
    int hitPoint;
};typedef struct player_type *Player;

int getPlayerPositionX(Player a);
int getPlayerPositionY(Player a);
Player createPlayer(int x, int y);
void setPlayerPositionY(Player a, int y);
void setPlayerPositionX(Player a, int x);
int getPlayerWidth();
int getPlayerHeight();
int getPlayerHitpoint(Player a);
int getSpawnPointX(int a);
int getSpawnPointY(int a);
void respawnPlayer(Player a, SDL_Rect pPostion[]);


#endif /* Player_h */
