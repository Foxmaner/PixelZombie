#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "zombie.h"
#include "gameInit.h"
#include "server/udpClient.h"

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ZOMBIE_WIDTH = 54;
PRIVATE int ZOMBIE_HEIGTH = 54;

//Spawnpoints
//LEFT
PRIVATE int zSpawnPointX0 = -200;
PRIVATE int zSpawnPointY0 = 360;
//BOTTOM
PRIVATE int zSpawnPointX1 = 335;
PRIVATE int zSpawnPointY1 = 1224;
//RIGHT
PRIVATE int zSpawnPointX2 = 1224;
PRIVATE int zSpawnPointY2 = 360;

/* int currentLevel=1;

int getCurrentLevel(){
    return currentLevel;
}
*/
PUBLIC Zombie createZombie(int x, int y){  //Allocate memory to create a zombie, must make free when done.
    Zombie z = malloc(sizeof(struct zombie_type));
    z->ZOMBIE_POSITION_Y = y;
    z->ZOMBIE_POSITION_X = x;
    z->hitPoint = 1;
    z->alive = 1;
    return z;
}

PUBLIC void setZombiePositionY(Zombie a, int y){ 
    a->ZOMBIE_POSITION_Y = y;
}

PUBLIC int getZombiePositionX(Zombie a){
    return a->ZOMBIE_POSITION_X;
}


PUBLIC int getZombiePositionY(Zombie a){
    return a->ZOMBIE_POSITION_Y;
}

PUBLIC int getZombieWidth(){
    return ZOMBIE_WIDTH;
}

PUBLIC int getZombieHeight(){
    return ZOMBIE_HEIGTH;
}

PUBLIC int getZombieHitPoint(Zombie a){
    return a->hitPoint;
}

//Gives and spawn zombies at "random" spawnpoint and give random skin
PUBLIC void createAllZombies(){
    //createTextbox(iSDL.renderer,x,y,"1",size);
    for(int i = 0; i < ZombInit.nrOfZombies; i++){
        z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
        ZombInit.zPosition[i].x = getZombiePositionX(z[i]);
        ZombInit.zPosition[i].y = getZombiePositionY(z[i]);
        ZombInit.zPosition[i].w = 43;
        ZombInit.zPosition[i].h = 54;
        zFrame[i].skin = ((rand() % 4 + 1) * 8) - 8;
    }
}

PUBLIC int getZSpawnPointX(int a){
    if(a == 0)
        return zSpawnPointX0 + (rand() % 200);
    else if(a == 1)
        return zSpawnPointX1 + (rand() % 115);
    else if(a == 2)
        return zSpawnPointX2 - (rand() % 200);
}

PUBLIC int getZSpawnPointY(int a){
    if(a == 0)
        return zSpawnPointY0 + (rand() % 65);
    else if(a == 1)
        return zSpawnPointY1 - (rand() % 200);
    else if(a == 2)
        return zSpawnPointY2 + (rand() % 65);
}

PUBLIC void changeZFrameX(int frameA, int frameB, int i){ //Changes the zombie frame making it appear like its walking
    zFrame[i].diagonal = 0;
    if(zFrame[i].frame == frameA && zFrame[i].counter >= 25){
        zFrame[i].frame = frameB;
        zFrame[i].counter = 0;
    }
    else if(zFrame[i].frame == frameB){
        if(zFrame[i].counter >= 25){
            zFrame[i].frame = frameA;
            zFrame[i].counter = 0;
        }
        else (zFrame[i].counter)++;
    }
    else{
        zFrame[i].frame = frameA;
        (zFrame[i].counter)++;
    }
}

PUBLIC void changeZFrameY(int frameA, int frameB, int i){ //Changes the zombie frame making it appear like its walking
    if((zFrame[i].diagonal)++ > 0){
        if(zFrame[i].frame == frameA && zFrame[i].counter >= 25){
            zFrame[i].frame = frameB;
            zFrame[i].counter = 0;
        }
        else if(zFrame[i].frame == frameB){
            if(zFrame[i].counter >= 25){
                zFrame[i].frame = frameA;
                zFrame[i].counter = 0;
            }
            else (zFrame[i].counter)++;
        }
        else{
            zFrame[i].frame = frameA;
            (zFrame[i].counter)++;
        }
    }
}

PUBLIC bool checkZCollisionWithZ(SDL_Rect zombie1, SDL_Rect zombie2){
    int z1Left, z1Right, z1Top, z1Bottom;
    int z2Left, z2Right, z2Top, z2Bottom;

    //Calculate zombie1 hitbox
    z1Left = zombie1.x + 10;
    z1Right = zombie1.x + zombie1.w - 10;
    z1Top = zombie1.y  + 10;
    z1Bottom = zombie1.y + zombie1.h - 10;

    //Calculate zombie2 hitbox
    z2Left = zombie2.x + 10;
    z2Right = zombie2.x + zombie2.w - 10;
    z2Top = zombie2.y + 10;
    z2Bottom = zombie2.y + zombie2.h - 10;

    //Check if sides collide with eachother
    if(z1Top > z2Bottom) return false;
    if(z1Bottom < z2Top) return false;
    if(z1Left > z2Right) return false;
    if(z1Right < z2Left) return false;
    //if sides are not outside eachother(aka collision), then return true
    return true;
}

PUBLIC bool checkZCollisionWithP(SDL_Rect zombie, SDL_Rect player){
    int zLeft, zRight, zTop, zBottom;
    int plLeft, plRight, plTop, plBottom;
    
    //Calculate zombie hitbox
    zLeft = zombie.x;
    zRight = zombie.x + zombie.w;
    zTop = zombie.y;
    zBottom = zombie.y + zombie.h;

    //Calculate player hitbox
    plLeft = player.x;
    plRight = player.x + player.w;
    plTop = player.y;
    plBottom = player.y + player.h;
    
    //Check if sides collide with eachother
    if(zTop > plBottom) return false;
    if(zBottom < plTop) return false;
    if(zLeft > plRight) return false;
    if(zRight < plLeft) return false;
    //if sides are not outside eachother(aka collision), then return true
    return true;
}

PUBLIC void killZombie(Zombie a, int i, int playerID){
    sendData(2, i, 0, "127.0.0.1", playerID);
    a->alive = 0;
}

PUBLIC void respawnZombie(){
    int alive=0;   // All zombies dead?
    //char txt[4]="";
    int newZombieId=0;
    for(int a = 0; a < ZombInit.nrOfZombies; a++){
        if(z[a]->alive) alive++;
    }

    if(!alive){  //if all zombies are dead, create a "new" wave of zombies.
        for(int a = 0; a < ZombInit.nrOfZombies; a++){
            z[a]->alive = 1;
            ZombInit.zPosition[a].x = getZSpawnPointX(a % 3);
            ZombInit.zPosition[a].y = getZSpawnPointY(a % 3);
        }
        
        newZombieId = ZombInit.nrOfZombies;
        printf("%d\n",newZombieId);
        ZombInit.nrOfZombies+=2;
        printf("nr# %d\n",ZombInit.nrOfZombies);
        //currentLevel++; sprintf(txt,"%d",currentLevel);
        //createTextbox(iSDL.renderer,40,40,txt,20);                                                        //FIX
        for(int i = newZombieId; i < newZombieId+2; i++){ //Create 2 more zombies each wave
            z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
            ZombInit.zPosition[i].x = getZombiePositionX(z[i]);
            ZombInit.zPosition[i].y = getZombiePositionY(z[i]);
            ZombInit.zPosition[i].w = 43;
            ZombInit.zPosition[i].h = 54;
            zFrame[i].skin = ((rand() % 4 + 1) * 8) - 8;
        }
    }
}

PUBLIC int msTimer(int *pCurrentTime, int *pLastRecordedTime, int ms){ //Wait x ms.
    *pCurrentTime = SDL_GetTicks();
    if(*pCurrentTime >= *pLastRecordedTime + ms){
        *pLastRecordedTime = *pCurrentTime;
        return 1;
    }
    else return 0;
}