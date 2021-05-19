#ifndef gameEvent_h
#define gameEvent_h

#include <stdio.h>
#include <math.h>

void setSelect(int a);
int getPlayerID();
void receiveCoordData(int *kordLista[], int *playerID);
void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl,SDL_Event event);
void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
double distance( int x1, int y1, int x2, int y2 );
void zombieTrackingPlayer(int i);
void isGameOver();
void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime,int *lastDmgTakenTime);
void zombieCollisionWithMap(int i);
void playerCollisionWithMap();
void bulletPositioning(int i);
void bulletCollisionWithZombieX(int i);
void bulletCollisionWithZombieY(int i);
int checkmousestate(int *lowX,int *highX,int *lowY,int *highY);
int MenuKeyboard(SDL_Event event, char buf[], int *LetterforIP);
void GetString( char* strOut, unsigned int strSize );


int mainGameEvent();

#endif