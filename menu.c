
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "menu.h"
#include "gameEvent.h"
#include "ttf.h"

#define PUBLIC /* empty */
#define PRIVATE static

PUBLIC void playerLobby(SDL_Renderer *renderer, int *startrender, int *lobby, int *credits, int *back, char* IPaddress){
    int backbutton[4]={40,190,600,750};
    int StartbuttonPos[4]={800,1050,40,125};

    createTextbox(iSDL.renderer, 40, 40, "Enter IPadress:", 36); 
    createTextbox(iSDL.renderer, 300, 40,  IPaddress, 36); 
    createTextbox(iSDL.renderer, 40, 600, "Back", 36);

    createTextbox(iSDL.renderer, 800, 40, "Start game", 36); 
    *startrender=checkmousestate(&StartbuttonPos[0],&StartbuttonPos[1],&StartbuttonPos[2],&StartbuttonPos[3]);

    *back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
    if (*back==1){
        (*lobby)=2;
        (*credits)=2;    
    }
}

PUBLIC void mainMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back){
    int buttonPos[4]={40,155,40,85};    
    int buttonStartGamePos[4]={40,155,80,125};
    createTextbox(iSDL.renderer, 40, 40, "START", 36);
    createTextbox(iSDL.renderer, 40, 80, "Credits", 36); 
    *lobby=checkmousestate(&buttonPos[0],&buttonPos[1],&buttonPos[2],&buttonPos[3]);
    *credits=checkmousestate(&buttonStartGamePos[0],&buttonStartGamePos[1],&buttonStartGamePos[2],&buttonStartGamePos[3]);
    *back=2;

}

PUBLIC void creditMenu(SDL_Renderer *renderer, int *lobby, int *credits, int *back){
    int backbutton[4]={40,190,600,750};

    createTextbox(iSDL.renderer, 40, 600, "Back", 36);
    //Creators
    createTextbox(iSDL.renderer, 40, 80, "Made by Anton C, Carl G, Eskil B, Markus H, Marcus M", 36); 
    //Heart pixel art
    createTextbox(iSDL.renderer, 40, 120, "Heart pixel art: DanSevenStar.xyz", 30); 
    //Spelare
    createTextbox(iSDL.renderer, 40, 160, "Player: thekingphoenix & Bonsaiheldin", 30); 
    //Zombie
    createTextbox(iSDL.renderer, 40, 200, "Zombie: Kazzador & Enterbrain", 30); 
    //Musik
    createTextbox(iSDL.renderer, 40, 240, "Music: March of Midnight by Scott Buckley ", 30); 

    *back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
    if (*back==1){
        (*lobby)=2;
        (*credits)=2;    
    }   
}

PUBLIC void theMenu()
{

}