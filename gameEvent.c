#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "gameMedia.h"
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"

int lastDmgTakenTime = 0, currentDmgTakenTime = 0;
int kordLista[3];
int playerID=-1;
int up_w,down_s,left_a,right_d,lctrl;

void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if (*up_w==1){
        PlayerInit.pPosition[playerID].y -= 6;
        b.bVelY = -1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if (PlayerInit.pFrame!=9 && PlayerInit.pFrame>=10) PlayerInit.pFrame=9;
        else PlayerInit.pFrame++;
        }
        if (*down_s==1){
            PlayerInit.pPosition[playerID].y += 6;
            b.bVelY = 1;
            b.bVelX = 0;
            b.bUpDown = 90;
            if (PlayerInit.pFrame!=12 && PlayerInit.pFrame>=13) PlayerInit.pFrame=12;
            else PlayerInit.pFrame++;
        }
        if(*left_a==1){
            PlayerInit.pPosition[playerID].x -= 6;
            b.bVelX = -1;
            b.bVelY = 0;
            b.bUpDown = 0;
            PlayerInit.flip = SDL_FLIP_NONE;
            if (PlayerInit.pFrame>=8) PlayerInit.pFrame=1;
            else PlayerInit.pFrame++;
        }
        if (*right_d==1){
            PlayerInit.pPosition[playerID].x += 6;
            b.bVelX = 1;
            b.bVelY = 0;
            b.bUpDown = 0;
            PlayerInit.flip = SDL_FLIP_HORIZONTAL;
            if (PlayerInit.pFrame>=8) PlayerInit.pFrame=1;
            else PlayerInit.pFrame++;
        }
        if (event.key.keysym.sym==SDLK_w){
            *up_w=1;
        }
        if (event.key.keysym.sym==SDLK_s){
            *down_s=1;
        } 
        if(event.key.keysym.sym==SDLK_a){
            *left_a=1;
        }
        if(event.key.keysym.sym==SDLK_d){
            *right_d=1;
        }
        if(event.key.keysym.sym==SDLK_LCTRL){
            if(msTimer(&b.currentShotTime, &b.lastShotTime, 500)){  //13 rps
                b.shot = true;
                playPistolShot();
            }
    }
}

void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if(event.key.keysym.sym==SDLK_w){
        *up_w=0;
        PlayerInit.pFrame=11;
    }
    if(event.key.keysym.sym==SDLK_s){
        *down_s=0;
        PlayerInit.pFrame=14;
    }
    if(event.key.keysym.sym==SDLK_a){
        *left_a=0;
        PlayerInit.pFrame=0;
    }
    if(event.key.keysym.sym==SDLK_d){
        *right_d=0;
        PlayerInit.pFrame=0;
    }
    if(event.key.keysym.sym==SDLK_LCTRL){
        lctrl=0;
    }
}

void zombieTrackingPlayer(int i){
    if((ZombInit.zPosition[i].x - PlayerInit.pPosition->x) > 20){
        ZombInit.zPosition[i].x -= 1;
        //Frame change LEFT
        changeZFrameX(2 + zFrame[i].skin, 3 + zFrame[i].skin, i);
    }
    else if((ZombInit.zPosition[i].x - PlayerInit.pPosition->x) < -20){
        ZombInit.zPosition[i].x += 1;
        //Frame change RIGHT
        changeZFrameX(4 + zFrame[i].skin, 5 + zFrame[i].skin, i);
    }
    //Zombie following the Survivor Y
    if((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) > 20){
        ZombInit.zPosition[i].y -= 1;
        //Frame change UP
        changeZFrameY(6 + zFrame[i].skin, 7 + zFrame[i].skin, i);
    }
    else if ((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) < -20){
        ZombInit.zPosition[i].y += 1;
        //Frame change DOWN
        changeZFrameY(0 + zFrame[i].skin, 1 + zFrame[i].skin, i);
    }
}

void zombieCollisionWithZombie(int i){
    for(int j = 0; j < ZombInit.nrOfZombies; j++){
        if(j==i){
            break;
        }
        else if((ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) <= 19 && (ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) >=0){
            ZombInit.zPosition[j].x -= 1;
        }
        else if((ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) >= -19 && (ZombInit.zPosition[i].x - ZombInit.zPosition[j].x) <=0){
            ZombInit.zPosition[i].x -=1;
        }
    }
    for(int j = 0; j < ZombInit.nrOfZombies; j++){
        if(j==i){
            break;
        }
        else if((ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) <= 27 && (ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) >= 0){
            ZombInit.zPosition[j].y -= 1;
        }
        else if((ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) >= -27 && (ZombInit.zPosition[i].y - ZombInit.zPosition[j].y) <= 0){
            ZombInit.zPosition[i].y -=1;
        }
    }
}

void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime,int *lastDmgTakenTime){
    if(z[i]->alive && checkZCollisionWithP(ZombInit.zPosition[i],PlayerInit.pPosition[playerID])){
        if(msTimer(currentDmgTakenTime, lastDmgTakenTime, 1000)){
           //respawnPlayer(PlayerInit.p[playerID], &PlayerInit.pPosition[playerID], playerID);
           playZombieAttack();
           playPlayerHurt();
        }
    }
}

void zombieCollisionWithMap(int i){
    //TOP
    if(ZombInit.zPosition[i].y < 15){
        ZombInit.zPosition[i].y = 15;
    }
    //BOTTOM
    if(ZombInit.zPosition[i].y > 1224) ZombInit.zPosition[i].y = 1224;
    if(ZombInit.zPosition[i].y > 905 && (ZombInit.zPosition[i].x < 330 || ZombInit.zPosition[i].x > 455))
        ZombInit.zPosition[i].y = 905;
    else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x < 335)
        ZombInit.zPosition[i].x = 335;
    else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x > 450)
        ZombInit.zPosition[i].x = 450;
    //LEFT
    if(ZombInit.zPosition[i].x < -200) ZombInit.zPosition[i].x = -200;
    if(ZombInit.zPosition[i].x < 64 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430))
        ZombInit.zPosition[i].x = 64;
    else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y < 360)
        ZombInit.zPosition[i].y = 360;
    else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y > 425)
        ZombInit.zPosition[i].y = 425;
    //RIGHT
    if(ZombInit.zPosition[i].x > 1224) ZombInit.zPosition[i].x = 1224;
    if(ZombInit.zPosition[i].x > 930 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430))
        ZombInit.zPosition[i].x = 930;
    else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y < 360)
        ZombInit.zPosition[i].y = 360;
    else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y > 425)
        ZombInit.zPosition[i].y = 425;
}

void playerCollisionWithMap(){
    //TOP
    if(PlayerInit.pPosition[playerID].y < 15) PlayerInit.pPosition[playerID].y = 15;
    //BOTTOM
    if(PlayerInit.pPosition[playerID].y > 905) PlayerInit.pPosition[playerID].y = 905;
    //LEFT
    if(PlayerInit.pPosition[playerID].x < 30) PlayerInit.pPosition[playerID].x = 30;
    //RIGHT
    if(PlayerInit.pPosition[playerID].x > 930) PlayerInit.pPosition[playerID].x = 930;
}

void bulletPositioning(int i){
    if(!b.shot){
        b.bPosition.x = PlayerInit.pPosition[playerID].x + 25;
        b.bPosition.y = PlayerInit.pPosition[playerID].y + 20;
    }
    else{
        if(!b.bVelY){
            b.bPosition.x += b.bVelX * 10;
            bulletCollisionWithZombieX(i);
        }
        else{
            b.bPosition.y += b.bVelY * 10;
            bulletCollisionWithZombieY(i);
        }
        if(b.bPosition.x < 0 || b.bPosition.x > 1024 || b.bPosition.y < 0 || b.bPosition.y > 1024){
            b.shot = false;
        }
    }
}

void bulletCollisionWithZombieX(int i){
    //RIGHT
    if((z[i]->alive) && (b.bVelX == 1) && (b.bPosition.y >= ZombInit.zPosition[i].y) && (b.bPosition.y <= (ZombInit.zPosition[i].y + ZombInit.gZombie->h) && (PlayerInit.pPosition[playerID].x + 25 < ZombInit.zPosition[i].x))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i]);
            playZombieDie();
            b.shot = false;
        }
    }
    //LEFT
    if((z[i]->alive) && (b.bVelX == -1) && (b.bPosition.y >= ZombInit.zPosition[i].y) && (b.bPosition.y <= (ZombInit.zPosition[i].y + ZombInit.gZombie->h) && (PlayerInit.pPosition[playerID].x + 25 > ZombInit.zPosition[i].x))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i]);
            playZombieDie();
            b.shot = false;
        }
    }
}

void bulletCollisionWithZombieY(int i){
    //UP
    if((z[i]->alive) && (b.bVelY == 1) && (b.bPosition.x >= ZombInit.zPosition[i].x) && (b.bPosition.x <= (ZombInit.zPosition[i].x + ZombInit.gZombie->w) && (PlayerInit.pPosition[playerID].y + 25 < ZombInit.zPosition[i].y))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i]);
            playZombieDie();
            b.shot = false;
        }
    }
    //DOWN
    if((z[i]->alive) && (b.bVelY == -1) && (b.bPosition.x >= ZombInit.zPosition[i].x) && (b.bPosition.x <= (ZombInit.zPosition[i].x + ZombInit.gZombie->w) && (PlayerInit.pPosition[playerID].y + 25 > ZombInit.zPosition[i].y))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i]);
            playZombieDie();
            b.shot = false;
        }
    }
}

int mainGameEvent(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int close_requested = 0;
    if(playerID == -1){
        playerID = reciveID("127.0.0.1");
    }
    reciveData("127.0.0.1", kordLista);
    if(kordLista[1] != -1000){
        //printf("Satta kordinater %d %d \n", kordLista[0], kordLista[1]);
        PlayerInit.pPosition[kordLista[0]].x = kordLista[1];
        PlayerInit.pPosition[kordLista[0]].y = kordLista[2];
    }
    //receiveCoordData(&kordLista, &playerID);
    SDL_Event event;
    while (SDL_PollEvent(&event)){ 
        if (event.type== SDL_QUIT){
            close_requested = 1;
            return close_requested;
        }
        if (event.type== SDL_KEYDOWN){
            sendData(PlayerInit.pPosition[playerID].x, PlayerInit.pPosition[playerID].y, "127.0.0.1", playerID);
            pressedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);
        }
        if(event.type== SDL_KEYUP){
            releasedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);
        }
    }
    for(int i = 0; i < ZombInit.nrOfZombies; i++){
        zombieTrackingPlayer(i);
        zombieCollisionWithZombie(i);
        zombieCollisionWithPlayer(i, &currentDmgTakenTime, &lastDmgTakenTime);
        zombieCollisionWithMap(i);
        bulletPositioning(i);
    }
    playerCollisionWithMap();
    
}
