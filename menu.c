
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameInit.h"
#include "menu.h"
#include "gameEvent.h"
#include "ttf.h"
#include "player.h"
#include "gameRender.h"

#define PUBLIC /* empty */
#define PRIVATE static

int startrender=2;
int credits=2;
int back=2;
int lookingforgame=2;
int hostinggame=2;
//sets start renderer to a specific value
void setStartRender(int a){
    startrender = a;
}
//Returns if the game has been initiated
int checkIfGamestarted(){
    return startrender;
}
//Renders host lobby 
PUBLIC void hostinglobby(SDL_Renderer *renderer, int *back, int *hostinggame, int *startrender,char* AmountPlayers){
    int StartbuttonPos[4]={800,1050,40,125};
    int backbutton[4]={40,190,600,750};
    createTextbox(iSDL.renderer, 40, 40, "Number of players:", 36); 
    createTextbox(iSDL.renderer, 365, 40,  AmountPlayers, 36); 
    createTextbox(iSDL.renderer, 800, 40, "Start game", 36); 
    createTextbox(iSDL.renderer, 40, 600, "Back", 36);
    *startrender=checkmousestate(&StartbuttonPos[0],&StartbuttonPos[1],&StartbuttonPos[2],&StartbuttonPos[3]);
    *back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
    if (*back==1){
        clearRenderer();
        (*hostinggame)=2;
    } 

}
//Renders non host lobby
PUBLIC void findinggameLobby(SDL_Renderer *renderer, int *back, int *lookingforgame, int *startrender,char* IPaddress){
    int backbutton[4]={40,190,600,750};
    createTextbox(iSDL.renderer, 40, 40, "Enter IPadress:", 36); 
    createTextbox(iSDL.renderer, 300, 40,  IPaddress, 36); 
    createTextbox(iSDL.renderer, 40, 600, "Back", 36);
    *startrender=sendSelect();
    *back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
    if (*back==1){
        clearRenderer();
        (*lookingforgame)=2;
    }

}
//Render default main menu
PUBLIC void mainMenu(SDL_Renderer *renderer, int *lookingforgame,int *hostinggame, int *credits, int *back){
    int buttonPos[4]={40,155,40,85};    
    int buttonPos2[4]={40,155,80,125};
    int buttonPos3[4]={40,155,120,165};
    createTextbox(iSDL.renderer, 40, 40, "Find game", 36);
    createTextbox(iSDL.renderer, 40, 80, "Host game", 36);
    createTextbox(iSDL.renderer, 40, 120, "Credits", 36); 
    *lookingforgame=checkmousestate(&buttonPos[0],&buttonPos[1],&buttonPos[2],&buttonPos[3]);
    *hostinggame=checkmousestate(&buttonPos2[0],&buttonPos2[1],&buttonPos2[2],&buttonPos2[3]);
    *credits=checkmousestate(&buttonPos3[0],&buttonPos3[1],&buttonPos3[2],&buttonPos3[3]);
    *back=2;

}
//Renders credits part of menu
PUBLIC void creditMenu(SDL_Renderer *renderer, int *credits, int *back){
    int backbutton[4]={40,190,600,750};
    
    createTextbox(iSDL.renderer, 40, 600, "Back", 36);
    //Creators
    createTextbox(iSDL.renderer, 40, 80, "Made by Anton C, Carl G, Eskil B, Markus H, Marcus M", 36); 
    //Heart pixel art
    createTextbox(iSDL.renderer, 40, 120, "Heart pixel art: DanSevenStar.xyz", 30); 
    //Player
    createTextbox(iSDL.renderer, 40, 160, "Player: thekingphoenix & Bonsaiheldin", 30); 
    //Zombie
    createTextbox(iSDL.renderer, 40, 200, "Zombie: Kazzador & Enterbrain", 30); 
    //Musik
    createTextbox(iSDL.renderer, 40, 240, "Music: March of Midnight by Scott Buckley ", 30);

    *back=checkmousestate(&backbutton[0],&backbutton[1],&backbutton[2],&backbutton[3]);
    if (*back==1){
        clearRenderer();
        (*credits)=2;    
    }
}
//Returns if host instance is active. 
PUBLIC int CheckIfHost(){
    return hostinggame;
}
//Returns if person is a none host
PUBLIC int CheckIfLooking(){
    return lookingforgame;
}

PUBLIC void theMenu(SDL_Renderer *renderer){
    char AmountPlayers[2]="\0";
    char IPaddress[12]=" \0";
    SDL_RenderCopyEx(iSDL.renderer, MenuInit.mBackgroundMenu, &MenuInit.gMenubackground[0],&MenuInit.gMenubackground[0], 0, NULL, SDL_FLIP_NONE);
    //GetIPaddress(PlayerInit.IPaddress, 15 );
    GetAmountPlayers(AmountPlayers, 2);
    //Beginning menu
    if (lookingforgame!=1 && credits!=1 && lookingforgame!=1 && hostinggame!=1){
        mainMenu(iSDL.renderer, &lookingforgame, &hostinggame, &credits, &back);
    }
    //None host lobby
    if (lookingforgame==1){
        findinggameLobby(iSDL.renderer, &back, &lookingforgame, &startrender,IPaddress);
    }
    //Host session lobby
    if (hostinggame==1)
    {
        hostinglobby(iSDL.renderer, &back, &hostinggame, &startrender,AmountPlayers);
    }
    //Credits for creators and artists
    if (credits==1)
    {
        creditMenu(iSDL.renderer, &credits, &back);
    }
}