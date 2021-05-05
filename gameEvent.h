#ifndef gameEvent_h
#define gameEvent_h

#include <stdio.h>
#include <SDL2/SDL.h>

void receiveCoordData(int *kordLista[], int *playerID);
void pressedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
void releasedKeyEvent(int *up_w, int *down_s, int *left_a, int *right_d, int *lctrl, SDL_Event event);
void zombieTrackingPlayer(int i);
void zombieCollisionWithPlayer(int i, int currentDmgTakenTime,int lastDmgTakenTime);
void zombieCollisionWithMap(int i);
void playerCollisionWithMap();
void bulletPositioning();

int mainGameEvent();

#endif