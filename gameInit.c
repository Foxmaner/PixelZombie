#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "map.h"
#include "zombie.h"
#include "player.h"

#define WINDOW_WIDTH (1024)
#define WINDOW_HEIGHT (1024)

void initGame(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Pixel Zombie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win){
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    //Initilize renderer
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //Initilize background
    SDL_Texture *mTiles = NULL;
    SDL_Rect gTiles[32];
   
    //Alien Initilizers
    SDL_Texture *mZombie = NULL;
    SDL_Rect gZombie[8];  //8 sprites per zombie
    int nrOfZombies=6;
    ZombieFrame zFrame[nrOfZombies];
    Zombie z[nrOfZombies];
    SDL_Rect zPosition[nrOfZombies];
    //Creates the zombies
    for(int i = 0; i < nrOfZombies; i++){
        z[i] = createZombie(getZSpawnPointX(i % 3),getZSpawnPointY(i % 3));
        zPosition[i].x = getZombiePositionX(z[i]);
        zPosition[i].y = getZombiePositionY(z[i]);
        zPosition[i].w = 43;
        zPosition[i].h = 54;
    }
    
    //Player initilizer
    int playerID=-1;
    int nrOfPlayers=4;
    SDL_Texture *mPlayer = NULL;
    SDL_Rect gPlayer[16];
    Player p[nrOfPlayers];
    SDL_Rect pPosition[nrOfPlayers];
    for(int i = 0; i < nrOfPlayers; i++){
        p[i] = createPlayer(getSpawnPointX(i),getSpawnPointY(i));
        pPosition[i].x = getPlayerPositionX(p[i]);
        pPosition[i].y = getPlayerPositionY(p[i]);
        pPosition[i].w = 64;
        pPosition[i].h = 64;
    }
    unsigned int lastDmgTakenTime = 0, currentDmgTakenTime = 0; //Used to limit taken damage to 1hp/s
    int pFrame=0; //in gPlayer[] to show which state the player is in, which sprite is being used

    //Bullet initilizer
    SDL_Texture *mBullet;
    SDL_Rect gBullet[1];
    SDL_Rect bPosition;
    bPosition.x = 100;
    bPosition.y = 100;
    bPosition.w = 15;
    bPosition.h = 5;
    bool shot = false;
    int lastShotTime = 0, currentShotTime = 0;
    int bVelX = 1, bVelY = 1, bUpDown = 0;

    // End of Setup
    //-------------------------------------------
    // Start of continuing render-loop

    const Uint8 *state = SDL_GetKeyboardState(NULL); //Initierar hela skrivbordet. Det möjliggör att man konstant kan skanna in om en tangent är på eller av
    // set to 1 when window close button is pressed
    int close_requested = 0;
    int up_w,down_s,left_a,right_d,lctrl;
    int kordLista[2];
    
    loadMedia(renderer, win, &mTiles, gTiles, &mZombie, gZombie, &mPlayer, gPlayer, &mBullet, gBullet);
}