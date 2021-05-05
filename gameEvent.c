#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "map.h"
#include "zombie.h"
#include "player.h"
#include "server/udpClient.h"

/*void receiveCoordData(int *kordLista[], int *playerID){
    if(*playerID == -1){
        *playerID = reciveID("192.168.56.1");
    }
    reciveData("192.168.56.1", *kordLista);
    if(*kordLista[0] != -1000){
        //printf("Satta kordinater %d %d \n", kordLista[0], kordLista[1]);
        PlayerInit.pPosition[1].x = *kordLista[0];
        PlayerInit.pPosition[1].y = *kordLista[1];
    }
}*/

void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if (*up_w==1){
        PlayerInit.pPosition->y -= 6;
        b.bVelY = -1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if (PlayerInit.pFrame!=9 && PlayerInit.pFrame>=10) PlayerInit.pFrame=9;
        else PlayerInit.pFrame++;
        }
        if (*down_s==1) {
            PlayerInit.pPosition->y += 6;
            b.bVelY = 1;
            b.bVelX = 0;
            b.bUpDown = 90;
            if (PlayerInit.pFrame!=12 && PlayerInit.pFrame>=13) PlayerInit.pFrame=12;
            else PlayerInit.pFrame++;
        }
        if(*left_a==1){ 
            PlayerInit.pPosition->x -= 6;
            b.bVelX = -1;
            b.bVelY = 0;
            b.bUpDown = 0;
            PlayerInit.flip = SDL_FLIP_NONE;
            if (PlayerInit.pFrame>=8) PlayerInit.pFrame=1;
            else PlayerInit.pFrame++;
        }
        if (*right_d==1){
            PlayerInit.pPosition->x += 6;
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
            if(msTimer(&b.currentShotTime, &b.lastShotTime, 500))  //13 rps
                b.shot = true;
    }
}

void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if(event.key.keysym.sym==SDLK_w){
        up_w=0;
        PlayerInit.pFrame=11;
    }
    if(event.key.keysym.sym==SDLK_s){
        down_s=0;
        PlayerInit.pFrame=14;
    }
    if(event.key.keysym.sym==SDLK_a){
        left_a=0;
        PlayerInit.pFrame=0;
    }
    if(event.key.keysym.sym==SDLK_d){
        right_d=0;
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
        changeZFrameX(&zFrame[i].frame, 2, 3, &zFrame[i].counter, &zFrame[i].diagonal);
    }
    else if((ZombInit.zPosition[i].x - PlayerInit.pPosition->x) < -20){
        ZombInit.zPosition[i].x += 1;
        //Frame change RIGHT
        changeZFrameX(&zFrame[i].frame, 4, 5, &zFrame[i].counter, &zFrame[i].diagonal);
    }
    //Zombie following the Survivor Y
    if((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) > 20){
        ZombInit.zPosition[i].y -= 1;
        //Frame change UP
        changeZFrameY(&zFrame[i].frame, 6, 7, &zFrame[i].counter, &zFrame[i].diagonal);
    }
    else if ((ZombInit.zPosition[i].y - PlayerInit.pPosition->y) < -20){
        ZombInit.zPosition[i].y += 1;
        //Frame change DOWN
        changeZFrameY(&zFrame[i].frame, 0, 1, &zFrame[i].counter, &zFrame[i].diagonal);
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
    if(checkZCollisionWithP(ZombInit.zPosition[i],PlayerInit.pPosition[0])){
        if(msTimer(&currentDmgTakenTime, &lastDmgTakenTime, 1000)){
            respawnPlayer(PlayerInit.p[0], &PlayerInit.pPosition[0]);
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
    if(PlayerInit.pPosition[0].y < 15) PlayerInit.pPosition[0].y = 15;
    //BOTTOM
    if(PlayerInit.pPosition[0].y > 905) PlayerInit.pPosition[0].y = 905;
    //LEFT
    if(PlayerInit.pPosition[0].x < 30) PlayerInit.pPosition[0].x = 30;
    //RIGHT
    if(PlayerInit.pPosition[0].x > 930) PlayerInit.pPosition[0].x = 930;
}

void bulletPositioning(){
    if(!b.shot){
        b.bPosition.x = PlayerInit.pPosition[0].x + 20;
        b.bPosition.y = PlayerInit.pPosition[0].y + 17;
    }
    else{
        if(!b.bVelY) b.bPosition.x += b.bVelX * 75;
        else b.bPosition.y += b.bVelY * 75;
        if(b.bPosition.x < 0 || b.bPosition.x > 1024 || b.bPosition.y < 0 || b.bPosition.y > 1024){
            b.shot = false;
        }
    }
}

int mainGameEvent(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int lastDmgTakenTime = 0, currentDmgTakenTime = 0;
    int kordLista[2];
    int playerID=-1;
    int up_w,down_s,left_a,right_d,lctrl;
    int close_requested = 0;
    while (!close_requested){
        if(playerID == -1){
            playerID = reciveID("192.168.56.1");
        }
        reciveData("192.168.56.1", kordLista);
        if(kordLista[0] != -1000){
            //printf("Satta kordinater %d %d \n", kordLista[0], kordLista[1]);
            PlayerInit.pPosition[1].x = kordLista[0];
            PlayerInit.pPosition[1].y = kordLista[1];
        }
        //receiveCoordData(&kordLista, &playerID);
        SDL_Event event;
        while (SDL_PollEvent(&event)){ 
            if (event.type== SDL_QUIT){
                close_requested = 1;
                return 1;
            }
            if (event.type== SDL_KEYDOWN){
                sendData(PlayerInit.pPosition->x, PlayerInit.pPosition->y, "192.168.56.1", playerID);
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
        }
        playerCollisionWithMap();
        bulletPositioning();
    }
}