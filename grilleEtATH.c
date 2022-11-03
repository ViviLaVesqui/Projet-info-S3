#include "maBiblio.h"




///Sert à créer la deuxième grille (type losange)
void affichage_LARGEgrille2(BITMAP * buffer){
    int i;
    int ncases = 16;
    int marge_x = 320;
    int marge_y =240;
    for(i=0;i<ncases+1;i++){
        line(buffer,i*30 +marge_x/2      ,SCREEN_H/2 + i*15     ,i*30 + 30*ncases +marge_x/2      ,marge_y/2 +i*15            ,makecol(0,255,0));
        line(buffer,i*30 +marge_x/2      ,SCREEN_H/2 - i*15     ,i*30 + 30*ncases +marge_x/2      ,SCREEN_H-marge_y/2 - i*15  ,makecol(0,255,0));
    }
}

///Sert à détécter/afficher dans quelle case on est
void detection_LARGEcase2(BITMAP * buffer){
    int x,y;    //position classique
    int xP,yP;  //position en fonction du plateau

    convertirPosMouse_PosLARGEPlateau2(&xP,&yP);
    convertirPosLARGEPlateau_RealPos2(&x,&y,xP,yP);

    ///Dessin de la zone de la case séléctionnée
    line(buffer,x,y,x-30,y+15,makecol(255,255,255));
    line(buffer,x,y,x+30,y+15,makecol(255,255,255));
    line(buffer,x-30,y+15,x,y+30,makecol(255,255,255));
    line(buffer,x,y+30,x+30,y+15,makecol(255,255,255));

    ///Décommenter ci dessous pour avoir modèle en relief
    /*
    convertirPosPlateau_RealPos2(&x,&y,xP-hauteur,yP-hauteur);

    line(buffer,x,y+30,x-60,y+30+30,makecol(255,255,255));
    line(buffer,x,y+30,x+60,y+30+30,makecol(255,255,255));
    line(buffer,x-60,y+30+30,x,y+60+30,makecol(255,255,255));
    line(buffer,x,y+30+60,x+60,y+30+30,makecol(255,255,255));

    line(buffer,x-60,y+30+30,x-60,y+90,makecol(255,255,255));
    line(buffer,x+60,y+30+30,x+60,y+90,makecol(255,255,255));
    line(buffer,x,y+60+30,x,y+120,makecol(255,255,255));
    circlefill(buffer,x, y+30+30 ,10,makecol(255,0,255));//yp+30 pour placer le cercle au centre
    */
    circlefill(buffer,x, y+15 ,10,makecol(255,0,255));//yp+30 pour placer le cercle au centre

}

///Sert à convertir la position de la souris en coordonnée plateau
void convertirPosMouse_PosLARGEPlateau2(int * x, int * y){
    *x = (int)((mouse_x+2*mouse_y-880)/60);
    *y = (int)((2*mouse_y-mouse_x+400)/60);
}

///Sert à convertir les coordonées plateau en coordonées cartésienne(coordonées classque de l'écran)
void convertirPosLARGEPlateau_RealPos2(int * x, int *y, int xPlateau, int yPlateau){  //on met en paramètre un pointeur vers la variable de coordonée cartésienne
    *x = 30*xPlateau -30*yPlateau +640 ;                                        //et les coordonées du plateau à convertir
    *y = 15*xPlateau +15*yPlateau +120;
}

///Sert à afficher les coordonées plateau où se trouve la souris
void affichage_LARGEpos2(BITMAP * buffer,BITMAP * map_collision){
    int xP,yP;
    convertirPosMouse_PosLARGEPlateau2(&xP,&yP);
    if(detection_map(map_collision)){
        textprintf(buffer,font,15,15,makecol(255,0,0),"Position Plateau %d : %d", xP, yP ); //affichage de la position en fonction du plateau
    }
    else{
        textprintf(buffer,font,15,15,makecol(255,0,0),"Position Plateau - : -"); //pas dans le plateau donc - -
    }
}

///Sert à détécter/afficher dans quelle case on est
void affichage_LARGEcaseDeplacement(BITMAP * buffer,int xP,int yP){
    int x,y;    //position classique

    convertirPosLARGEPlateau_RealPos2(&x,&y,xP,yP);

    ///Dessin de la zone de la case séléctionnée
    line(buffer,x,y,x-30,y+15,makecol(255,255,255));
    line(buffer,x,y,x+30,y+15,makecol(255,255,255));
    line(buffer,x-30,y+15,x,y+30,makecol(255,255,255));
    line(buffer,x,y+30,x+30,y+15,makecol(255,255,255));

    ///Décommenter ci dessous pour avoir modèle en relief
    /*
    convertirPosPlateau_RealPos2(&x,&y,xP-hauteur,yP-hauteur);

    line(buffer,x,y+30,x-60,y+30+30,makecol(255,255,255));
    line(buffer,x,y+30,x+60,y+30+30,makecol(255,255,255));
    line(buffer,x-60,y+30+30,x,y+60+30,makecol(255,255,255));
    line(buffer,x,y+30+60,x+60,y+30+30,makecol(255,255,255));

    line(buffer,x-60,y+30+30,x-60,y+90,makecol(255,255,255));
    line(buffer,x+60,y+30+30,x+60,y+90,makecol(255,255,255));
    line(buffer,x,y+60+30,x,y+120,makecol(255,255,255));
    circlefill(buffer,x, y+30+30 ,10,makecol(255,0,255));//yp+30 pour placer le cercle au centre
    */
    circlefill(buffer,x, y+15 ,10,makecol(255,0,255));//yp+30 pour placer le cercle au centre

}




///initialiser la map de collision de l'ATH
void init_ATH(BITMAP * buffer){
    rectfill(buffer, SCREEN_W/5, SCREEN_H-100, SCREEN_W-SCREEN_W/5, SCREEN_H,makecol(255,255,255)); //barre du bas
    round_rect(buffer, 558, SCREEN_H-71, 40, 40, 5, 2, makecol(255,0,0), makecol(255,0,0));   //bouton pour attaque corps à corps
    round_rect(buffer, 609, SCREEN_H-71, 40, 40, 5, 2, makecol(0,255,0), makecol(0,255,0)); //bouton pour guerrison
    round_rect(buffer, 660, SCREEN_H-71, 40, 40, 5, 2, makecol(0,0,255), makecol(0,0,255)); //bouton pour sort proche
    round_rect(buffer, 708, SCREEN_H-71, 40, 40, 5, 2, makecol(0,255,255), makecol(0,255,255));//bouton pour sort loin
    round_rect(buffer, 758, SCREEN_H-71, 40, 40, 5, 2, makecol(155,0,255), makecol(155,0,255));//bouton pour sort puissant
    round_rect(buffer, 810, SCREEN_H-71, 40, 40, 5, 2, makecol(255,255,0), makecol(255,255,0));//bouton pour courir
    round_rect(buffer, 925, SCREEN_H-71, 95, 35, 5, 2, makecol(155,0,155), makecol(155,0,155));//bouton pour joueur suivant



    rectfill(buffer, SCREEN_W-125, SCREEN_H/2-250,SCREEN_W-25,SCREEN_H/2+250,makecol(255,255,255));//barre des joueurs côté droit

    rectfill(buffer,SCREEN_W-225,25,SCREEN_W-25,75,makecol(255,255,255)); //barre menu en haut a droite


    rectfill(buffer,25,25,125,125,makecol(255,255,255));
    rectfill(buffer,100,15,129,42,makecol(255,155,5));//BOUTON pour regarder les carac des perso petit livre
    floodfill(buffer,SCREEN_W/2,SCREEN_H/2,makecol(255,0,255)); //juste pour la transparence afin de faciliter la visualisation lors du développement
}

///initialiser la map de collision de la carte
void init_MAPCollPlateau(BITMAP * buffer){
    int marge_x = 320;
    int marge_y =240;

    line(buffer,1 +marge_x/2      ,SCREEN_H/2      , 60*8 +1 +marge_x/2      ,marge_y/2             ,makecol(0,75,100));
    line(buffer,1 +marge_x/2      ,SCREEN_H/2      , 60*8 +1 +marge_x/2      ,SCREEN_H-marge_y/2    ,makecol(0,75,100));

    line(buffer,8*60 +marge_x/2      ,SCREEN_H/2 + 8*30     ,8*60 + 60*8 +marge_x/2      ,marge_y/2 +8*30            ,makecol(0,75,100));
    line(buffer,8*60 +marge_x/2      ,SCREEN_H/2 - 8*30     ,8*60 + 60*8 +marge_x/2      ,SCREEN_H-marge_y/2 - 8*30  ,makecol(0,75,100));

    floodfill(buffer,SCREEN_W/2,SCREEN_H/2,makecol(0,75,100));
}



///detection clique gauche dans la map 1 et 2
int detection_map(BITMAP * map_collision){ //Sert à savoir si on est dans la zone de la map
    //Retourne 1 si oui, 0 sinon.
    if(getpixel(map_collision,mouse_x,mouse_y) == makecol(0,75,100)){
        return 1;
    }
    else{
        return 0;
    }
}



/// Afficher la vies et les infos des autres joueurs pdt un tour (+nfos du joueur en cours)
void afficher_carac_autres_joueurs(BITMAP* buffer, BITMAP* police[120], t_jeu regl){
    int i=0;

    //parcours du tableau de joueurs
    for(i=0; i<regl.nbJoueurs; i++){
        //si le joueur n'est pas celui qui joue
        if(i != regl.tour && regl.joueur[i].estMort == 0){
            round_rect(buffer, 1155, 195 + 100*i, 120, 100, 10, 3, makecol(255,255,255), makecol(0,0,0));
            printTEXT(buffer, police, regl.joueur[i].nom, 1165, 200 + 105*i, 0.4);
            afficher_carac_player2(buffer, police, regl.joueur[i], 0.5, 1165, 200 + 105*i + 20);
        }
        if(i == regl.tour){
            round_rect(buffer, 1155, 195 + 100*i, 120, 100, 10, 3, makecol(255,255,255), makecol(0,0,0));
            printTEXT(buffer, police, "---", 1165, 200 + 105*i, 0.4);
            afficher_carac_player2(buffer, police, regl.joueur[i], 1, 60, 640);
        }
    }
}

void afficher_carac_player2(BITMAP* buffer, BITMAP* police[120], t_player p, float coef, int x, int y){
    // chaine pr les récupérations
    char pv[6], pa[6], pm[6];
    char pv_def[3], pa_def[3], pm_def[3];
    char pv_t[9], pa_t[9], pm_t[9];


    float ratio =  (float) p.PV / p.classe.PV_default;

    //bitmaps pr la vie
    BITMAP* coeurplein = load_bitmap("Bitmap/coeurplein.bmp", NULL);
    BITMAP* coeurvide = load_bitmap("Bitmap/coeurvide.bmp", NULL);

    //printf("rentre ss prgrm");

    //remplissage des chaines de transition
    sprintf(pv_def, "%d", p.classe.PV_default);
    sprintf(pv, "%d", p.PV);
    strcat(pv, "/");
    strcat(pv, pv_def);

    strcpy(pv_t, "PV:");
    strcat(pv_t, pv);

    sprintf(pa_def, "%d", p.classe.PA_default);
    sprintf(pa, "%d", p.PA);
    strcat(pa, "/");
    strcat(pa, pa_def);

    strcpy(pa_t, "PA:");
    strcat(pa_t, pa);

    sprintf(pm_def, "%d", p.classe.PM_default);
    sprintf(pm, "%d", p.PM);
    strcat(pm, "/");
    strcat(pm, pm_def);

    strcpy(pm_t, "PM:");
    strcat(pm_t, pm);

    //masked_blit(coeurvide, buffer, 0, 0, 410, 640, (coeurvide->w), ((1-ratio)*(coeurvide->h)));
    //masked_blit(coeurplein, buffer, 0, ((1-ratio)*(coeurplein->h)), 410, (640+(1-ratio)*(coeurvide->h)), (coeurplein->w), (ratio*(coeurplein->h)));

    masked_stretch_blit(coeurvide, buffer, 0, 0, (coeurvide->w), ((1-ratio)*(coeurvide->h)), x, y, (coeurvide->w)*coef, ((1-ratio)*(coeurvide->h))*coef);
    masked_stretch_blit(coeurplein, buffer, 0, (1-ratio)*(coeurplein->h), coeurplein->w, ratio*(coeurplein->h), x, y+(1-ratio)*(coeurvide->h)*coef, (coeurplein->w)*coef, (ratio*coeurplein->h)*coef);

    if(coef != 1.0){
        printTEXT(buffer, police, pv_t, (x + (coeurplein->w) + 10) - (coeurplein->w)*coef, y, coef-0.2);
        printTEXT(buffer, police, pa_t, (x + (coeurplein->w) + 10) - (coeurplein->w)*coef, y+20, coef-0.2);
        printTEXT(buffer, police, pm_t, (x + (coeurplein->w) + 10) - (coeurplein->w)*coef, y+40, coef-0.2);
    }
    if(coef==1){
            printTEXT(buffer, police, pv_t, (x + (coeurplein->w) + 10), y, 0.4);
            printTEXT(buffer, police, pa_t, (x + (coeurplein->w) + 10), y+20, 0.4);
            printTEXT(buffer, police, pm_t, (x + (coeurplein->w) + 10), y+40, 0.4);
    }

    destroy_bitmap(coeurplein);
    destroy_bitmap(coeurvide);
}




