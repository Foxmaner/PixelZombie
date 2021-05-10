#include "menu.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int STARTB_WIDTH = 200;
PRIVATE int STARTB_HEIGTH = 200;
PRIVATE int STARTBPOS_Y = 500;
PRIVATE int STARTBPOS_X = 500;

PRIVATE int STARTBUTTONPOS[5][5] = {500,500};

PUBLIC Startbutton startButtonPos(int x, int y){
    Startbutton button = malloc(sizeof(struct startbutton));
    button->STARTBUTTON_POSITION_X= x;
    button->STARTBUTTON_POSITION_Y= y;
    return button;
}

PUBLIC int getStartState(Startbutton a){
    return a->INITSTART;
}

PUBLIC int getStartButtonWidth(){
    return STARTB_WIDTH;
}

PUBLIC int getStartButtonHeight(){
    return STARTB_HEIGTH;
}

PUBLIC void setStartButtomPositionY(Startbutton a, int y){
    a->STARTBUTTON_POSITION_Y = y;
}

PUBLIC void setStartButtonPositionX(Startbutton a, int x){
    a->STARTBUTTON_POSITION_X = x;
}

PUBLIC int setStartButtonPosition(int x, int y)
{
    return STARTBUTTONPOS[x][y];
}

