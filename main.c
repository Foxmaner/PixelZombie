//Project start: 2021-04-15
//Created by Eskil B, Marcus M, Carl G, Anton C and Markus H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "lib/include/gameInit.h"
#include "lib/include/gameEvent.h"
#include "lib/include/gameRender.h"
#include "lib/include/gameQuit.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    int close = 0;
    GIO.initedGame = false;
    GIO.gameOver = true;
    do{
        if(GIO.gameOver) initGame();
        close = mainGameEvent();
        renderGame();
    }while (close != 1);

    quitGame();
}