#include "maBiblio.h"



t_jeu attaque(BITMAP * buffer,BITMAP * Font[120],t_jeu partie){
    int x=0, y=0, i=0,k=0;
    int r = partie.joueur[partie.tour].Range;
    int alea=0, variation=0;

    //récup et conversion des pos souris
    convertirPosMouse_PosLARGEPlateau2(&x, &y);

    //vérification de si la case est ds la range du joueur
    if((mouse_b&1) && (estenRange(x, y, partie.joueur[partie.tour].x, partie.joueur[partie.tour].y, r)==1)){
        while(mouse_b&1);
        //parcours du tableau de joueur pr voir si un joueur est sur la case cliquée
        for(i=0; i<partie.nbJoueurs; i++){

            //si un joueur est sur la case
            if((partie.joueur[i].x == x) && (partie.joueur[i].y == y)){
                switch (partie.joueur[partie.tour].typeAction){

                    //cas corps à corps
                    case 1:
                        //coute 2 pt d'action au joueur et vie de l'autre diminué (1/10 d'échouer, 1 nb qui échoue), inflige tjrs la valeur de base
                        if(partie.joueur[partie.tour].PA >= 2){
                            partie.joueur[partie.tour].PA = partie.joueur[partie.tour].PA - 2;
                            alea = rand()%(10-1+1)+1;
                            if(!(alea==1)){
                                partie.joueur[i].PV = partie.joueur[i].PV - partie.joueur[partie.tour].classe.corpsacorps;
                                animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.corpsacorps);
                                ///si les pv du joueur touché tombe à 0 le déclarer mort
                                if((partie.joueur[i].PV)<=0){
                                    partie.joueur[i].estMort = 1;
                                    animationMort(buffer,partie,i);
                                    for(k=partie.nbJoueurs-1;k>=0;k--){
                                        if(partie.rankTab[k] == -1){
                                            partie.rankTab[k] = i;
                                            partie.joueur[i].podium = k;
                                            break;
                                        }
                                    }
                                }

                            }
                            else{
                                ///print qq part sur l'écran que l'attaque à échouée
                                animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,0);
                            }
                        }

                        break;

                    //cas de guérison (sort[0])
                    case 2:
                        //coute 5PA et a une chance sur 7 d'échouer, (2/8 de resituer que la moitié, 5/8 de restituer la valeur initiale, 1/8 de restituer le double de vie
                        if(partie.joueur[partie.tour].PA >= 5){
                            partie.joueur[partie.tour].PA = partie.joueur[partie.tour].PA - 5;
                            alea = rand()%(7-1+1)+1;
                            variation = rand()%(8-1+1)+1;
                            if(!(alea==1)){
                                //restitue la vie (valeur du sort classique)
                                if(variation==3 || variation==4 || variation==5 || variation==6 || variation==7){
                                    partie.joueur[partie.tour].PV = partie.joueur[partie.tour].PV + partie.joueur[partie.tour].classe.sorts[0];
                                    //si les pv du joueur dépasse les pv de base de sa classe
                                    if(partie.joueur[partie.tour].PV > partie.joueur[partie.tour].classe.PV_default){
                                        partie.joueur[partie.tour].PV = partie.joueur[partie.tour].classe.PV_default;
                                    }
                                    animationGuerison(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.sorts[0]);
                                }
                                //restitue seulement la moitiée de la vie
                                else if (variation==1 || variation==2){
                                    partie.joueur[partie.tour].PV = partie.joueur[partie.tour].PV + (partie.joueur[partie.tour].classe.sorts[0])/2;
                                    //si les pv du joueur dépasse les pv de base de sa classe
                                    if(partie.joueur[partie.tour].PV > partie.joueur[partie.tour].classe.PV_default){
                                        partie.joueur[partie.tour].PV = partie.joueur[partie.tour].classe.PV_default;
                                    }
                                    animationGuerison(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.sorts[0]/2);
                                }
                                //restitue le double de la vie (valeur sort initiale *2)
                                else if(variation==8){
                                    partie.joueur[partie.tour].PV = partie.joueur[partie.tour].PV + (partie.joueur[partie.tour].classe.sorts[0])*2;
                                    //si les pv du joueur dépasse les pv de base de sa classe
                                    if(partie.joueur[partie.tour].PV > partie.joueur[partie.tour].classe.PV_default){
                                        partie.joueur[partie.tour].PV = partie.joueur[partie.tour].classe.PV_default;
                                    }
                                    animationGuerison(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.sorts[0]*2);
                                }
                            }
                            else{
                                ///afficher sur l'écran que la guérison à échoué
                                //animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationGuerison(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,0);
                            }
                        }
                        break;

                    //cas d'une attaque proche (damage[0])
                    case 3:
                        //coute 3PA et a 1/15 d'échouer (1/10 d'infliger le double des dégats, 2/10 d'infliger plus la moitiée des dégats, 2/10 d'infliger moins la moitiée des dégats, 5/10 d'infliger les dégats initiaux)
                        if(partie.joueur[partie.tour].PA >= 3){
                            partie.joueur[partie.tour].PA = partie.joueur[partie.tour].PA - 3;
                            alea = rand()%(15-1+1)+1;
                            variation = rand()%(10-1+1)+1;
                            if(!(alea==1)){
                                //degat de base fois 2
                                if(variation==1){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[0])*2;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[0])*2);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                //degat - la moitié des dégats
                                else if(variation==2 || variation==3){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[0])/2;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[0])/2);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==4 || variation==5){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[0])*1.5;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[0])*1.5);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==6 || variation==7 || variation==8 || variation==9 || variation==10){
                                    partie.joueur[i].PV = partie.joueur[i].PV - partie.joueur[partie.tour].classe.damage[0];
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.damage[0]);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                            else{
                                ///afficher écran
                                animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,0);
                            }
                        }
                        break;
                    case 4:
                        if(partie.joueur[partie.tour].PA >= 4){
                                                        //coute 4PA et a 1/15 d'échouer (1/10 d'infliger le double des dégats, 2/10 d'infliger plus la moitiée des dégats, 2/10 d'infliger moins la moitiée des dégats, 5/10 d'infliger les dégats initiaux)
                            partie.joueur[partie.tour].PA = partie.joueur[partie.tour].PA - 4;
                            alea = rand()%(15-1+1)+1;
                            variation = rand()%(10-1+1)+1;
                            if(!(alea==1)){
                                //degat de base fois 2
                                if(variation==1){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[1])*2;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[1])*2);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                //degat - la moitié des dégats
                                else if(variation==2 || variation==3){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[1])/2;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[1])/2);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==4 || variation==5){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.damage[1])*1.5;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.damage[1])*1.5);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==6 || variation==7 || variation==8 || variation==9 || variation==10){
                                    partie.joueur[i].PV = partie.joueur[i].PV - partie.joueur[partie.tour].classe.damage[1];
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.damage[1]);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                            else{
                                animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,0);
                            }

                        }
                        break;
                    case 5:
                        //coute 6PA a 1/7 d'échouer (6/9 degats initiaux, 2/9 - moitié degats, 1/9 + moitié degats)
                        if(partie.joueur[partie.tour].PA >= 6){
                            partie.joueur[partie.tour].PA = partie.joueur[partie.tour].PA - 6;
                            alea = rand()%(7-1+1)+1;
                            variation = rand()%(9-1+1)+1;
                            if(!(alea==1)){
                                if(variation==1){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.sorts[1])*1.5;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.sorts[1])*1.5);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==2 || variation==3){
                                    partie.joueur[i].PV = partie.joueur[i].PV - (partie.joueur[partie.tour].classe.sorts[1])/2;
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,(partie.joueur[partie.tour].classe.sorts[1])/2);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if(variation==4 || variation==5 || variation==6 || variation==7 || variation==8 || variation==9){
                                    partie.joueur[i].PV = partie.joueur[i].PV - partie.joueur[partie.tour].classe.sorts[1];
                                    animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                    animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,partie.joueur[partie.tour].classe.sorts[1]);
                                    if((partie.joueur[i].PV)<=0){
                                        partie.joueur[i].estMort = 1;
                                        animationMort(buffer,partie,i);
                                        for(k=partie.nbJoueurs-1;k>=0;k--){
                                                if(partie.rankTab[k] == -1){
                                                partie.rankTab[k] = i;
                                                partie.joueur[i].podium = k;
                                                break;
                                            }
                                        }
                                    }
                                }

                            }
                            else{
                                animationAttaque(buffer,partie,partie.joueur[i].x, partie.joueur[i].y);
                                animationPerteVie(buffer,Font,partie,partie.joueur[i].x, partie.joueur[i].y,0);
                            }


                        }
                        break;
                }
            }
        }

    }

    return partie;
}



///FAIRE ANIMATION PROJECTILE




void animationAttaque(BITMAP * buffer, t_jeu regl, int dx,int dy){
    int i;
    int x, y;
    int xdess, ydess;
    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(temp);
    x = regl.joueur[regl.tour].x;
    y = regl.joueur[regl.tour].y;
    convertirPosLARGEPlateau_RealPos2(&xdess, &ydess, x, y);
    xdess-=60;
    ydess -=52;
    if(dx > x ){
        if(dy > y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueSO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
        if(dy<y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueSO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
        if(dy==y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueSO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
    }


    if(dx<x){
        if(dy > y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueNO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
        if(dy<y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueNO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }

        }
        if(dy==y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueNO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
    }
    if(dx==x){
        if(dy > y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueSO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
        if(dy<y){
            for(i=0;i<regl.tabClasses[regl.joueur[regl.tour].classe.type].nbAnimationsAttaque;i++){
                rest(100);
                clear_bitmap(temp);
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].attaqueNO[i],xdess,ydess);
                blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
            }
        }
    }
    destroy_bitmap(temp);

}



void animationPerteVie(BITMAP * buffer,BITMAP * Font[120],t_jeu regl, int dx, int dy, int degats){
    BITMAP * temp = create_bitmap(SCREEN_W, SCREEN_H);
    float coef;
    int i;
    int xdess, ydess;
    char mot[10];
    sprintf(mot, "-%d", degats);
    if(degats == 0){
        sprintf(mot,"Rate");
    }
    for(i=100;i>=50;i--){
        rest(1);
        clear_bitmap(temp);
        coef = (float)i/(float)100;
        blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);

        affichageJoueurActuel(temp,regl);

        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,dx,dy);
        printTEXT(temp,Font,mot, xdess+30, ydess-50,coef);

        blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }
    destroy_bitmap(temp);
}



void animationGuerison(BITMAP * buffer,BITMAP * Font[120],t_jeu regl, int dx, int dy, int degats){
    BITMAP * temp = create_bitmap(SCREEN_W, SCREEN_H);
    float coef;
    int i;
    int xdess, ydess;
    char mot[10];
    sprintf(mot, "+%d", degats);
    if(degats == 0){
        sprintf(mot,"Rate");
    }
    for(i=100;i>=50;i--){
        rest(1);
        clear_bitmap(temp);
        coef = (float)i/(float)100;
        blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);

        affichageJoueurActuel(temp,regl);

        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,dx,dy);
        printTEXT(temp,Font,mot, xdess+30, ydess-50,coef);

        blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }
    destroy_bitmap(temp);
}


void animationMort(BITMAP * buffer,t_jeu regl,int indice){

    int i,j;
    int x, y;
    int xdess, ydess;
    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(temp);


    for(i=0;i<16;i++){
        rest(100);
        clear_bitmap(temp);
        blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
        masked_blit(regl.mapJeu,temp,0,0,0,0,SCREEN_W,SCREEN_H);
        for(j=0;j<regl.nbJoueurs;j++){
            if(j!=indice && regl.joueur[j].x>=0 && regl.joueur[j].x<16 && regl.joueur[j].y >= 0 && regl.joueur[j].y <16){
                convertirPosLARGEPlateau_RealPos2(&x,&y,regl.joueur[j].x,regl.joueur[j].y);
                draw_sprite(temp,regl.tabClasses[regl.joueur[j].classe.type].animSO[0], x-60,y-52);
            }
        }
        x = regl.joueur[indice].x;
        y = regl.joueur[indice].y;
        convertirPosLARGEPlateau_RealPos2(&xdess, &ydess, x, y);
        xdess-=60;
        ydess -=52;
        draw_sprite(temp,regl.tabClasses[regl.joueur[indice].classe.type].mort[i],xdess,ydess);
        blit(temp,screen, 0,0,0,0,SCREEN_W,SCREEN_H);
    }


    destroy_bitmap(temp);
}
