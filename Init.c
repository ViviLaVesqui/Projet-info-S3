#include "maBiblio.h"






////////////////////////////
////////////////////////////

void basicInit(){

    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_uformat(U_ASCII);
    set_color_depth(desktop_color_depth());

    if((set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,1280,720,0,0))!=0){
        allegro_message("Probleme Graphique ...");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

////////////////////////////
////////////////////////////





///Sert à récupérer les classes dans un fichier
void recupfichier(t_classe tab[4]){

    FILE* fileclass = fopen("classe/classe.txt", "r"); //ouverture du fichier en lecture seule
    t_classe a;
    char nom[50];


    int i=0;
    int j=0;
    if(fileclass == NULL){
        printf("pbm ouverture");
    }
    else{
            for(i=0; i<4; i++){
                fscanf(fileclass, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &(a.type), &(a.damage[0]), &(a.damage[1]), &(a.range_damage[0]), &(a.range_damage[1]), &(a.sorts[0]), &(a.sorts[1]), &(a.range_sorts[0]), &(a.range_sorts[1]), &(a.PM_default), &(a.PV_default), &(a.PA_default),&(a.corpsacorps),&(a.nbAnimationsAttaque));
                tab[i] = a;
            }

    }
    fclose(fileclass);


    ///pour la récupération des bitmaps
    for(i=0;i<4;i++){
        for(j=0;j<16;j++){
            sprintf(nom,"animation/mort/%d.bmp",j+1);
            tab[i].mort[j] = load_bitmap(nom,NULL);
            if(!tab[i].mort[j]){
                allegro_message("probleme animMort %d %d", i, j);
            }
        }
        for(j=0;j<8;j++){
            sprintf(nom,"animation/%d/deplacement/N%d.bmp",i,j+1);
            tab[i].animNO[j] = load_bitmap(nom,NULL);

            sprintf(nom,"animation/%d/deplacement/S%d.bmp",i,j+1);
            tab[i].animSO[j] = load_bitmap(nom,NULL);

            if(!tab[i].animNO[j]){
                allegro_message("c'est raté....%d", j);
                allegro_exit();
            }
            if(!tab[i].animSO[j]){
                allegro_message("c'est raté....%d", j);
                allegro_exit();
            }
        }

        tab[i].attaqueNO = (BITMAP **)malloc(tab[i].nbAnimationsAttaque*sizeof(BITMAP*));
        tab[i].attaqueSO = (BITMAP **)malloc(tab[i].nbAnimationsAttaque*sizeof(BITMAP*));
        for(j=0;j<tab[i].nbAnimationsAttaque;j++){
            sprintf(nom,"animation/%d/attaque/N%d.bmp",i,j+1);
            tab[i].attaqueNO[j] = load_bitmap(nom,NULL);

            sprintf(nom,"animation/%d/attaque/S%d.bmp",i,j+1);
            tab[i].attaqueSO[j] = load_bitmap(nom,NULL);

            if(!tab[i].attaqueNO[j]){
                allegro_message("probleme attaque");
            }

            if(!tab[i].attaqueSO[j]){
                allegro_message("probleme attaque");
            }
        }
    }

}


t_jeu initTabMap(t_jeu regl){
    int i,j;

    for ( i=0;i<16;i++){
        for( j=0;j<16;j++){
            regl.tabMap[i][j] = 0;
        }
    }
    FILE* maptxt = fopen("map/map.txt", "r"); //ouverture du fichier en lecture seule

    if(maptxt == NULL){
        printf("pbm ouverture map");
    }

    else{
        for( i=0; i<16; i++){
            fscanf(maptxt, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &regl.tabMap[0][i], &regl.tabMap[1][i], &regl.tabMap[2][i], &regl.tabMap[3][i], &regl.tabMap[4][i], &regl.tabMap[5][i], &regl.tabMap[6][i], &regl.tabMap[7][i], &regl.tabMap[8][i], &regl.tabMap[9][i], &regl.tabMap[10][i], &regl.tabMap[11][i], &regl.tabMap[12][i], &regl.tabMap[13][i], &regl.tabMap[14][i], &regl.tabMap[15][i]);

        }
    }
    fclose(maptxt);


    return regl;
}


t_jeu initMapJeu(t_jeu regl){
    int i,j;

    regl = initTabMap(regl);
    int x,y;
    BITMAP * tileSET = load_bitmap("map/tileSET.bmp",NULL);
    BITMAP * cactus = load_bitmap("map/cactus.bmp",NULL);
    BITMAP * buisson = load_bitmap("map/buisson.bmp",NULL);
    if(!tileSET){
        allegro_message("ta mere la pute");
        allegro_exit();
    }

    for( i=0;i<16;i++){
        for( j = 0; j<16;j++){
            convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
            x-=30;
            switch (regl.tabMap[i][j]){
            ///Herbe
            case 10:
                masked_blit(tileSET,regl.mapJeu,0,0,x,y,60,30);
                masked_blit(tileSET,regl.mapJeu,0,5*30,x-30,y+15,60,30);
                masked_blit(tileSET,regl.mapJeu,0,4*30,x,y+30,60,30);


                break;

            case 11:
                masked_blit(tileSET,regl.mapJeu,0,0,x,y,60,30);

                masked_blit(tileSET,regl.mapJeu,0,2*30,x,y+30,60,30);
                masked_blit(tileSET,regl.mapJeu,0,3*30,x+30,y+15,60,30);

                break;

            case 12:
                masked_blit(tileSET,regl.mapJeu,0,0,x,y,60,30);
                break;

            case 13:
                 masked_blit(tileSET,regl.mapJeu,0,0,x,y,60,30);
                 masked_blit(tileSET,regl.mapJeu,0,30,x,y+30,60,30);
                 masked_blit(tileSET,regl.mapJeu,0,3*30,x+30,y+15,60,30);

                 masked_blit(tileSET,regl.mapJeu,0,5*30,x-30,y+15,60,30);
                break;
            ///sable
            case 20:
                masked_blit(tileSET,regl.mapJeu,60,0,x,y,60,30);
                masked_blit(tileSET,regl.mapJeu,60,5*30,x-30,y+15,60,30);
                masked_blit(tileSET,regl.mapJeu,60,4*30,x,y+30,60,30);

                break;

            case 21:
                masked_blit(tileSET,regl.mapJeu,60,0,x,y,60,30);

                masked_blit(tileSET,regl.mapJeu,60,2*30,x,y+30,60,30);
                masked_blit(tileSET,regl.mapJeu,60,3*30,x+30,y+15,60,30);
                break;

            case 22:
                masked_blit(tileSET,regl.mapJeu,60,0,x,y,60,30);
                break;
            case 23:
                masked_blit(tileSET,regl.mapJeu,60,0,x,y,60,30);
                masked_blit(tileSET,regl.mapJeu,60,30,x,y+30,60,30);
                masked_blit(tileSET,regl.mapJeu,60,3*30,x+30,y+15,60,30);

                masked_blit(tileSET,regl.mapJeu,60,5*30,x-30,y+15,60,30);
                break;
            ///eau
            case 30:
                masked_blit(tileSET,regl.mapJeu,2*60,0,x,y,60,30);
                masked_blit(tileSET,regl.mapJeu,2*60,5*30,x-30,y+15,60,30);
                masked_blit(tileSET,regl.mapJeu,2*60,4*30,x,y+30,60,30);
                break;

            case 31:
                masked_blit(tileSET,regl.mapJeu,2*60,0,x,y,60,30);

                masked_blit(tileSET,regl.mapJeu,2*60,2*30,x,y+30,60,30);
                masked_blit(tileSET,regl.mapJeu,2*60,3*30,x+30,y+15,60,30);
                break;

            case 32:
                masked_blit(tileSET,regl.mapJeu,2*60,0,x,y,60,30);
                break;

            case 33:
                masked_blit(tileSET,regl.mapJeu,2*60,0,x,y,60,30);
                masked_blit(tileSET,regl.mapJeu,2*60,30,x,y+30,60,30);
                masked_blit(tileSET,regl.mapJeu,2*60,3*30,x+30,y+15,60,30);

                masked_blit(tileSET,regl.mapJeu,2*60,5*30,x-30,y+15,60,30);
                break;
            ///bois
            case 41:

                if(regl.tabMap[i][j+1] == 12){
                    masked_blit(tileSET,regl.mapJeu,0,0,x,y,60,30);
                }
                if(regl.tabMap[i][j+1] == 32){
                    masked_blit(tileSET,regl.mapJeu,2*60,0,x,y,60,30);
                }
                //masked_blit(tileSET,regl.mapJeu,3*60,0,x-30,y-15,60,45);
                break;


            }
        }
    }
    for( i=0;i<16;i++){
        for( j = 0; j<16;j++){
            if(regl.tabMap[i][j] == 41){
                convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                x-=30;
                masked_blit(tileSET,regl.mapJeu,3*60,0,x,y,60,45);
            }
        }
    }
    for( i=0;i<16;i++){
        for( j = 0; j<16;j++){
            if(regl.tabObstacles[i][j] == 1){
                convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                x-=30;
                masked_blit(buisson,regl.mapJeu,0,0,x,y,60,30);
            }
            if(regl.tabObstacles[i][j] == 2){
                convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                x-=30;
                masked_blit(cactus,regl.mapJeu,0,0,x,y,60,30);
            }
        }
    }

    destroy_bitmap(tileSET);
    destroy_bitmap(cactus);
    destroy_bitmap(buisson);
    return regl;
}


t_jeu initTabObstacles(t_jeu regl){

    int i,j;

    for (i=0;i<16;i++){
        for(j=0;j<16;j++){
            regl.tabObstacles[i][j] = 0;
        }
    }
    FILE* mapObstaclestxt = fopen("map/mapObstacles.txt", "r"); //ouverture du fichier en lecture seule

    if(mapObstaclestxt == NULL){
        printf("pbm ouverture map obstacles");
    }

    else{
        for(i=0; i<16; i++){
            fscanf(mapObstaclestxt, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &regl.tabObstacles[0][i], &regl.tabObstacles[1][i], &regl.tabObstacles[2][i], &regl.tabObstacles[3][i], &regl.tabObstacles[4][i], &regl.tabObstacles[5][i], &regl.tabObstacles[6][i], &regl.tabObstacles[7][i], &regl.tabObstacles[8][i], &regl.tabObstacles[9][i], &regl.tabObstacles[10][i], &regl.tabObstacles[11][i], &regl.tabObstacles[12][i], &regl.tabObstacles[13][i], &regl.tabObstacles[14][i], &regl.tabObstacles[15][i]);

        }
    }
    fclose(mapObstaclestxt);


    return regl;

}




int premierChargement(int cpt)
{
    int nbJ;
    /***********Initialisation des cases du plateau***********/
    if(cpt==1)
    {
        FILE* pf = fopen("sauvegarde/sauv1.txt", "r+");
        if(!pf){
            allegro_message("Probleme d'ouverture du fichier");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
        fscanf(pf, "%d\n",&nbJ);
        fclose(pf);
        pf = NULL;
        free(pf);
    }
    else if(cpt==2)
    {
        FILE* pf = fopen("sauvegarde/sauv2.txt", "r+");
        if(!pf){
            allegro_message("Probleme d'ouverture du fichier");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
         fscanf(pf, "%d\n",&nbJ);
         fclose(pf);
        pf = NULL;
        free(pf);
    }
    else if(cpt==3)
    {
        FILE* pf = fopen("sauvegarde/sauv3.txt", "r+");
        if(!pf){
            allegro_message("Probleme d'ouverture du fichier");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
         fscanf(pf, "%d\n",&nbJ);
         fclose(pf);
        pf = NULL;
        free(pf);
    }

    return nbJ;
}

t_jeu chargement(t_jeu regl,int nbr,int cpt)
{
    /***********Initialisation des cases du plateau***********/
     int classe;
    recupfichier(regl.tabClasses);

    if(cpt==1)
    {
        FILE* pf = fopen("sauvegarde/sauv1.txt", "r+");
        if(!pf){
            printf("erreur de fichier");
            allegro_message("probleme d'ouvertur du fichier de sauvegarde");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
        for (int i = 0; i < nbr; i++) {
            fscanf(pf, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n",&regl.nbJoueurs,&regl.tour, &regl.joueur[i].x,&regl.joueur[i].y,&regl.joueur[i].dx,&regl.joueur[i].dy,regl.joueur[i].nom,&regl.joueur[i].PA,&regl.joueur[i].PV,&regl.joueur[i].PM,&classe,&regl.joueur[i].podium,&regl.joueur[i].estMort, &regl.joueur[i].typeAction);
            regl.joueur[i].classe=regl.tabClasses[classe];
            regl.joueur[i].classe.type = classe;
        }

        fclose(pf);
        pf = NULL;
        free(pf);
    }
    else if(cpt==2)
    {
        FILE* pf = fopen("sauvegarde/sauv2.txt", "r+");
        if(!pf){
            printf("erreur de fichier");
            allegro_message("probleme d'ouvertur du fichier de sauvegarde");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
        for (int i = 0; i < nbr; i++) {
            fscanf(pf, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n",&regl.nbJoueurs,&regl.tour, &regl.joueur[i].x,&regl.joueur[i].y,&regl.joueur[i].dx,&regl.joueur[i].dy,regl.joueur[i].nom,&regl.joueur[i].PA,&regl.joueur[i].PV,&regl.joueur[i].PM,&classe,&regl.joueur[i].podium,&regl.joueur[i].estMort, &regl.joueur[i].typeAction);
            regl.joueur[i].classe=regl.tabClasses[classe];
            regl.joueur[i].classe.type = classe;
        }

        fclose(pf);
        pf = NULL;
        free(pf);
    }
    else if(cpt==3)
    {
        FILE* pf = fopen("sauvegarde/sauv3.txt", "r+");
        if(!pf){
            printf("erreur de fichier");
            allegro_message("probleme d'ouvertur du fichier de sauvegarde");
        }
        else {
            perror("Erreur ");
            char buff[1000];
            printf("CWD : %s\n", getcwd(buff,1000));
        }
        for (int i = 0; i < nbr; i++) {
            fscanf(pf, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n",&regl.nbJoueurs,&regl.tour, &regl.joueur[i].x,&regl.joueur[i].y,&regl.joueur[i].dx,&regl.joueur[i].dy,regl.joueur[i].nom,&regl.joueur[i].PA,&regl.joueur[i].PV,&regl.joueur[i].PM,&classe,&regl.joueur[i].podium,&regl.joueur[i].estMort, &regl.joueur[i].typeAction);
            regl.joueur[i].classe=regl.tabClasses[classe];
            regl.joueur[i].classe.type = classe;
        }

        fclose(pf);
        pf = NULL;
        free(pf);
    }


    return regl;


}
t_jeu chargementGlobal(t_jeu regl,int cpt){
     int nb,i;

     nb=premierChargement(cpt);

     //allocation dynamique en f° du nb de joueur
     regl.joueur = (t_player*)malloc((nb)*sizeof(t_player));
     regl.nbJoueurs=nb;
     regl = chargement(regl,nb,cpt);
     regl.rankTab = (int*)malloc(nb*sizeof(int));
     for(i=0;i<nb;i++){
        if(regl.joueur[i].podium>=0 && regl.joueur[i].podium<nb){
            regl.rankTab[regl.joueur[i].podium] = i;
        }
     }

    return regl;
}
/// Menu pr sélectionner le nb de joueur (sert pr alloc dyn ap)
void selec_charg(int* choix, BITMAP* Font[120]){
    BITMAP* souris = load_bitmap("mouse.bmp", NULL);
    int cpt=0;

    //initialisation du buffer et vérification
    BITMAP* transition = create_bitmap(SCREEN_W, SCREEN_H);
    if(transition == NULL){
        allegro_message("Pbm bitmap");
    }

    //initialisation pr la boucle while
    *choix = -1;

    //tant que pas de boutons sélectionné
    while(*choix==-1){
        clear_bitmap(transition);

        afficher_charg(transition, Font, cpt);
        masked_blit(souris, transition, 0,0, mouse_x, mouse_y, souris->w, souris->h);
        blit(transition, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

         if(mouse_x<=850 && mouse_x>=350){
            if(mouse_y<=300 && mouse_y>=200){
                cpt = 1;
                if(mouse_b&1){
                    *choix = 1;
                }
            }
            if(mouse_y<=450 && mouse_y>=350){
                cpt = 2;
                if(mouse_b&1){
                    *choix = 2;
                }
            }
            if(mouse_y<=600 && mouse_y>=500){
                cpt = 3;
                if(mouse_b&1){
                    *choix = 3;
                }
            }
        }
        else{
            //sinon compteur à 0 (souris sur aucun boutons)
            cpt = 0;
        }

        // mm chose que pr le menu des type switch sert à la vérification de la sélec et pourra être enlevé (!! si enlevé remettre le destroy)
        switch (*choix){
            case 2:
                clear_bitmap(transition);
                destroy_bitmap(transition);
                destroy_bitmap(souris);
                printf("\n%d", *choix);
                break;
            case 3:
                clear_bitmap(transition);
                destroy_bitmap(transition);
                destroy_bitmap(souris);
                printf("\n%d", *choix);
                break;
            case 4:
                clear_bitmap(transition);
                destroy_bitmap(transition);
                destroy_bitmap(souris);
                printf("\n%d", * choix);
                break;

        }
    }
}
void afficher_charg(BITMAP* buffer, BITMAP* police[120], int cpt){
    if(cpt==0){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "CHARGEMENT", 360, 50, 2);
        printTEXT(buffer, police, "Chargement 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Chargement 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Chargement 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==1){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "CHARGEMENT", 360, 50, 2);
        printTEXT(buffer, police, "Chargement 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Chargement 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Chargement 3", 490, 530, 0.7);
        round_rect(buffer, 300, 200, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==2){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "CHARGEMENT", 360, 50, 2);
        printTEXT(buffer, police, "Chargement 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Chargement 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Chargement 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 300, 350, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==3){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "CHARGEMENT", 360, 50, 2);
        printTEXT(buffer, police, "Chargement 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Chargement 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Chargement 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 300, 500, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
    }
}




