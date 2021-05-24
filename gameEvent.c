#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "gameInit.h"
#include "gameEvent.h"
#include "gameMedia.h"
#include "gameRender.h"
#include "zombie.h"
#include "player.h"
#include "gameRender.h"
#include "server/udpClient.h"

int lastDmgTakenTime = 0, currentDmgTakenTime = 0;

int kordLista[4];
int playerID=-1;
int up_w,down_s,left_a,right_d,lctrl, select=2, IPletter=0, areyouhost=2,areyoulooking=2;
char IPBuffstring[12]=" \0";
char AmountPlayersBuffstring[2]="4\0";

int checkmousestate(int *lowX,int *highX,int *lowY,int *highY){
    int MouseX, MouseY;
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_GetMouseState(&MouseX, &MouseY);
    }

    if (*lowX<MouseX && MouseX<*highX && *lowY<MouseY && MouseY<*highY){
        return 1;
    }
    //printf("MouseX: %d MouseY: %d\n ",MouseX, MouseY);
}

void setSelect(int a){
    select = a;
}

int getPlayerID(){
    return playerID;
}

void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl,SDL_Event event){
    if (event.key.keysym.sym == SDLK_w){
        *up_w = 1;
    }
    if (event.key.keysym.sym == SDLK_s){
        *down_s = 1;
    } 
    if(event.key.keysym.sym == SDLK_a){
        *left_a = 1;
    }
    if(event.key.keysym.sym == SDLK_d){
        *right_d = 1;
    }
    if(event.key.keysym.sym == SDLK_LCTRL){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 500)){  //13 rps
            b.shot = true;
            playPistolShot();
            sendData(1, 0,  0, "127.0.0.1", playerID);
        }
    }
    if(*up_w == 1){
        PlayerInit.pPosition[playerID].y -= 6;
        b.bVelY = -1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if (PlayerInit.pFrame[playerID] != 9 && PlayerInit.pFrame[playerID] >= 10) PlayerInit.pFrame[playerID] = 9;
        else PlayerInit.pFrame[playerID]++;
    }
    if(*down_s == 1){
        PlayerInit.pPosition[playerID].y += 6;
        b.bVelY = 1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if (PlayerInit.pFrame[playerID] != 12 && PlayerInit.pFrame[playerID] >= 13) PlayerInit.pFrame[playerID] = 12;
        else PlayerInit.pFrame[playerID]++;
    }
    if(*left_a == 1){
        PlayerInit.pPosition[playerID].x -= 6;
        b.bVelX = -1;
        b.bVelY = 0;
        b.bUpDown = 0;
        PlayerInit.flip[playerID] = SDL_FLIP_NONE;
        if (PlayerInit.pFrame[playerID] >= 8) PlayerInit.pFrame[playerID] = 1;
        else PlayerInit.pFrame[playerID]++;
    }
    if(*right_d == 1){
        PlayerInit.pPosition[playerID].x += 6;
        b.bVelX = 1;
        b.bVelY = 0;
        b.bUpDown = 0;
        PlayerInit.flip[playerID] = SDL_FLIP_HORIZONTAL;
        if (PlayerInit.pFrame[playerID] >= 8) PlayerInit.pFrame[playerID] = 1;
        else PlayerInit.pFrame[playerID]++;
    }
}

void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if(event.key.keysym.sym == SDLK_w){
        *up_w = 0;
        PlayerInit.pFrame[playerID] = 11;
    }
    if(event.key.keysym.sym == SDLK_s){
        *down_s = 0;
        PlayerInit.pFrame[playerID] = 14;
    }
    if(event.key.keysym.sym == SDLK_a){
        *left_a = 0;
        PlayerInit.pFrame[playerID] = 0;
    }
    if(event.key.keysym.sym == SDLK_d){
        *right_d = 0;
        PlayerInit.pFrame[playerID] = 0;
    }

    if(event.key.keysym.sym==SDLK_LCTRL){
        lctrl=0;
        PlayerInit.pFrame[playerID]=15;
    }
}

double distance(int x1, int y1, int x2, int y2){
    //Return the distance between the two points
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int closestPlayerToZombie(int zombieNr){
    int closestPlayerId = 0;
    double closestPlayerIdDistance;
    double distancePlayer;
    for (int i = 0; i < PlayerInit.nrOfPlayers; i++){
        closestPlayerIdDistance = distance(PlayerInit.pPosition[closestPlayerId].x, PlayerInit.pPosition[closestPlayerId].y, ZombInit.zPosition[zombieNr].x, ZombInit.zPosition[zombieNr].y);
        distancePlayer = distance(PlayerInit.pPosition[i].x, PlayerInit.pPosition[i].y, ZombInit.zPosition[zombieNr].x, ZombInit.zPosition[zombieNr].y);
        if(closestPlayerIdDistance > distancePlayer){
            closestPlayerId = i;
        };
    }
    return closestPlayerId;
}

void zombieTrackingPlayer(int i){
    int playerToTrack=0;
    playerToTrack = closestPlayerToZombie(i);
    if((ZombInit.zPosition[i].x - PlayerInit.pPosition[playerToTrack].x) > 20){
        ZombInit.zPosition[i].x -= 1;
        //Frame change LEFT
        changeZFrameX(2 + zFrame[i].skin, 3 + zFrame[i].skin, i);
    }
    else if((ZombInit.zPosition[i].x - PlayerInit.pPosition[playerToTrack].x) < -20){
        ZombInit.zPosition[i].x += 1;
        //Frame change RIGHT
        changeZFrameX(4 + zFrame[i].skin, 5 + zFrame[i].skin, i);
    }
    //Zombie following the Survivor Y
    if((ZombInit.zPosition[i].y - PlayerInit.pPosition[playerToTrack].y) > 20){
        ZombInit.zPosition[i].y -= 1;
        //Frame change UP
        changeZFrameY(6 + zFrame[i].skin, 7 + zFrame[i].skin, i);
    }
    else if ((ZombInit.zPosition[i].y - PlayerInit.pPosition[playerToTrack].y) < -20){
        ZombInit.zPosition[i].y += 1;
        //Frame change DOWN
        changeZFrameY(0 + zFrame[i].skin, 1 + zFrame[i].skin, i);
    }
}

void zombieCollisionWithZombie(int i){
    for(int j = 0; j < ZombInit.nrOfZombies; j++){
        if(!z[i]->alive || j == i){
            break;
        }
        else 
            if(checkZCollisionWithZ(ZombInit.zPosition[i], ZombInit.zPosition[j])){
                ZombInit.zPosition[i].x += 2;
                ZombInit.zPosition[i].y += 2;
            }
    }
}

void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime,int *lastDmgTakenTime){
    if(z[i]->alive && checkZCollisionWithP(ZombInit.zPosition[i],PlayerInit.pPosition[playerID])){
        if(msTimer(currentDmgTakenTime, lastDmgTakenTime, 1000)){
            playZombieAttack();
            playPlayerHurt();
            //hurtPlayer(PlayerInit.hitPoint[playerID]);
            if(--PlayerInit.hitPoint[playerID] == 0){
                PlayerInit.hitPoint[playerID] = 3;
                setStartRender(2);
                setSelect(2);
                GIO.gameOver = true;
           }
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
            killZombie(z[i], i, playerID);
            playZombieDie();
            b.shot = false;
        }
    }
    //LEFT
    if((z[i]->alive) && (b.bVelX == -1) && (b.bPosition.y >= ZombInit.zPosition[i].y) && (b.bPosition.y <= (ZombInit.zPosition[i].y + ZombInit.gZombie->h) && (PlayerInit.pPosition[playerID].x + 25 > ZombInit.zPosition[i].x))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i], i, playerID);
            playZombieDie();
            b.shot = false;
        }
    }
}

void bulletCollisionWithZombieY(int i){
    //UP
    if((z[i]->alive) && (b.bVelY == 1) && (b.bPosition.x >= ZombInit.zPosition[i].x) && (b.bPosition.x <= (ZombInit.zPosition[i].x + ZombInit.gZombie->w) && (PlayerInit.pPosition[playerID].y + 25 < ZombInit.zPosition[i].y))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i], i, playerID);
            playZombieDie();
            b.shot = false;
        }
    }
    //DOWN
    if((z[i]->alive) && (b.bVelY == -1) && (b.bPosition.x >= ZombInit.zPosition[i].x) && (b.bPosition.x <= (ZombInit.zPosition[i].x + ZombInit.gZombie->w) && (PlayerInit.pPosition[playerID].y + 25 > ZombInit.zPosition[i].y))){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 50)){
            killZombie(z[i], i, playerID);
            playZombieDie();
            b.shot = false;
        }
    }
}

int mainGameEvent(){
    int LetterforIP;
    if (LetterforIP>12){LetterforIP=0;}
    char bufIPaddress[12];
    char bufAmountPlayers[2]="4";
    areyouhost=CheckIfHost();
    areyoulooking=CheckIfLooking();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int close_requested = 0;
    if(playerID == -1){
        playerID = reciveID("127.0.0.1");
    }
    if (select!=1){
        select=checkIfGamestarted();
        Mix_HaltMusic();
    }
    reciveData("127.0.0.1", kordLista);
    if(kordLista[3] == 0){
        //printf("Satta kordinater %d %d \n", kordLista[0], kordLista[1]);
        if((PlayerInit.pPosition[kordLista[0]].x) < (kordLista[1])){
            PlayerInit.pFrame[kordLista[0]] = 0;
            PlayerInit.flip[kordLista[0]] = SDL_FLIP_HORIZONTAL;
        }
        else if((PlayerInit.pPosition[kordLista[0]].x) > (kordLista[1])){
            PlayerInit.pFrame[kordLista[0]]=0;
            PlayerInit.flip[kordLista[0]] = SDL_FLIP_NONE;
        }
        else if((PlayerInit.pPosition[kordLista[0]].y) < (kordLista[2])){
            PlayerInit.pFrame[kordLista[0]]=14;
        }
        else if((PlayerInit.pPosition[kordLista[0]].y) > (kordLista[2])){
            PlayerInit.pFrame[kordLista[0]]=11;
        }
        PlayerInit.pPosition[kordLista[0]].x = kordLista[1];
        PlayerInit.pPosition[kordLista[0]].y = kordLista[2];

    }else if(kordLista[3]==1){
        PlayerInit.pFrame[kordLista[0]]=15;
    }
    else if(kordLista[3]==2){
        z[kordLista[1]]->alive = 0;
    }
    //receiveCoordData(&kordLista, &playerID);
    SDL_Event event;
    while(SDL_PollEvent(&event)){ 
        if(event.type == SDL_QUIT){
            close_requested = 1;
            return close_requested;
            } 
            playBgGameMusic();
            if(event.type == SDL_KEYDOWN){
                sendData(0, PlayerInit.pPosition[playerID].x, PlayerInit.pPosition[playerID].y, "127.0.0.1", playerID);
                if (select == 1){pressedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);}
                MenuKeyboard(event, bufIPaddress, bufAmountPlayers, &LetterforIP);
            }
            if(event.type == SDL_KEYUP){
                releasedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);
            }
    }
    if (select == 1){
        respawnZombie();
        startGameTimer();
        playZombieBrain();
        for(int i = 0; i < ZombInit.nrOfZombies; i++){
            zombieTrackingPlayer(i);
            zombieCollisionWithZombie(i);
            zombieCollisionWithPlayer(i, &currentDmgTakenTime, &lastDmgTakenTime);
            zombieCollisionWithMap(i);
            bulletPositioning(i);
        }
        playerCollisionWithMap();
    }
}

int MenuKeyboard(SDL_Event event,char buf[],char buf2[], int *LetterforIP){

    if (event.key.keysym.sym==SDLK_0)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='0';
        }
    }
    if (event.key.keysym.sym==SDLK_1)
    {
        if (areyoulooking==1 && select!=1){
        buf[*LetterforIP]='1'; 
        }
        if (areyouhost==1 && select!=1)
        {
            buf2[0]='1';
            PlayerInit.nrOfPlayers = 1;
        }
    }
    if (event.key.keysym.sym==SDLK_2)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='2';
        }
        if (areyouhost==1 && select!=1){
            buf2[0]='2';
            PlayerInit.nrOfPlayers = 2;
        }
    }
    if (event.key.keysym.sym==SDLK_3)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='3';
        }
        if (areyouhost==1 && select!=1){
            buf2[0]='3';
            PlayerInit.nrOfPlayers = 3;
        }
    }
    if (event.key.keysym.sym==SDLK_4)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='4';
        }
        if (areyouhost==1 && select!=1){
            buf2[0]='4';
            PlayerInit.nrOfPlayers = 4;
        }
    }
    if (event.key.keysym.sym==SDLK_5)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='5';
        }    
    }
    if (event.key.keysym.sym==SDLK_6)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='6';
        }
    }
    if (event.key.keysym.sym==SDLK_7)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='7';
        }
    }
    if (event.key.keysym.sym==SDLK_8)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='8';
        }
    }
    if (event.key.keysym.sym==SDLK_9)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='9';
        }
    }
    if (event.key.keysym.sym==SDLK_PERIOD)
    {
        if (areyoulooking==1 && select!=1){
            buf[*LetterforIP]='.';
        }
    }

    strcpy(AmountPlayersBuffstring,buf2);    
    if (areyoulooking==1){
        (*LetterforIP)++;
        buf[*LetterforIP]='\0';
        strcpy(IPBuffstring,buf);
    }
}

void GetIPaddress( char* strOut, unsigned int strSize )
{
   strncpy( strOut, IPBuffstring, strSize );
}

void GetAmountPlayers( char* strOut, unsigned int strSize )
{
    strncpy( strOut, AmountPlayersBuffstring, strSize );
}