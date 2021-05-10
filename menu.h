#ifndef menu_h
#define menu_h
#include <stdio.h>
#include <SDL2/SDL.h>


struct startbutton{
    int STARTBUTTON_POSITION_X;
    int STARTBUTTON_POSITION_Y;
    int INITSTART;
}; typedef struct startbutton *Startbutton;

struct startsync{
    SDL_Texture *mstartbutton;
    SDL_Rect gstartbutton[1];
    SDL_Rect WhichPlayer[4];
    int GameInstance[4];
};typedef struct startsync Start_Init;
Start_Init StartInit;

int setStartButtonPosition(int x, int y);
int getStartState(Startbutton a);
int getStartButtonWidth();
int getStartButtonHeight();
void setStartButtomPositionY(Startbutton a, int y);
void setStartButtonPositionX(Startbutton a, int x);
Startbutton startButtonPos(int x, int y);

#endif /* menu_h */