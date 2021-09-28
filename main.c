#include "mainSDL.h"

const int FPS = 120;
const int DELAY_TIME = 1000.0f/FPS;

Liste *createListe()
{
    Liste *l ;
    l = (Liste *)malloc(sizeof(Liste));
    l->first=NULL;
    l->last=NULL;
    return l ;
}

Liste **initializeZone(int size)
{
    Liste **e ;
    e = (Liste **)malloc(size*sizeof(Liste));

    for (int i = 0; i < size; i++)
    {
        e[i] = createListe() ;
    }

    return e ;
}
Element *createElement(Carte *carte  )
{
    Element *e ;
    e = (Element *)malloc(sizeof(Element));
    e->carte = carte ;
    e->next = NULL ;
    e->previous = NULL ;
    return e;
}

Carte *createCarte(int number , char *shape ,char *color)
{
    Carte *c;
    c=(Carte *)malloc(sizeof(Carte));
    c->number=number;
    c->color=color;
    c->shape=shape;
    return c;
}

void push(Liste *L , Carte *carte)
{
    Element *newElement;
    newElement = createElement(carte);

    if (L->first == NULL)
    {
        newElement->carte = carte;
        L->first = newElement;
        L->last = newElement;
        return;
    }

    newElement->carte = carte;
    newElement->previous = L->last;

    L->last->next = newElement;
    L->last = newElement;
}



void addCarteToZone1 (Carte **cartes ,Liste **zone ,int size )
{
    for (int i = 0 , j = 0 ,  z=0; i < size; i++)
    {

        if (i<4)
        {
            while (z<7)
            {
                push(zone[i],cartes[j]);
                z++ ;
                j++ ;
            }
        }
        else
        {
            while (z<6)
            {
                push(zone[i],cartes[j]);
                z++ ;
                j++ ;
            }
        }
        z = 0 ;
    }

}
void separateCartes(Carte **cartes)
{
    srand(time(NULL));
    Carte *tmpCarte = NULL ;
    int carte1 = 0 ;
    int carte2 = 0 ;

    for (int i = 0; i < 52; i++)
    {

        carte1 = (rand()%51)+0 ;
        carte2 = (rand()%51)+0 ;
        while (carte2 == carte1)
        {
            carte2 = (rand()%51)+0 ;
        }

        tmpCarte = cartes[carte1] ;
        cartes[carte1] = cartes[carte2] ;
        cartes[carte2] = tmpCarte ;
        tmpCarte = NULL ;
    }

}

void displayALL(Liste *L)
{
    Element *p ;
    p=L->first;

    while (p !=NULL)
    {
        printf("First : %d -> %s\n",p->carte->number,p->carte->shape);


        p = p->next ;
    }
    printf("\n-----------------------------------------------------\n");
}

Element *getLastCarte(Liste *L)
{
    return L->last ;
}

Element *deletLastCarte(Liste **L)
{
    Element *tmp;
    tmp = (*L)->last;
    if((*L)->last == NULL && (*L)->first==NULL)
    {
        return ;
    }
    else if (tmp->previous == NULL)
        {

            (*L)->last = NULL;
            (*L)->first = NULL ;
            return tmp;
        }

    (*L)->last = (*L)->last->previous;
    (*L)->last->next = NULL ;

    return tmp;

}

int main(int argc, char *argv[])
{


    Carte *cartes[52] ;
    Liste **zone1 ;
    Liste **zone2 ;
    Liste **zone3 ;

    zone1 = initializeZone(8);
    zone2 = initializeZone(4);
    zone3 = initializeZone(4);

    for (int i = 0 ; i < 13; i++)
    {
        cartes[i] = createCarte(i+1,"carreaux","red");
    }
    for (int i = 13 , j=1; i < 26; i++)
    {
        cartes[i] = createCarte(j,"piques","black");
        j++;
    }
    for (int i = 26 , j=1; i < 39; i++)
    {
        cartes[i] = createCarte(j,"coeurs","red");
        j++;
    }
    for (int i = 39 , j=1; i < 52; i++)
    {
        cartes[i] = createCarte(j,"trefles","black");
        j++;
    }
    SDL_Texture *caretCoeur[13], *carteTrefle[13] , *cartePique[13] , *carteCarreau[13] ;

    SDL_Event windowEvent ;
    SDL_Window *window = createWindow(SDL_INIT_VIDEO,1300,840); //create window with HIGH = 1000 & width = 800
    SDL_Renderer *windowRender = createRender(window);
    SDL_Texture *m_Texture = createTexture(windowRender,1300,840);

    start : ;

    separateCartes(cartes);
    addCarteToZone1(cartes,zone1,8);



    SDL_Rect SDL_zoneMother = {0, 0 , 1300,840} ;

    SDL_Rect SDL_zone2 = {3, 5 , 645,227} ;
    SDL_Rect SDL_zone3 = {652, 5 , 645 , 227 } ;
    SDL_Rect SDL_zone1 = {3, 240 , 1294 , 595 } ;

    SDL_Rect zone2_sp1 = {25,15,135,200};
    SDL_Rect zone2_sp2 = {180,15,135,200};
    SDL_Rect zone2_sp3 = {333,15,135,200};
    SDL_Rect zone2_sp4 = {496,15,135,200};

    SDL_Rect zone3_sp1 = {674,15,135,200};
    SDL_Rect zone3_sp2 = {831,15,135,200};
    SDL_Rect zone3_sp3 = {988,15,135,200};
    SDL_Rect zone3_sp4 = {1145,15,135,200};

    SDL_Rect zone1_sp1 = {25,250,135,600};
    SDL_Rect zone1_sp2 = {180,250,135,600};
    SDL_Rect zone1_sp3 = {333,250,135,600};
    SDL_Rect zone1_sp4 = {496,250,135,600};
    SDL_Rect zone1_sp5 = {674,250,135,600};
    SDL_Rect zone1_sp6 = {831,250,135,600};
    SDL_Rect zone1_sp7 = {988,250,135,600};
    SDL_Rect zone1_sp8 = {1145,250,135,600};

    SDL_Rect globalRect = {0,0,135,200};

    SDL_Rect reload_Button = {635,5,30,30};

    SDL_Color backGround = {32, 106, 93, 255};
    SDL_Color zone_Color = {238,238,238};
    SDL_Color zoneIN = {162,222,150,255};

    SDL_Color backGround_Reload = {255,255,255,255};

    SDL_SetRenderTarget(windowRender,m_Texture);
    SDL_SetRenderDrawColor(windowRender , backGround.r , backGround.g , backGround.b , backGround.a);
    SDL_RenderFillRect(windowRender, &SDL_zoneMother);
    SDL_RenderClear(windowRender);
    SDL_RenderPresent(windowRender); //update Window Screen
    SDL_SetWindowIcon(window,SDL_LoadBMP("freecellicon.bmp"));

    SDL_Surface *img = NULL ;
    SDL_Surface *gameOver_img ;
    SDL_Surface *gameWin_img ;

    gameOver_img = SDL_LoadBMP("./img/gameOver.bmp");
    gameWin_img = SDL_LoadBMP("./img/gameWin.bmp");
    img = SDL_LoadBMP("./img/reload.bmp");
    SDL_Texture *texture_img = SDL_CreateTextureFromSurface(windowRender,img) ;
    SDL_Texture *texture_imgOverGame = SDL_CreateTextureFromSurface(windowRender,gameOver_img) ;
    SDL_Texture *texture_imgWinGame = SDL_CreateTextureFromSurface(windowRender,gameWin_img) ;



    drawInTexture(windowRender,m_Texture,&SDL_zone2,&zone_Color);
    drawInTexture(windowRender,m_Texture,&SDL_zone3,&zone_Color);
    drawInTexture(windowRender,m_Texture,&SDL_zone1,&zone_Color);

    drawInTexture(windowRender,m_Texture,&zone2_sp1,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone2_sp2,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone2_sp3,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone2_sp4,&zoneIN);



    drawInTexture(windowRender,m_Texture,&zone3_sp1,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone3_sp2,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone3_sp3,&zoneIN);
    drawInTexture(windowRender,m_Texture,&zone3_sp4,&zoneIN);


    SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);



    SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
    SDL_SetRenderTarget(windowRender, NULL);

    createCarteCouer(windowRender,&globalRect,caretCoeur);
    createCarteCarreau(windowRender,&globalRect,carteCarreau);
    createCarteTrefle(windowRender,&globalRect,carteTrefle);
    createCartePique(windowRender,&globalRect,cartePique);

    carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
    carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

    SDL_RenderPresent(windowRender);

    Element *get_carte = NULL ;
    Element *zone2_carte1 = NULL , *zone2_carte2 = NULL , *zone2_carte3 = NULL , *zone2_carte4 = NULL ;

    Element *zone3_carte1 = NULL , *zone3_carte2 = NULL , *zone3_carte3 = NULL , *zone3_carte4 = NULL ;
    Liste *zoneToAdd = NULL ;
    Element *carteZone2OnMove = NULL ;
    Uint32 frameStart;
    int frameTime ;
    int zone2Number = 0 ;

    while(1)
    {

        SDL_WaitEvent(&windowEvent);
        frameStart = SDL_GetTicks();

        if(windowEvent.type == SDL_QUIT)
        {
            break ;
        }
        if(windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp1.x && windowEvent.motion.x <=zone1_sp1.x+zone1_sp1.w  && windowEvent.motion.y >= zone1_sp1.y && windowEvent.motion.y <= zone1_sp1.y+zone1_sp1.h )
        {
            get_carte = deletLastCarte(&zone1[0]);
            zoneToAdd = zone1[0];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp2.x && windowEvent.motion.x <=zone1_sp2.x+zone1_sp2.w  && windowEvent.motion.y >= zone1_sp2.y && windowEvent.motion.y <= zone1_sp2.y+zone1_sp2.h )
        {
            get_carte = deletLastCarte(&zone1[1]);
            zoneToAdd = zone1[1];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp3.x && windowEvent.motion.x <=zone1_sp3.x+zone1_sp3.w  && windowEvent.motion.y >= zone1_sp3.y && windowEvent.motion.y <= zone1_sp3.y+zone1_sp3.h )
        {
            get_carte = deletLastCarte(&zone1[2]);
            zoneToAdd = zone1[2];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp4.x && windowEvent.motion.x <=zone1_sp4.x+zone1_sp4.w  && windowEvent.motion.y >= zone1_sp4.y && windowEvent.motion.y <= zone1_sp4.y+zone1_sp4.h )
        {
            get_carte = deletLastCarte(&zone1[3]);
            zoneToAdd = zone1[3];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp5.x && windowEvent.motion.x <=zone1_sp5.x+zone1_sp5.w  && windowEvent.motion.y >= zone1_sp5.y && windowEvent.motion.y <= zone1_sp5.y+zone1_sp5.h )
        {
            get_carte = deletLastCarte(&zone1[4]);
            zoneToAdd = zone1[4];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp6.x && windowEvent.motion.x <=zone1_sp6.x+zone1_sp6.w  && windowEvent.motion.y >= zone1_sp6.y && windowEvent.motion.y <= zone1_sp6.y+zone1_sp6.h )
        {
            get_carte = deletLastCarte(&zone1[5]);
            zoneToAdd = zone1[5];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp7.x && windowEvent.motion.x <=zone1_sp7.x+zone1_sp7.w  && windowEvent.motion.y >= zone1_sp7.y && windowEvent.motion.y <= zone1_sp7.y+zone1_sp7.h )
        {
            get_carte = deletLastCarte(&zone1[6]);
            zoneToAdd = zone1[6];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone1_sp8.x && windowEvent.motion.x <=zone1_sp8.x+zone1_sp8.w  && windowEvent.motion.y >= zone1_sp8.y && windowEvent.motion.y <= zone1_sp8.y+zone1_sp8.h )
        {
            get_carte = deletLastCarte(&zone1[7]);
            zoneToAdd = zone1[7];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone2_sp1.x && windowEvent.motion.x <=zone2_sp1.x+zone2_sp1.w  && windowEvent.motion.y >= zone2_sp1.y && windowEvent.motion.y <= zone2_sp1.y+zone2_sp1.h )
        {
            get_carte = deletLastCarte(&zone2[0]);
            zone2_carte1 = NULL ;
            zone2Number = 1 ;
            zoneToAdd = zone2[0];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone2_sp2.x && windowEvent.motion.x <=zone2_sp2.x+zone2_sp2.w  && windowEvent.motion.y >= zone2_sp2.y && windowEvent.motion.y <= zone2_sp2.y+zone2_sp2.h )
        {
            get_carte = deletLastCarte(&zone2[1]);
            zone2_carte2 = NULL ;
            zone2Number = 2 ;
            zoneToAdd = zone2[1];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone2_sp3.x && windowEvent.motion.x <=zone2_sp3.x+zone2_sp3.w  && windowEvent.motion.y >= zone2_sp3.y && windowEvent.motion.y <= zone2_sp3.y+zone2_sp3.h )
        {
            get_carte = deletLastCarte(&zone2[2]);
            zone2_carte3 = NULL ;
            zone2Number = 3 ;
            zoneToAdd = zone2[2];
        }
        else if (windowEvent.type == SDL_MOUSEBUTTONDOWN&&windowEvent.motion.x >= zone2_sp4.x && windowEvent.motion.x <=zone2_sp4.x+zone2_sp4.w  && windowEvent.motion.y >= zone2_sp4.y && windowEvent.motion.y <= zone2_sp4.y+zone2_sp4.h )
        {
            get_carte = deletLastCarte(&zone2[3]);
            zone2_carte4 = NULL ;
            zone2Number = 4 ;
            zoneToAdd = zone2[3];
        }

        //********************************************************************
        if(windowEvent.type == SDL_MOUSEBUTTONDOWN && windowEvent.motion.x >= reload_Button.x && windowEvent.motion.x <=reload_Button.x+reload_Button.w  && windowEvent.motion.y >= reload_Button.y && windowEvent.motion.y <= reload_Button.y+reload_Button.h )
        {
            zone1 = initializeZone(8);
            zone2 = initializeZone(4);
            zone3 = initializeZone(4);
            goto start ;
        }
        if((windowEvent.motion.state & SDL_BUTTON_LEFT)&&get_carte!=NULL  )
        {

            SDL_RenderClear(windowRender);

            SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
            SDL_SetRenderTarget(windowRender,NULL);

            carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

            carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
            carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

            setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
            setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
            setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
            setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

            SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);

            createMovingCarte(windowRender,get_carte,windowEvent.motion.x-70,windowEvent.motion.y-70,caretCoeur,carteCarreau,carteTrefle,cartePique);
            SDL_RenderPresent(windowRender);
        }
        if(windowEvent.type == SDL_MOUSEBUTTONUP && get_carte != NULL )
        {
            if(windowEvent.motion.x >= zone1_sp1.x && windowEvent.motion.x <= zone1_sp1.x+zone1_sp1.w&& windowEvent.motion.y >= zone1_sp1.y && windowEvent.motion.y <= zone1_sp1.y+zone1_sp1.h&& checkToReplace(get_carte,zone1[0]->last)==1)
            {
                push(zone1[0],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp2.x && windowEvent.motion.x <= zone1_sp2.x+zone1_sp2.w&& windowEvent.motion.y >= zone1_sp2.y && windowEvent.motion.y <= zone1_sp2.y+zone1_sp2.h && checkToReplace(get_carte,zone1[1]->last)==1)
            {
                push(zone1[1],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);

            }
            else if(windowEvent.motion.x >= zone1_sp3.x && windowEvent.motion.x <= zone1_sp3.x+zone1_sp3.w&& windowEvent.motion.y >= zone1_sp3.y && windowEvent.motion.y <= zone1_sp3.y+zone1_sp3.h&& checkToReplace(get_carte,zone1[2]->last)==1)
            {
                push(zone1[2],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp4.x && windowEvent.motion.x <= zone1_sp4.x+zone1_sp4.w&& windowEvent.motion.y >= zone1_sp4.y && windowEvent.motion.y <= zone1_sp4.y+zone1_sp4.h&& checkToReplace(get_carte,zone1[3]->last)==1)
            {
                push(zone1[3],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp5.x && windowEvent.motion.x <= zone1_sp5.x+zone1_sp5.w&& windowEvent.motion.y >= zone1_sp5.y && windowEvent.motion.y <= zone1_sp5.y+zone1_sp5.h&& checkToReplace(get_carte,zone1[4]->last)==1)
            {
                push(zone1[4],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp6.x && windowEvent.motion.x <= zone1_sp6.x+zone1_sp6.w&& windowEvent.motion.y >= zone1_sp6.y && windowEvent.motion.y <= zone1_sp6.y+zone1_sp6.h&& checkToReplace(get_carte,zone1[5]->last)==1)
            {
                push(zone1[5],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp7.x && windowEvent.motion.x <= zone1_sp7.x+zone1_sp7.w&& windowEvent.motion.y >= zone1_sp7.y && windowEvent.motion.y <= zone1_sp7.y+zone1_sp7.h&& checkToReplace(get_carte,zone1[6]->last)==1)
            {
                push(zone1[6],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone1_sp8.x && windowEvent.motion.x <= zone1_sp8.x+zone1_sp8.w&& windowEvent.motion.y >= zone1_sp8.y && windowEvent.motion.y <= zone1_sp8.y+zone1_sp8.h&& checkToReplace(get_carte,zone1[7]->last)==1)
            {
                push(zone1[7],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone2_sp1.x && windowEvent.motion.x <= zone2_sp1.x+zone2_sp1.w&& windowEvent.motion.y >= zone2_sp1.y && windowEvent.motion.y <= zone2_sp1.y+zone2_sp1.h&& zone2_carte1 == NULL)
            {

                push(zone2[0],get_carte->carte);
                zone2_carte1 = get_carte ;
                zone2Number = 0 ;
                get_carte = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone2_sp2.x && windowEvent.motion.x <= zone2_sp2.x+zone2_sp2.w&& windowEvent.motion.y >= zone2_sp2.y && windowEvent.motion.y <= zone2_sp2.y+zone2_sp2.h&& zone2_carte2 == NULL)
            {
                push(zone2[1],get_carte->carte);
                zone2_carte2 = get_carte ;
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone2_sp3.x && windowEvent.motion.x <= zone2_sp3.x+zone2_sp3.w&& windowEvent.motion.y >= zone2_sp3.y && windowEvent.motion.y <= zone2_sp3.y+zone2_sp3.h&& zone2_carte3 == NULL)
            {
                push(zone2[2],get_carte->carte);
                zone2_carte3 = get_carte ;
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone2_sp4.x && windowEvent.motion.x <= zone2_sp4.x+zone2_sp4.w&& windowEvent.motion.y >= zone2_sp4.y && windowEvent.motion.y <= zone2_sp4.y+zone2_sp4.h&& zone2_carte4 == NULL)
            {
                push(zone2[3],get_carte->carte);
                zone2_carte4 = get_carte ;
                zone2Number = 0 ;
                get_carte = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone3_sp1.x && windowEvent.motion.x <= zone3_sp1.x+zone3_sp1.w&& windowEvent.motion.y >= zone3_sp1.y && windowEvent.motion.y <= zone3_sp1.y+zone3_sp1.h  && ( checkFirstCarteBase(zone3[0]->last,get_carte)==0 || checkFirstCarteBase(zone3[0]->last,get_carte)==1 ))
            {
                push(zone3[0],get_carte->carte);
                zone2Number = 0 ;
                get_carte = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone3_sp2.x && windowEvent.motion.x <= zone3_sp2.x+zone3_sp2.w&& windowEvent.motion.y >= zone3_sp2.y && windowEvent.motion.y <= zone3_sp2.y+zone3_sp2.h && ( checkFirstCarteBase(zone3[1]->last,get_carte)==0 || checkFirstCarteBase(zone3[1]->last,get_carte)==1 ))
            {
                push(zone3[1],get_carte->carte);
                zone2Number = 0 ;
                get_carte = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone3_sp3.x && windowEvent.motion.x <= zone3_sp3.x+zone3_sp3.w&& windowEvent.motion.y >= zone3_sp3.y && windowEvent.motion.y <= zone3_sp3.y+zone3_sp3.h && ( checkFirstCarteBase(zone3[2]->last,get_carte)==0 || checkFirstCarteBase(zone3[2]->last,get_carte)==1 )  )
            {
                push(zone3[2],get_carte->carte);
                zone2Number = 0 ;
                get_carte = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else if(windowEvent.motion.x >= zone3_sp4.x && windowEvent.motion.x <= zone3_sp4.x+zone3_sp4.w&& windowEvent.motion.y >= zone3_sp4.y && windowEvent.motion.y <= zone3_sp4.y+zone3_sp4.h && ( checkFirstCarteBase(zone3[3]->last,get_carte)==0 || checkFirstCarteBase(zone3[3]->last,get_carte)==1 ) )
            {
                push(zone3[3],get_carte->carte);
                get_carte = NULL ;
                zone2Number = 0 ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            else
            {
                if(zone2Number==1)
                {
                    zone2_carte1 = get_carte;
                }
                else if(zone2Number==2)
                {
                    zone2_carte2 = get_carte;
                }
                else if(zone2Number==3)
                {
                    zone2_carte3 = get_carte;
                }
                else if(zone2Number==4)
                {
                    zone2_carte4 = get_carte;
                }

                push(zoneToAdd,get_carte->carte);

                zone2Number = 0 ;
                get_carte = NULL ;
                zoneToAdd = NULL ;
                SDL_RenderClear(windowRender);

                SDL_RenderCopy(windowRender, m_Texture, &SDL_zoneMother, &SDL_zoneMother);
                SDL_SetRenderTarget(windowRender,NULL);

                carte_model(windowRender,&zone1_sp1,zone1[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp2,zone1[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp3,zone1[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp4,zone1[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp5,zone1[4],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp6,zone1[5],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp7,zone1[6],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone1_sp8,zone1[7],caretCoeur,carteCarreau,carteTrefle,cartePique);

                carte_model(windowRender,&zone2_sp1,zone2[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp2,zone2[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp3,zone2[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                carte_model(windowRender,&zone2_sp4,zone2[3],caretCoeur,carteCarreau,carteTrefle,cartePique);

                setBaseCarte(windowRender,&zone3_sp1,zone3[0],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp2,zone3[1],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp3,zone3[2],caretCoeur,carteCarreau,carteTrefle,cartePique);
                setBaseCarte(windowRender,&zone3_sp4,zone3[3],caretCoeur,carteCarreau,carteTrefle,cartePique);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);
                SDL_RenderPresent(windowRender);
            }
            if(zone3[0]->last != NULL && zone3[1]->last != NULL && zone3[2]->last != NULL && zone3[3]->last != NULL && zone3[0]->last->carte->number==13 && zone3[1]->last->carte->number==13 && zone3[2]->last->carte->number==13 && zone3[3]->last->carte->number==13 )
            {
                printf("win");
                SDL_RenderClear(windowRender);
                SDL_RenderCopy(windowRender, texture_imgWinGame, NULL, &SDL_zoneMother);

                SDL_SetRenderDrawColor(windowRender , backGround_Reload.r , backGround_Reload.g , backGround_Reload.b , backGround_Reload.a);
                SDL_SetRenderTarget(windowRender,texture_img) ;
                SDL_RenderFillRect(windowRender, &reload_Button);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);

                SDL_SetRenderTarget(windowRender,NULL);
                zone1 = initializeZone(8);
                zone2 = initializeZone(4);
                zone3 = initializeZone(4);
                SDL_RenderPresent(windowRender);
            }
            if(gameOver(zone1,zone2,zone3)==1)
            {
                printf("game over");
                SDL_RenderClear(windowRender);
                SDL_RenderCopy(windowRender, texture_imgOverGame, NULL, &SDL_zoneMother);

                SDL_SetRenderDrawColor(windowRender , backGround_Reload.r , backGround_Reload.g , backGround_Reload.b , backGround_Reload.a);
                SDL_SetRenderTarget(windowRender,texture_img) ;
                SDL_RenderFillRect(windowRender, &reload_Button);
                SDL_RenderCopy(windowRender, texture_img, NULL, &reload_Button);

                SDL_SetRenderTarget(windowRender,NULL);
                zone1 = initializeZone(8);
                zone2 = initializeZone(4);
                zone3 = initializeZone(4);
                SDL_RenderPresent(windowRender);

            }

        }
    }

    SDL_DestroyRenderer(windowRender);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


