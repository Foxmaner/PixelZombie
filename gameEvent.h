#ifndef gameEvent_h
#define gameEvent_h

#include <stdio.h>
#include <math.h>

void receiveCoordData(int *kordLista[], int *playerID);
void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
double distance( int x1, int y1, int x2, int y2 );
void zombieTrackingPlayer(int i);
void zombieCollisionWithPlayer(int i, int *currentDmgTakenTime,int *lastDmgTakenTime);
void zombieCollisionWithMap(int i);
void playerCollisionWithMap();
void bulletPositioning();

int mainGameEvent();

#endif