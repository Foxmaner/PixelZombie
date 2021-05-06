#include <stdlib.h>
#include <SDL2/SDL.h>

#include "player.h"

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int PLAYER_WIDTH = 54;
PRIVATE int PLAYER_HEIGTH = 54;

PRIVATE int zSpawnPointX0 = 500;
PRIVATE int zSpawnPointY0 = 500;
PRIVATE int zSpawnPointX1 = 600;
PRIVATE int zSpawnPointY1 = 600;
PRIVATE int zSpawnPointX2 = 700;
PRIVATE int zSpawnPointY2 = 700;
PRIVATE int zSpawnPointX3 = 800;
PRIVATE int zSpawnPointY3 = 800;

PUBLIC Player createPlayer(int x, int y){
    Player p = malloc(sizeof(struct player_type));
    p->PLAYER_POSITION_Y = y;
    p->PLAYER_POSITION_X = x;
    p->hitPoint = 3;
    return p;
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

PUBLIC int getPlayerHitpoint(Player a){
    return a->hitPoint;
}

PUBLIC void createAllPlayers(){
    for(int i = 0; i <PlayerInit.nrOfPlayers; i++){
        PlayerInit.p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        PlayerInit.pPosition[i].x = getPlayerPositionX(PlayerInit.p[i]);
        PlayerInit.pPosition[i].y = getPlayerPositionY(PlayerInit.p[i]);
        PlayerInit.pPosition[i].w = 64;
        PlayerInit.pPosition[i].h = 64;
    }
}

PUBLIC int getSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0;
    else if(a == 1)
        return zSpawnPointX1;
}

PUBLIC int getSpawnPointY(int a){
    if(a == 0){
        return zSpawnPointY0;
    }
    else if (a == 1){
        return zSpawnPointY1;
    }
    else if(a==2){
        return zSpawnPointY2;
    }
    else if(a==3){
        return zSpawnPointY3;
    }
}

PUBLIC void respawnPlayer(Player a, SDL_Rect pPostion[]){
    if (!--a->hitPoint){
        a->hitPoint=3;
        pPostion->x=512;
        pPostion->y=512;
    }
}