  
#ifndef player_h
#define player_h

#include <stdio.h>

typedef struct player_type *Player;

int getPlayerPositionX(Player a);
int getPlayerPositionY(Player a);
Player createPlayer(int x, int y);
void setPlayerPositionY(Player a, int y);
void setY(Player a, int y);
int getPlayerWidth();
int getPlayerHeight();
int getPlayerFrame(Player a);
int getSpawnPointX(int a);
int getSpawnPointY(int a);

#endif /* Player_h */