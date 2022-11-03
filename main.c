#include "maBiblio.h"



int main()
{
    int i,j,cptJoueursRestants;
    srand(time(NULL));


    basicInit();
    BITMAP * buffer;

    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP * cursor = load_bitmap("mouse.bmp",NULL);
    BITMAP * RoueCrantee = load_bitmap("parametres/roueCrantee.bmp", NULL);

    ///initialisation ATH
    BITMAP * ath_collision;
    ath_collision = create_bitmap(SCREEN_W, SCREEN_H);
    init_ATH(ath_collision);

    ///intitalisation hitmap map
    BITMAP * map_collision;
    map_collision = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(map_collision);
    init_MAPCollPlateau(map_collision);


    int rejouer = 1;    //1 si le joueur veut rejouer avec les mêmes caractéristiques 0 sinon
    int choixFin = 0;
    t_jeu regl;

    regl.affichage = 1;
    regl.enJeu = 0;
    regl.sampl.freq = 1000;
    regl.sampl.vol = 255;
    regl.sampl.loop = 10;
    regl.sampl.pan = 128;
    regl.sampl.xm = 790;
    regl.sampl.on = 1;
    regl.fermerParam = 0;
    regl.quit = 0;

    regl.mapJeu = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(regl.mapJeu);
    floodfill(regl.mapJeu,1,1,makecol(255,0,255));

    BITMAP * Font[120];

    initFont(Font);


    //SAMPLE* loadingmusic = load_sample("menu/One Piece - Whitebeard Theme (Most Epic Theme).wav");

    startAnimation(buffer);

    regl.quit = 0;
    while(regl.quit == 0){
        ///MENU DU DEBUT
        regl = startMenu(buffer,Font, regl);
        if(regl.choixMenu == 1){

            ///Initialisation des joueurs
            regl = initialisation_complete(Font, regl);
            regl = initTabObstacles(regl);
            regl = initMapJeu(regl);
            regl = initPositions(cursor,Font,map_collision,regl);
            regl.tour = rand()%(regl.nbJoueurs) -1;
            if(regl.tour>=regl.nbJoueurs || regl.tour<0){
                regl.tour = 0;
            }
            regl.rankTab = (int*)malloc(regl.nbJoueurs*sizeof(int));
            for(i=0;i<regl.nbJoueurs;i++){
                regl.rankTab[i] = -1;
                regl.joueur[i].podium = -1;
            }
        }
        else if(regl.choixMenu == 2){
            int sauv;
            selec_charg(&sauv, Font);
            regl = initTabObstacles(regl);
            regl = initMapJeu(regl);
            regl = chargementGlobal(regl, sauv);
            regl.quit = 0;

        }
        else if(regl.choixMenu == 0){
            allegro_exit();
            return 0;
        }
        while(mouse_b&1);  //attente du relachement de la souris pour éviter les bugs

        regl.attendreScore = 1;
        rejouer = 1;
        regl.quit =0;

        regl.attendreScore = 1;
        while(rejouer == 1){
            ///pour initialiser les joueurs
            regl.enJeu = 1;
            regl.attendreScore = 1;
            regl = remplissageDesPouvoir_etProfil(regl,regl.mapJeu);
            regl.chrono.prevtime = clock();
            //regl.sampl.smpl = load_sample("menu/musiqueJeu.wav");
            if(!regl.sampl.smpl){
                allegro_message("le sample");
            }
            //play_sample(regl.sampl.smpl,regl.sampl.vol,regl.sampl.pan,regl.sampl.freq,regl.sampl.loop);
            while(regl.enJeu == 1){

                if(regl.sampl.loop <=10)
                    regl.sampl.loop++;
                regl.chrono.timer = clock();
                ///Boucle de jeu
                cptJoueursRestants = 0;
                for(i = 0;i<regl.nbJoueurs;i++){
                    if(regl.joueur[i].estMort == 0){
                        cptJoueursRestants ++;
                    }
                }
                if(cptJoueursRestants == 1){
                    regl.enJeu = 0;
                    regl.rankTab[0] = regl.tour;
                    regl.joueur[regl.tour].podium = 0;
                }


                clear_bitmap(buffer);

                ///refresh de la range
                regl = refreshRange(regl);


                ///CHOISI LE TYPE D'ACTION

                affichage_livre(regl.mapJeu,ath_collision,regl,Font);


                regl = detectionTypeAction_etProfil(ath_collision,regl);

                affichage_boutons_selection(regl,regl.mapJeu,ath_collision,buffer);



                //affichage_LARGEgrille2(buffer);



                ///afficher la barre de vie, les PV, PA et PM
                afficher_carac_autres_joueurs(buffer,Font,regl);

                ///affichage de la grille
                masked_blit(regl.mapJeu,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

                ///affichage des boutons
                touche_bouton(buffer,ath_collision,regl,Font);


                ///pour afficher la range disponible ou non
                affichageRange(buffer,regl);

                ///afficher les autres joueurs
                affichageAutresJoueurs(buffer,regl,regl.nbJoueurs);



                for(i=0;i<regl.nbJoueurs;i++){
                    regl.joueur[i].x = regl.joueur[i].dx;
                    regl.joueur[i].y = regl.joueur[i].dy;
                }

                  ///deplacement
                if(mouse_b&1 && deplacementPossible(map_collision,regl) && regl.joueur[regl.tour].typeAction == 0){       //si le déplacement est possible
                        convertirPosMouse_PosLARGEPlateau2(&regl.joueur[regl.tour].dx,&regl.joueur[regl.tour].dy);  //et on les transformes en coord plateau
                        while(mouse_b&1);
                }

                ///Affichage du déplacement si il y en a un
                regl = deplacement(buffer,regl);


                ///pour l'attaque
                regl = attaque(buffer,Font,regl);


                ///pour afficher le joueur a sa position actuelle
                affichageJoueurActuel(buffer,regl);
                //affichage_LARGEcaseDeplacement(buffer,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y)



                ///Afficher roue crantée
                masked_blit(RoueCrantee, buffer, 0,0,1240,0,RoueCrantee->w,RoueCrantee->h);
                //afficage de la souris et du buffer


                 ///SUIVANT
                if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(155,0,155)&&( mouse_b&1)) || regl.chrono.chrono >= 30)
                {
                    regl.tour +=1;
                    if(regl.tour>= regl.nbJoueurs){
                        regl.tour = 0;
                    }
                    while(regl.joueur[regl.tour].estMort == 1){
                        regl.joueur[regl.tour].x = -1;
                        regl.joueur[regl.tour].y = -1;
                        regl.joueur[regl.tour].dx = -1;
                        regl.joueur[regl.tour].dy = -1;
                        regl.tour +=1;
                        if(regl.tour>= regl.nbJoueurs){
                            regl.tour = 0;
                        }
                    }
                    regl.joueur[regl.tour].PM = regl.joueur[regl.tour].classe.PM_default;
                    //printf("\n%d\n", regl.joueur[regl.tour].classe.PM_default);
                    regl.joueur[regl.tour].PA = regl.joueur[regl.tour].classe.PA_default;
                    regl=remplissageDesPouvoir_etProfil(regl,regl.mapJeu);
                    while(mouse_b&1);
                    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
                    while(!key[KEY_ENTER] && !(mouse_b&1 && mouse_x>45 && mouse_x<295 && mouse_y>575 && mouse_y<600)){
                        blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
                        printTEXT(temp,Font,"C'est a toi de jouer ",50,550,0.6);
                        printTEXT(temp,Font,regl.joueur[regl.tour].nom,330,550,0.6);
                        round_rect(temp,45,575,250,25,3,2,makecol(187,97,0), makecol(0,121,175));
                        printTEXT(temp,Font,"Continuer [ENTRER]", 50,575,0.6);
                        masked_blit(cursor,temp,0,0,mouse_x,mouse_y,13,19);
                        blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    }
                    destroy_bitmap(temp);
                    regl.chrono.prevtime = clock();
                }
                ///Parametres
                if((mouse_b&1 && mouse_x>=1240 && mouse_x<=1280 && mouse_y <=40) || key[KEY_ESC]){
                    while(key[KEY_ESC]);
                    while(mouse_b&1);
                    BITMAP *collVolume;
                    collVolume =create_bitmap(SCREEN_W, SCREEN_H);
                    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);


                    regl.fermerParam = 0;
                    //masked_stretch_blit(menu[0],buffer, 0,0,menu[0]->w, menu[0]->h, 0,0,SCREEN_W, SCREEN_H);
                    while(regl.fermerParam == 0){
                        regl.chrono.timer = clock();
                        clear_bitmap(temp);
                        blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);

                        regl = parametre(temp,Font,collVolume,regl);

                        masked_blit(cursor, temp, 0,0,mouse_x, mouse_y, 13,19);

                        regl = printTime(temp,regl,Font);
                        //blit(buffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);
                        blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                    }


                    destroy_bitmap(collVolume);
                    destroy_bitmap(temp);
                }


                regl = printTime(buffer,regl, Font);
                printTEXT(buffer,Font,regl.joueur[regl.tour].nom,5,140,0.8);
                masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,cursor->w,cursor->h);
                //blit(regl.joueur[regl.tour].classe.animNO[1],buffer,0,0,500,500,70,80);


                blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

            }
            stop_sample(regl.sampl.smpl);
            destroy_sample(regl.sampl.smpl);
            choixFin = 1;
            //stop_sample(regl.sampl.smpl);
            //destroy_sample(regl.sampl.smpl);
            if(regl.attendreScore == 1){
                for(i=0;i<regl.nbJoueurs;i++){
                    regl.rankTab[regl.joueur[i].podium] = i;
                }
                printf("\nRANKTAB\n");
                for(i=0;i<regl.nbJoueurs;i++){
                    printf("r%d : %d\n", i, regl.rankTab[i]);
                }
                for(i=0;i<regl.nbJoueurs;i++){
                    printf("%s : %d\n", regl.joueur[regl.rankTab[i]].nom,i);
                }
                choixFin = showScores(regl,buffer,Font);
                printf("\n%d\n", choixFin);
                if(choixFin == 1){
                    rejouer = 0;
                }
                if(choixFin == 2){
                    rejouer = 0;
                }
                if(choixFin == 3){
                    rejouer = 1;
                    for(i=0;i<regl.nbJoueurs;i++){
                        regl.joueur[i].PV = regl.joueur[i].classe.PV_default;
                        regl.joueur[i].PA = regl.joueur[i].classe.PA_default;
                        regl.joueur[i].PM = regl.joueur[i].classe.PM_default;
                        regl.joueur[i].podium = -1;
                    }
                    regl = initPositions(cursor,Font,map_collision,regl);
                }
            }

            if(regl.attendreScore == 0){
                rejouer = 0;
                free(regl.rankTab);
            }

        }
        regl.quit = 0;
        if(choixFin == 1){
            regl.quit = 0;
        }
        if(choixFin == 0){
            regl.quit = 1;
        }


    }

destroy_bitmap(buffer);
destroy_bitmap(RoueCrantee);
destroy_bitmap(map_collision);
destroy_bitmap(ath_collision);
destroy_bitmap(cursor);
destroy_bitmap(regl.mapJeu);

for(i=0;i<4;i++){
    for(i=0;j<16;j++){
        destroy_bitmap(regl.tabClasses[i].mort[j]);
    }
    for(j = 0;j<8;j++){
        destroy_bitmap(regl.tabClasses[i].animNO[j]);
        destroy_bitmap(regl.tabClasses[i].animSO[j]);
    }

}
allegro_exit();
return 0;

}END_OF_MAIN();
