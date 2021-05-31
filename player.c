#include <stdlib.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "gameEvent.h"
#include "gameRender.h"

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
    return p;
}
//sets player position to specific Y value
PUBLIC void setPlayerPositionY(Player a, int y){
    a->PLAYER_POSITION_Y = y;
}
//sets player position to specific X value
PUBLIC void setPlayerPositionX(Player a, int x){
    a->PLAYER_POSITION_X = x;
}

//returns player's specific X position
PUBLIC int getPlayerPositionX(Player a){
    return a->PLAYER_POSITION_X;
}

//returns player's specific Y position
PUBLIC int getPlayerPositionY(Player a){
    return a->PLAYER_POSITION_Y;
}
//returns player's specific width of texture
PUBLIC int getPlayerWidth(){
    return PLAYER_WIDTH;
}
//returns player's specific height of texture
PUBLIC int getPlayerHeight(){
    return PLAYER_HEIGTH;
}

PUBLIC int getPlayerHitpoint(int PlayerID){ //returns player´s specific current health
    return PlayerInit.hitPoint[PlayerID];
}

PUBLIC void createAllPlayers(){ //Create all player with their own spawnpoint
    for(int i = 0; i < PlayerInit.nrOfPlayers; i++){
        PlayerInit.p[i] = createPlayer(getSpawnPointX(i), getSpawnPointY(i));
        PlayerInit.pPosition[i].x = getPlayerPositionX(PlayerInit.p[i]);
        PlayerInit.pPosition[i].y = getPlayerPositionY(PlayerInit.p[i]);
        PlayerInit.pPosition[i].w = 64;
        PlayerInit.pPosition[i].h = 64;
        PlayerInit.hitPoint[i] = 3;
        PlayerInit.alive[i] = true;
    }
}

PUBLIC int getSpawnPointX(int a){ //Decides what X value the player will spawn on
    if(a == 0)
        return zSpawnPointX0;
    else if(a == 1)
        return zSpawnPointX1;
    else if(a == 2)
        return zSpawnPointX2;
    else if(a == 3)
        return zSpawnPointX3;
}

PUBLIC int getSpawnPointY(int a){ //Decides what Y value the player will spawn on
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