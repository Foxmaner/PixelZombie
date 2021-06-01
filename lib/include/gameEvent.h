#ifndef gameEvent_h
#define gameEvent_h

#include <stdio.h>
#include <math.h>


int checkmousestate(int *lowX,int *highX,int *lowY,int *highY);

//Sets select in order to make game over

void setSelect(int a);
int getPlayerID();
void receiveCoordData(int *kordLista[], int *playerID);
void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl,SDL_Event event);
void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
double distance( int x1, int y1, int x2, int y2 );

//Zombies walk towards nearest player and changes frames (animation)
void zombieTrackingPlayer(int i);

//Checks all alive zombies if they run into eachother...
//...and adjust their position if they do.
void zombieCollisionWithZombie(int i);

//Restarts game if all players are dead
void isGameOver();

//Checks if alive zombie collide with alive players...
//...and removes player hitpoints if they do
void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime,int *lastDmgTakenTime);

//Checks if zombies collide with map boundries...
//...and adjust thier position accordingly.
void zombieCollisionWithMap(int i);

//Checks if players collide with map boundries...
//...and adjust thier position accordingly.
void playerCollisionWithMap();

//If player has not shot, bullet follows player...
//...when shot, shoots in direction and checks for collision.
void bulletPositioning(int i);

//If bullet collide with alive zombie (X coordinates), kill it 
void bulletCollisionWithZombieX(int i);
//If bullet collide with alive zombie (Y coordinates), kill it
void bulletCollisionWithZombieY(int i);

int checkmousestate(int *lowX,int *highX,int *lowY,int *highY);
int MenuKeyboard(SDL_Event event,char buf[],char buf2[], int *LetterforIP);
void GetIPaddress( char* strOut, unsigned int strSize );
void GetAmountPlayers( char* strOut, unsigned int strSize );
int sendSelect();

int mainGameEvent();

#endif