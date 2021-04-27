#include <stdlib.h>
#include "player.h"


#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int PLAYER_WIDTH = 54;
PRIVATE int PLAYER_HEIGTH = 54;

PRIVATE int zSpawnPointX0 = 500;
PRIVATE int zSpawnPointY0 = 500;
PRIVATE int zSpawnPointX1 = 1040;
PRIVATE int zSpawnPointY1 = 400;

struct player_type{
    int PLAYER_POSITION_X;
    int PLAYER_POSITION_Y;
    int PLAYER_FRAME;
    int slow;
    int hitPoint;
};

PUBLIC Player createPlayer(int x, int y){
    Player z = malloc(sizeof(struct player_type));
    z->PLAYER_POSITION_Y = y;
    z->PLAYER_POSITION_X = x;
    z->PLAYER_FRAME = 0;
    z->slow = 1;
    z->hitPoint = 3;
    return z;
}


PUBLIC void setPlayerPositionY(Player a, int y){
    a->PLAYER_POSITION_Y = y;
}

PUBLIC void setPlayerPositionX(Player a, int x){
    a->PLAYER_POSITION_X = x;
}


PUBLIC int getPlayerPositionX(Player a){
    return a->PLAYER_POSITION_X;
}


PUBLIC int getPlayerPositionY(Player a){
    return a->PLAYER_POSITION_Y;
}

PUBLIC int getPlayerWidth(){
    return PLAYER_WIDTH;
}

PUBLIC int getPlayerHeight(){
    return PLAYER_HEIGTH;
}

PUBLIC int getPlayerFrame(Player a){
    return a->PLAYER_FRAME;
}

PUBLIC int getSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0;
    else if(a == 1)
        return zSpawnPointX1;
}

PUBLIC int getSpawnPointY(int a){
    if(a == 0)
        return zSpawnPointY0;
    else if(a == 1)
        return zSpawnPointY1;
}

PUBLIC void respawnPlayer(Player a){
    if (!--a->hitPoint){
        a->hitPoint=3;
        a->PLAYER_POSITION_X=512;
        a->PLAYER_POSITION_Y=512;
    }
}