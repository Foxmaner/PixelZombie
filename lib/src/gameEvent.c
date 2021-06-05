#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../include/gameInit.h"
#include "../include/gameEvent.h"
#include "../include/gameMedia.h"
#include "../include/gameRender.h"
#include "../include/zombie.h"
#include "../include/player.h"
#include "../include/gameRender.h"
#include "../../server/udpClient.h"

//Helps track time so players only take damage once per second
int lastDmgTakenTime = 0, currentDmgTakenTime = 0;
int playerID = -1;
int kordLista[4];
int up_w, down_s, left_a, right_d, lctrl, select = 2, IPletter = 0, areyouhost = 2, Lookingforgame = 2;
char IPBuffstring[12] = " \0";
char AmountPlayersBuffstring[2] = "4\0";

//Check if person running the game has clicked within a certain area
int checkmousestate(int *lowX,int *highX,int *lowY,int *highY){
    int MouseX, MouseY;
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
        SDL_GetMouseState(&MouseX, &MouseY);
    }

    if (*lowX < MouseX && MouseX < *highX && *lowY < MouseY && MouseY < *highY){
        return 1;
    }
    else{
        return 0;
    }
}

//Sets select in order to make game over
void setSelect(int a){
    select = a;
}

int getPlayerID(){
    return playerID;
}

void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event){
    if(event.key.keysym.sym == SDLK_w){
        *up_w = 1;
    }
    if(event.key.keysym.sym == SDLK_s){
        *down_s = 1;
    } 
    if(event.key.keysym.sym == SDLK_a){
        *left_a = 1;
    }
    if(event.key.keysym.sym == SDLK_d){
        *right_d = 1;
    }
    if(event.key.keysym.sym == SDLK_LCTRL){
        if(msTimer(&b.currentShotTime, &b.lastShotTime, 500)){  //Regulates the fire speed
            b.shot = true;
            playPistolShot();
            if(PlayerInit.pFrame[playerID] >= 0 && PlayerInit.pFrame[playerID] <= 8){
                PlayerInit.pFrame[playerID] = 15;
            }
            sendData(1, 0,  0, "127.0.0.1", playerID);
        }
    }
    if(*up_w == 1){
        PlayerInit.pPosition[playerID].y -= 6;
        b.bVelY = -1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if(PlayerInit.pFrame[playerID] != 9 && PlayerInit.pFrame[playerID] >= 10){
            PlayerInit.pFrame[playerID] = 9;
        }
        else{
            PlayerInit.pFrame[playerID]++;
        }
    }
    if(*down_s == 1){
        PlayerInit.pPosition[playerID].y += 6;
        b.bVelY = 1;
        b.bVelX = 0;
        b.bUpDown = 90;
        if(PlayerInit.pFrame[playerID] != 12 && PlayerInit.pFrame[playerID] >= 13){
            PlayerInit.pFrame[playerID] = 12;
        }
        else{
            PlayerInit.pFrame[playerID]++;
        }
    }
    if(*left_a == 1){
        PlayerInit.pPosition[playerID].x -= 6;
        b.bVelX = -1;
        b.bVelY = 0;
        b.bUpDown = 0;
        PlayerInit.flip[playerID] = SDL_FLIP_NONE;
        if(PlayerInit.pFrame[playerID] >= 8){
            PlayerInit.pFrame[playerID] = 1;
        }
        else{
            PlayerInit.pFrame[playerID]++;
        }
    }
    if(*right_d == 1){
        PlayerInit.pPosition[playerID].x += 6;
        b.bVelX = 1;
        b.bVelY = 0;
        b.bUpDown = 0;
        PlayerInit.flip[playerID] = SDL_FLIP_HORIZONTAL;
        if(PlayerInit.pFrame[playerID] >= 8){
            PlayerInit.pFrame[playerID] = 1;
        }
        else{
            PlayerInit.pFrame[playerID]++;
        }
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
        if(PlayerInit.pFrame[playerID] == 15) PlayerInit.pFrame[playerID]=0;
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
        if(PlayerInit.alive[i]){
            closestPlayerIdDistance = distance(PlayerInit.pPosition[closestPlayerId].x, PlayerInit.pPosition[closestPlayerId].y, ZombInit.zPosition[zombieNr].x, ZombInit.zPosition[zombieNr].y);
            distancePlayer = distance(PlayerInit.pPosition[i].x, PlayerInit.pPosition[i].y, ZombInit.zPosition[zombieNr].x, ZombInit.zPosition[zombieNr].y);
            if(closestPlayerIdDistance > distancePlayer){
                closestPlayerId = i;
            };
        }
    }
    return closestPlayerId;
}

//Zombies walk towards nearest player and changes frames (animation)
void zombieTrackingPlayer(int i){
    int playerToTrack = 0;
    playerToTrack = closestPlayerToZombie(i);
    if(!PlayerInit.alive[playerToTrack]){                   //This solved zombies only following one specific player...
        for(int j = 0; j < PlayerInit.nrOfPlayers; j++){    //...the rootproblem may be that clients start at different...
            if(PlayerInit.alive[j]) playerToTrack = j;      //...times. Until that is fixed, this solution will do.
        }                                                   //
    }                                                       //              ONLY WORKS FOR TWO PLAYERS!!!

    //Zombie following the Survivor X
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

//Checks all alive zombies if they run into eachother...
//...and adjust their position if they do.
void zombieCollisionWithZombie(int i){
    for(int j = 0; j < ZombInit.nrOfZombies; j++){
        if(!z[i]->alive || j == i){
            break;
        }
        else{
            if(checkZCollisionWithZ(ZombInit.zPosition[i], ZombInit.zPosition[j])){
                ZombInit.zPosition[i].x += 2;
                ZombInit.zPosition[i].y += 2;
            }
        }
    }
}

//Restarts game if all players are dead
void isGameOver(){
    int playersDead = 0;
    for(int i = 0; i < PlayerInit.nrOfPlayers; i++){
        if(!PlayerInit.alive[i]){
            playersDead++;
            if(playersDead == PlayerInit.nrOfPlayers){
                setStartRender(2);
                setSelect(2);
                GIO.gameOver = true;
            }
        }
    }
}

//Checks if alive zombie collide with alive players...
//...and removes player hitpoints if they do
void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime, int *lastDmgTakenTime){
    if(z[i]->alive && PlayerInit.alive[playerID] && checkZCollisionWithP(ZombInit.zPosition[i], PlayerInit.pPosition[playerID])){
        if(msTimer(currentDmgTakenTime, lastDmgTakenTime, 1000)){
            playZombieAttack();
            playPlayerHurt();
            PlayerInit.hitPoint[playerID]--;
            if(PlayerInit.hitPoint[playerID] == 0){
                PlayerInit.alive[playerID] = false;
            }
            sendData( 4, PlayerInit.alive[playerID], 0, "127.0.0.1", playerID);
        }
    }
}

//Checks if zombies collide with map boundries...
//...and adjust thier position accordingly.
void zombieCollisionWithMap(int i){
    //TOP
    if(ZombInit.zPosition[i].y < 15){
        ZombInit.zPosition[i].y = 15;
    }
    //BOTTOM with "Room" outside of map where zombies may spawn
    if(ZombInit.zPosition[i].y > 1224){
        ZombInit.zPosition[i].y = 1224;
    }
    if(ZombInit.zPosition[i].y > 905 && (ZombInit.zPosition[i].x < 330 || ZombInit.zPosition[i].x > 455)){
        ZombInit.zPosition[i].y = 905;
    }
    else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x < 335){
        ZombInit.zPosition[i].x = 335;
    }
    else if(ZombInit.zPosition[i].y > 905 && ZombInit.zPosition[i].x > 450){
        ZombInit.zPosition[i].x = 450;
    }
    //LEFT with "Room" outside of map where zombies may spawn
    if(ZombInit.zPosition[i].x < -200){
        ZombInit.zPosition[i].x = -200;
    }
    if(ZombInit.zPosition[i].x < 64 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430)){
        ZombInit.zPosition[i].x = 64;
    }
    else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y < 360){
        ZombInit.zPosition[i].y = 360;
    }
    else if(ZombInit.zPosition[i].x < 64 && ZombInit.zPosition[i].y > 425){
        ZombInit.zPosition[i].y = 425;
    }
    //RIGHT with "Room" outside of map where zombies may spawn
    if(ZombInit.zPosition[i].x > 1224){
        ZombInit.zPosition[i].x = 1224;
    }
    if(ZombInit.zPosition[i].x > 930 && (ZombInit.zPosition[i].y < 355 || ZombInit.zPosition[i].y > 430)){
        ZombInit.zPosition[i].x = 930;
    }
    else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y < 360){
        ZombInit.zPosition[i].y = 360;
    }
    else if(ZombInit.zPosition[i].x > 930 && ZombInit.zPosition[i].y > 425){
        ZombInit.zPosition[i].y = 425;
    }
}

//Checks if players collide with map boundries...
//...and adjust thier position accordingly.
void playerCollisionWithMap(){
    //TOP
    if(PlayerInit.pPosition[playerID].y < 15){
        PlayerInit.pPosition[playerID].y = 15;
    }
    //BOTTOM
    if(PlayerInit.pPosition[playerID].y > 905){
        PlayerInit.pPosition[playerID].y = 905;
    }
    //LEFT
    if(PlayerInit.pPosition[playerID].x < 30){
        PlayerInit.pPosition[playerID].x = 30;
    }
    //RIGHT
    if(PlayerInit.pPosition[playerID].x > 930){
        PlayerInit.pPosition[playerID].x = 930;
    }
}

//If player has not shot, bullet follows player...
//...when shot, shoots in direction and checks for collision.
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

//If bullet collide with alive zombie (X coordinates), kill it 
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

//If bullet collide with alive zombie (Y coordinates), kill it 
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

//Handles game events and game logic
int mainGameEvent(){
    playerID = PlayerInit.playerID;
    int LetterforIP;
    int close_requested = 0;
    char bufIPaddress[12];
    char bufAmountPlayers[2] = "4";
    
    if(LetterforIP > 12){
        LetterforIP = 0;
    }

    areyouhost = CheckIfHost();
    Lookingforgame = CheckIfLooking();

    if(select != 1){
        select = checkIfGamestarted();
        if(select == 1){
            Mix_HaltMusic();
        }
    }

    // Handles all information recived from the server and updates the character with that id
    //udpClient explains what flags(kordLista[3]) does
    reciveData("127.0.0.1", kordLista);

    if(kordLista[3] == 0){
        if((PlayerInit.pPosition[kordLista[0]].x) < (kordLista[1])){
            PlayerInit.pFrame[kordLista[0]] = 0;
            PlayerInit.flip[kordLista[0]] = SDL_FLIP_HORIZONTAL;
        }
        else if((PlayerInit.pPosition[kordLista[0]].x) > (kordLista[1])){
            PlayerInit.pFrame[kordLista[0]] = 0;
            PlayerInit.flip[kordLista[0]] = SDL_FLIP_NONE;
        }
        else if((PlayerInit.pPosition[kordLista[0]].y) < (kordLista[2])){
            PlayerInit.pFrame[kordLista[0]] = 14;
        }
        else if((PlayerInit.pPosition[kordLista[0]].y) > (kordLista[2])){
            PlayerInit.pFrame[kordLista[0]] = 11;
        }
        PlayerInit.pPosition[kordLista[0]].x = kordLista[1];
        PlayerInit.pPosition[kordLista[0]].y = kordLista[2];

    }
    else if(kordLista[3] == 1){
        PlayerInit.pFrame[kordLista[0]] = 15;
    }
    else if(kordLista[3] == 2){
        z[kordLista[1]]->alive = 0;
    }
    else if(kordLista[3] == 3){
        if (Lookingforgame == 1){
            select = kordLista[1];
            PlayerInit.nrOfPlayers = kordLista[2];
        }
    }
    else if(kordLista[3] == 4){
        PlayerInit.alive[kordLista[0]] = kordLista[1];
    }
    //receiveCoordData(&kordLista, &playerID);

    //Game events 
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            close_requested = 1;
            return close_requested;
        }
        if(event.type == SDL_KEYDOWN){
            if (select == 1){
                sendData(0, PlayerInit.pPosition[playerID].x, PlayerInit.pPosition[playerID].y, "127.0.0.1", playerID);
                pressedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);
            }
            MenuKeyboard(event, bufIPaddress, bufAmountPlayers, &LetterforIP);
        }
        if(event.type == SDL_KEYUP){
            releasedKeyEvent(&up_w, &down_s, &left_a, &right_d, &lctrl, event);
        }
    }

    //Game Logic
    if(select == 1){
        playBgGameMusic();
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
        isGameOver();
        printf(" ");    //1 player mode does not work unless this printf() is present, great success, very nice. nasa please give me job
    }
}

//Keyboard to read specific keystrokes made towards IP address or number of players
int MenuKeyboard(SDL_Event event,char buf[],char buf2[], int *LetterforIP){
    if (event.key.keysym.sym == SDLK_0){
        if (Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '0';
        }
    }
    if(event.key.keysym.sym == SDLK_1){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '1'; 
        }
        if(areyouhost == 1 && select != 1){
            buf2[0] = '1';
            PlayerInit.nrOfPlayers = 1;
        }
    }
    if(event.key.keysym.sym == SDLK_2){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '2';
        }
        if(areyouhost == 1 && select != 1){
            buf2[0] = '2';
            PlayerInit.nrOfPlayers = 2;
        }
    }
    if(event.key.keysym.sym == SDLK_3){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '3';
        }
        if(areyouhost == 1 && select != 1){
            buf2[0] = '3';
            PlayerInit.nrOfPlayers = 3;
        }
    }
    if(event.key.keysym.sym == SDLK_4){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '4';
        }
        if(areyouhost == 1 && select != 1){
            buf2[0] = '4';
            PlayerInit.nrOfPlayers = 4;
        }
    }
    if(event.key.keysym.sym == SDLK_5){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '5';
        }
    }
    if(event.key.keysym.sym == SDLK_6){
        if (Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '6';
        }
    }
    if(event.key.keysym.sym == SDLK_7){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '7';
        }
    }
    if(event.key.keysym.sym == SDLK_8){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '8';
        }
    }
    if(event.key.keysym.sym == SDLK_9){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '9';
        }
    }
    if(event.key.keysym.sym == SDLK_PERIOD){
        if(Lookingforgame == 1 && select != 1){
            buf[*LetterforIP] = '.';
        }
    }

    strcpy(AmountPlayersBuffstring,buf2);

    if(Lookingforgame == 1){
        (*LetterforIP)++;
        buf[*LetterforIP] = '\0';
        strcpy(IPBuffstring, buf);
    }
}

//returns the IP address that the non host has entered
void GetIPaddress(char* strOut, unsigned int strSize){
   strncpy(strOut, IPBuffstring, strSize);
}

//returns the amount of players that host has entered 
void GetAmountPlayers(char* strOut, unsigned int strSize){
    strncpy(strOut, AmountPlayersBuffstring, strSize);
}

//Returns if game has been started
int sendSelect(){
    return select;
}