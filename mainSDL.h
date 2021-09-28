#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL_ttf.h"
#include <string.h>

typedef struct{

    int number ;
    char *shape ;
    char *color ;
}Carte;

typedef struct elem{

    Carte *carte ;
    struct elem *next ;
    struct elem *previous ;

}Element ;

typedef struct
{
    Element *first;
    Element *last;

} Liste;


SDL_Window *createWindow(Uint32  , int  , int ) ;
SDL_Renderer *createRender(SDL_Window *);
SDL_Texture *createTexture (SDL_Renderer * ,int , int );
void carte_model(SDL_Renderer * ,SDL_Rect * , Liste * , SDL_Texture **  , SDL_Texture ** , SDL_Texture ** , SDL_Texture **);
void createMovingCarte(SDL_Renderer *,Element *,int ,int ,SDL_Texture ** ,SDL_Texture ** ,SDL_Texture ** ,SDL_Texture **  ) ;
void drawInTexture(SDL_Renderer * ,SDL_Texture *, SDL_Rect * , SDL_Color *);
void createCarteCouer(SDL_Renderer * ,SDL_Rect * , SDL_Texture **) ;
void createCarteCarreau(SDL_Renderer * ,SDL_Rect * , SDL_Texture **) ;
void createCarteTrefle(SDL_Renderer * ,SDL_Rect * , SDL_Texture **) ;
void createCartePique(SDL_Renderer * ,SDL_Rect * , SDL_Texture **) ;
int checkToReplace(Element * , Element *) ;

int moveCarteToBase(Liste *);
int checkFirstCarteBase(Element * , Element *);
int gameOver(Liste ** , Liste ** , Liste **);

