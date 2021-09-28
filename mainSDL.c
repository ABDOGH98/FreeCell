#include "mainSDL.h"


SDL_Window *createWindow (Uint32 flag , int h , int w)
{
    SDL_Init(flag);
    SDL_Window *window = SDL_CreateWindow("FreeCell",
                          SDL_WINDOWPOS_CENTERED,
                          23,
                          h, w ,
                          32);

    return window ;
}

SDL_Renderer *createRender(SDL_Window *window)
{
     SDL_Renderer *windowsRender = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
     return windowsRender ;
}

SDL_Texture *createTexture (SDL_Renderer *windowRender ,int h , int w )
{
    SDL_Texture *windowTexture = SDL_CreateTexture(windowRender, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,h,w);
    return windowTexture ;
}
void drawInTexture(SDL_Renderer *windowRender , SDL_Texture *m_Texture , SDL_Rect *rect , SDL_Color *color)
{
    SDL_SetRenderDrawColor(windowRender , color->r , color->g , color->b , color->a);
    SDL_SetRenderTarget(windowRender, m_Texture);
    SDL_RenderDrawRect(windowRender,rect);
    SDL_SetRenderTarget(windowRender, NULL);
}

void carte_model(SDL_Renderer *windowRender,SDL_Rect *rect_zone , Liste *L ,SDL_Texture **coeursCartes ,SDL_Texture **careauxCartes ,SDL_Texture **trefleCartes ,SDL_Texture **piqueCartes)
{
    int numberCarte = 0 ;
    Element *e = L->first ;
    int padding = 0 ;

    while(e != NULL)
    {
        SDL_SetRenderTarget(windowRender,NULL);
        SDL_Rect rect = {rect_zone->x,rect_zone->y+padding,135,200};
        if(strcmp("coeurs",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, coeursCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("carreaux",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, careauxCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("piques",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, piqueCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("trefles",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, trefleCartes[numberCarte-1], NULL,&rect);
        }
        padding += 40 ;
        e = e->next ;
    }
}
//****************************************************************************************************************

void createMovingCarte(SDL_Renderer *windowRender,Element *e,int cordX,int cordY,SDL_Texture **coeursCartes ,SDL_Texture **careauxCartes ,SDL_Texture **trefleCartes ,SDL_Texture **piqueCartes  )
{
    int numberCarte = 0 ;
    SDL_Rect movingRect = {cordX,cordY,135,200};
    if(strcmp("coeurs",e->carte->shape)==0)
    {
        numberCarte = e->carte->number ;
        SDL_RenderCopy(windowRender, coeursCartes[numberCarte-1], NULL,&movingRect);
    }
    if(strcmp("carreaux",e->carte->shape)==0)
    {
        numberCarte = e->carte->number ;
        SDL_RenderCopy(windowRender, careauxCartes[numberCarte-1], NULL,&movingRect);
    }
    if(strcmp("piques",e->carte->shape)==0)
    {
        numberCarte = e->carte->number ;
        SDL_RenderCopy(windowRender, piqueCartes[numberCarte-1], NULL,&movingRect);
    }
    if(strcmp("trefles",e->carte->shape)==0)
    {
        numberCarte = e->carte->number ;
        SDL_RenderCopy(windowRender, trefleCartes[numberCarte-1], NULL,&movingRect);
    }

}

void createCarteCouer(SDL_Renderer *windowRender ,SDL_Rect *rect , SDL_Texture **cartes)
{
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface *img = NULL ;
    SDL_Surface *texte = NULL ;

    SDL_Color backGround_Carte = {255,255,255,255};
    SDL_Color texte_color = {0,0,0,255};




    SDL_Rect *m_carte = {0,0,135,200} ;

        char numberCarte[1]  ;

        img = SDL_LoadBMP("./img/coeur.bmp");


        for(int i = 0 ; i<13 ; i++)
        {
            SDL_Rect position_number_carte = {rect->x+rect->w-25, rect->y+5 , 10 , 10 } ;
            SDL_Rect position_imgMIidd_carte = {rect->x+30, rect->y+70 , 70 , 70 } ;
            SDL_Rect position_img_carte = {rect->x+10, rect->y+10 , 20 , 20 } ;
            itoa(i+1,numberCarte,10);

            cartes[i] = createTexture(windowRender,135,200);

            SDL_SetRenderDrawColor(windowRender , backGround_Carte.r , backGround_Carte.g , backGround_Carte.b , backGround_Carte.a);
            SDL_SetRenderTarget(windowRender,cartes[i]) ;
            SDL_RenderFillRect(windowRender, m_carte);


            texte = TTF_RenderText_Solid(police,numberCarte,texte_color);
            SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(windowRender, texte);
            SDL_SetRenderTarget(windowRender,texture_texte) ;
            SDL_QueryTexture(texture_texte, NULL,NULL,&position_number_carte.w ,&position_number_carte.h );
            SDL_SetRenderTarget(windowRender,cartes[i]);
            SDL_RenderCopy(windowRender, texture_texte, NULL,&position_number_carte);

            SDL_Texture *texture_img = SDL_CreateTextureFromSurface(windowRender,img) ;

            SDL_SetRenderTarget(windowRender, cartes[i]);
            SDL_RenderCopy(windowRender, texture_img, NULL, &position_img_carte);

            SDL_RenderCopy(windowRender, texture_img, NULL, &position_imgMIidd_carte);

            SDL_DestroyTexture(texture_img);
            SDL_DestroyTexture(texture_texte);
        }

        SDL_FreeSurface(img);
        SDL_FreeSurface(texte);

        TTF_CloseFont(police);
        TTF_Quit();
}

void createCarteCarreau(SDL_Renderer *windowRender ,SDL_Rect *rect , SDL_Texture **cartes)
{
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface *img = NULL ;
    SDL_Surface *texte = NULL ;

    SDL_Color backGround_Carte = {255,255,255,255};
    SDL_Color texte_color = {0,0,0,255};




    SDL_Rect *m_carte = {0,0,135,200} ;

        char numberCarte[1]  ;

        img = SDL_LoadBMP("./img/careau.bmp");


        for(int i = 0 ; i<13 ; i++)
        {
            SDL_Rect position_number_carte = {rect->x+rect->w-25, rect->y+5 , 10 , 10 } ;
            SDL_Rect position_imgMIidd_carte = {rect->x+30, rect->y+70 , 70 , 70 } ;
            SDL_Rect position_img_carte = {rect->x+10, rect->y+10 , 20 , 20 } ;

            itoa(i+1,numberCarte,10);

            cartes[i] = createTexture(windowRender,135,200);

            SDL_SetRenderDrawColor(windowRender , backGround_Carte.r , backGround_Carte.g , backGround_Carte.b , backGround_Carte.a);
            SDL_SetRenderTarget(windowRender,cartes[i]) ;
            SDL_RenderFillRect(windowRender, m_carte);


            texte = TTF_RenderText_Solid(police,numberCarte,texte_color);
            SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(windowRender, texte);
            SDL_SetRenderTarget(windowRender,texture_texte) ;
            SDL_QueryTexture(texture_texte, NULL,NULL,&position_number_carte.w ,&position_number_carte.h );
            SDL_SetRenderTarget(windowRender,cartes[i]);
            SDL_RenderCopy(windowRender, texture_texte, NULL,&position_number_carte);

            SDL_Texture *texture_img = SDL_CreateTextureFromSurface(windowRender,img) ;

            SDL_SetRenderTarget(windowRender, cartes[i]);
            SDL_RenderCopy(windowRender, texture_img, NULL, &position_img_carte);

            SDL_RenderCopy(windowRender, texture_img, NULL, &position_imgMIidd_carte);

            SDL_DestroyTexture(texture_img);
            SDL_DestroyTexture(texture_texte);
        }

        SDL_FreeSurface(img);
        SDL_FreeSurface(texte);

        TTF_CloseFont(police);
        TTF_Quit();
}
void createCarteTrefle(SDL_Renderer *windowRender ,SDL_Rect *rect , SDL_Texture **cartes)
{
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface *img = NULL ;
    SDL_Surface *texte = NULL ;

    SDL_Color backGround_Carte = {255,255,255,255};
    SDL_Color texte_color = {0,0,0,255};




    SDL_Rect *m_carte = {0,0,135,200} ;

        char numberCarte[1]  ;
        img = SDL_LoadBMP("./img/trefle.bmp");


        for(int i = 0 ; i<13 ; i++)
        {
            SDL_Rect position_number_carte = {rect->x+rect->w-25, rect->y+5 , 10 , 10 } ;
            SDL_Rect position_imgMIidd_carte = {rect->x+30, rect->y+70 , 70 , 70 } ;
            SDL_Rect position_img_carte = {rect->x+10, rect->y+10 , 20 , 20 } ;

            itoa(i+1,numberCarte,10);

            cartes[i] = createTexture(windowRender,135,200);

            SDL_SetRenderDrawColor(windowRender , backGround_Carte.r , backGround_Carte.g , backGround_Carte.b , backGround_Carte.a);
            SDL_SetRenderTarget(windowRender,cartes[i]) ;
            SDL_RenderFillRect(windowRender, m_carte);


            texte = TTF_RenderText_Solid(police,numberCarte,texte_color);
            SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(windowRender, texte);
            SDL_SetRenderTarget(windowRender,texture_texte) ;
            SDL_QueryTexture(texture_texte, NULL,NULL,&position_number_carte.w ,&position_number_carte.h );
            SDL_SetRenderTarget(windowRender,cartes[i]);
            SDL_RenderCopy(windowRender, texture_texte, NULL,&position_number_carte);

            SDL_Texture *texture_img = SDL_CreateTextureFromSurface(windowRender,img) ;

            SDL_SetRenderTarget(windowRender, cartes[i]);
            SDL_RenderCopy(windowRender, texture_img, NULL, &position_img_carte);

            SDL_RenderCopy(windowRender, texture_img, NULL, &position_imgMIidd_carte);

            SDL_DestroyTexture(texture_img);
            SDL_DestroyTexture(texture_texte);
        }

        SDL_FreeSurface(img);
        SDL_FreeSurface(texte);

        TTF_CloseFont(police);
        TTF_Quit();
}

void createCartePique(SDL_Renderer *windowRender ,SDL_Rect *rect , SDL_Texture **cartes)
{
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("OpenSans-Bold.ttf", 20);
    SDL_Surface *img = NULL ;
    SDL_Surface *texte = NULL ;

    SDL_Color backGround_Carte = {255,255,255,255};
    SDL_Color texte_color = {0,0,0,255};




    SDL_Rect *m_carte = {0,0,135,200} ;

        char numberCarte[1]  ;

        img = SDL_LoadBMP("./img/pique.bmp");


        for(int i = 0 ; i<13 ; i++)
        {
            SDL_Rect position_number_carte = {rect->x+rect->w-25, rect->y+5 , 10 , 10 } ;
            SDL_Rect position_imgMIidd_carte = {rect->x+30, rect->y+70 , 70 , 70 } ;
            SDL_Rect position_img_carte = {rect->x+10, rect->y+10 , 20 , 20 } ;

            itoa(i+1,numberCarte,10);

            cartes[i] = createTexture(windowRender,135,200);

            SDL_SetRenderDrawColor(windowRender , backGround_Carte.r , backGround_Carte.g , backGround_Carte.b , backGround_Carte.a);
            SDL_SetRenderTarget(windowRender,cartes[i]) ;
            SDL_RenderFillRect(windowRender, m_carte);


            texte = TTF_RenderText_Solid(police,numberCarte,texte_color);
            SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(windowRender, texte);
            SDL_SetRenderTarget(windowRender,texture_texte) ;
            SDL_QueryTexture(texture_texte, NULL,NULL,&position_number_carte.w ,&position_number_carte.h );
            SDL_SetRenderTarget(windowRender,cartes[i]);
            SDL_RenderCopy(windowRender, texture_texte, NULL,&position_number_carte);

            SDL_Texture *texture_img = SDL_CreateTextureFromSurface(windowRender,img) ;

            SDL_SetRenderTarget(windowRender, cartes[i]);
            SDL_RenderCopy(windowRender, texture_img, NULL, &position_img_carte);

            SDL_RenderCopy(windowRender, texture_img, NULL, &position_imgMIidd_carte);

            SDL_DestroyTexture(texture_img);
            SDL_DestroyTexture(texture_texte);
        }

        SDL_FreeSurface(img);
        SDL_FreeSurface(texte);

        TTF_CloseFont(police);
        TTF_Quit();
}

int checkToReplace(Element *movingCarte , Element *baseCarte)
{
    if( baseCarte == NULL || (strcmp(movingCarte->carte->color,baseCarte->carte->color)!=0 && movingCarte->carte->number+1 == baseCarte->carte->number) )
    {
        return 1 ;
    }
    return 0 ;
}

int checkFirstCarteBase(Element *base , Element *e)
{
    if(base == NULL && e->carte->number == 1 )
    {
        return 1 ;
    }
    else if(base != NULL && e->carte->number != 1 && strcmp(base->carte->color,e->carte->color)!=0 && base->carte->number+1 == e->carte->number)
    {
        return 0 ;
    }
    else return -1 ;
}

void setBaseCarte(SDL_Renderer *windowRender,SDL_Rect *rect_zone , Liste *L ,SDL_Texture **coeursCartes ,SDL_Texture **careauxCartes ,SDL_Texture **trefleCartes ,SDL_Texture **piqueCartes)
{
    int numberCarte = 0 ;
    Element *e = L->first ;


    while(e != NULL)
    {
        SDL_SetRenderTarget(windowRender,NULL);
        SDL_Rect rect = {rect_zone->x,rect_zone->y,135,200};
        if(strcmp("coeurs",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, coeursCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("carreaux",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, careauxCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("piques",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, piqueCartes[numberCarte-1], NULL,&rect);
        }
        if(strcmp("trefles",e->carte->shape)==0)
        {
            numberCarte = e->carte->number ;
            SDL_RenderCopy(windowRender, trefleCartes[numberCarte-1], NULL,&rect);
        }

        e = e->next ;
    }
}
int gameOver(Liste **zone1 , Liste **zone2 , Liste **zone3)
{
    for(int i=0 ; i<8 ; i++)
    {
        printf("\n i-1 = %d\n",i);
        for(int j=0 ; j<8 ; j++)
        {
            if(i!=j)
            {
                printf("\n  j-1 = %d\n",j);
                if ( zone1[i]->first==NULL || zone1[j]->first==NULL || (   strcmp(zone1[i]->last->carte->color,zone1[j]->last->carte->color)!=0 && zone1[i]->last->carte->number== zone1[j]->last->carte->number+1) )
                {
                    printf("    return 0-1\n");
                    return 0 ;
                }
            }
        }
    }
    for(int i=0 ; i<4 ; i++)
    {
        printf("\n i-2 = %d\n",i);
        for(int k=0 ; k<8 ; k++)
        {
            printf("\n  k-2 = %d\n",k);

            if ( zone2[i]->first==NULL || (strcmp(zone2[i]->last->carte->color,zone1[k]->last->carte->color)!=0 && zone2[i]->last->carte->number + 1 == zone1[k]->last->carte->number ) )
            {
                printf("\n      return 0-2\n");
                return 0 ;
            }
        }
    }
    for(int i=0 ; i<4 ; i++)
    {

           for(int y=0 ; y<8 ; y++)
           {
               if(zone3[i]->first==NULL && zone1[y]->last->carte->number == 1)
               {
                    return 0 ;
               }
               else if(zone3[i]->first!=NULL && zone3[i]->last->carte->number + 1  == zone1[y]->last->carte->number && strcmp(zone3[i]->last->carte->color,zone1[y]->last->carte->color)!=0  )
               {
                    return 0 ;
               }
           }
           for(int z=0 ; z<4 ; z++)
           {
               if(zone3[i]->first==NULL && zone1[z]->last->carte->number == 1 )
               {
                    return 0 ;
               }
               else if(zone3[i]->first!=NULL && zone3[i]->last->carte->number + 1  == zone2[z]->last->carte->number && strcmp(zone3[i]->last->carte->color,zone2[z]->last->carte->color)!=0  )
               {
                    return 0 ;
               }
           }
    }
    printf("return 1");
    return 1 ;
}
