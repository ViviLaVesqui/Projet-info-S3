#include "maBiblio.h"






t_sample bouton_volume(BITMAP * buffer,BITMAP * collVolume, t_sample sampl, BITMAP * Font[120]){

    BITMAP * volUP = load_bitmap("parametres/volUP.bmp",NULL);
    BITMAP * volDOWN = load_bitmap("parametres/volDOWN.bmp",NULL);


    int w = 360;
    int h = 50;
    int round = 5;
    int thick = 5;
    int x = 450;
    int y = 110;

    sampl.vol = (float)(sampl.xm - x -140)/(x+w+10- x -170);
    sampl.vol = sampl.vol*255;


    round_rect(buffer, x, y, w, h, round, thick, makecol(100,100,100), makecol(255,255,255));   //création de la case contenant la barre de son


    rectfill(collVolume, 545,123,570,148, makecol(255,0,0));          //ajout de l'image Volume A AJOUTER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    printTEXT(buffer, Font, "Musique", 460,125,0.5);    //affichage de "Volume




    rectfill(buffer, x+140,y+20, x+w-20,y +30, makecol(0,0,0)); //rectangle case volume (barre de son)
    rectfill(buffer, x+140,y+20, sampl.xm,y +30, makecol(150,150,255)); // rectangle représentant le volume
    circlefill(buffer, x+140,y+25,5, makecol(150,150,255));     //cercle gauche case
    circlefill(buffer, x+w-20,y+25,5, makecol(0,0,0));    //cercle droit case
    circlefill(buffer, sampl.xm,y+25,7, makecol(10,10,10));       //Extérieur du bouton volume
    circlefill(buffer, sampl.xm,y+25,5, makecol(255,255,255));    //Intérieur du bouton volume




    circlefill(collVolume, x+140+(sampl.xm),y+25,7, makecol(255,0,255));
    if(mouse_b&1 && getpixel(collVolume, mouse_x, mouse_y)==makecol(255,0,255)){
        if(mouse_x>=x+140 && mouse_x<=x+w-20){
            sampl.xm = mouse_x;
        }
        sampl.on = 1;
    }
    if(mouse_b&1 && getpixel(collVolume, mouse_x, mouse_y)==makecol(255,0,0)){
        if(sampl.on == 1){
            sampl.on = 0;
        }
        else if(sampl.on == 0){
            sampl.on = 1;
        }
        while(mouse_b&1);

    }
    if(sampl.on == 1){
        masked_blit(volUP, buffer,0,0,545,123,25,25);
    }
    else if(sampl.on == 0){
        masked_blit(volDOWN, buffer,0,0,545,123,25,25);
        sampl.vol = 0;
    }



    clear_bitmap(collVolume);
    circlefill(collVolume, sampl.xm,y+25,7, makecol(255,0,255));

    rectfill(collVolume, x+140,y+20, x+w-20,y +30, makecol(255,0,255));
    destroy_bitmap(volDOWN);
    destroy_bitmap(volUP);



    adjust_sample(sampl.smpl, (int)sampl.vol, sampl.pan, sampl.freq, sampl.loop);
    return sampl;
}



t_jeu screenMode(BITMAP * buffer, BITMAP * Font[120], t_jeu regl){

    int w = 360;
    int h = 50;
    int round = 5;
    int thick = 5;
    int x = 450;
    int y = 170;
    int HasChanged = 0;


    round_rect(buffer, x, y, w, h, round, thick, makecol(100,100,100), makecol(255,255,255));   //création de la case contenant la barre de son
    printTEXT(buffer,Font, "Affichage", x+10, y+15, 0.5);

    if(regl.affichage == -1){
        printTEXT(buffer,Font, "Fenetre", x+205, y+15, 0.5);

    }
    else if(regl.affichage == 1){
        printTEXT(buffer,Font, "Plein ecran", x+185, y+15, 0.5);
    }

    if(mouse_b&1 && mouse_x>=(x+160) && mouse_x<=(x+180) && mouse_y>=(y+15) && mouse_y <=(y+35)){
        regl.affichage = -regl.affichage;
        HasChanged = 1;
    }

    if(mouse_b&1 && mouse_x>=(x+320) && mouse_x<=(x+340) && mouse_y>=(y+15) && mouse_y <=(y+35)){
        regl.affichage = -regl.affichage;
        HasChanged = 1;
    }



    if(HasChanged == 1){
        if(regl.affichage == 1){
            set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,1280,720,0,0);
        }
        if(regl.affichage == -1){
            set_gfx_mode(GFX_AUTODETECT_WINDOWED,1280,720,0,0);
        }
        HasChanged = 0;
        rest(500);
    }

    round_rect(buffer,x+160,y+15,20,20,7,1,makecol(14,14,14),makecol(14,14,14));
    round_rect(buffer,x+320,y+15,20,20,7,1,makecol(14,14,14),makecol(14,14,14));
    printTEXT(buffer,Font,"<",x+160,y+15,0.5);
    printTEXT(buffer,Font,">",x+320,y+15,0.5);

    return regl;
}



t_jeu quitter(BITMAP * buffer, BITMAP * Font[120], t_jeu regl){

    int w = 120;
    int h = 30;
    int round = 5;
    int thick = 5;
    int x = SCREEN_W/2-60;
    int y = 490;
    int sure = 0;


    round_rect(buffer, x, y, w, h, round, thick, makecol(100,100,100), makecol(255,255,255));   //création de la case contenant la barre de son

    printTEXT(buffer,Font,"QUITTER",SCREEN_W/2-45,y+5,0.5);



    if(mouse_b&1 && mouse_x>=x+5 && mouse_x<=(x+w-5) && mouse_y>=(y+5) && mouse_y <=(y+h-5)){
        if(regl.enJeu == 1){
        BITMAP * cursor = load_bitmap("mouse.bmp", NULL);
        BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);

            while(sure == 0){
                clear_bitmap(temp);
                rectfill(temp,0,0,SCREEN_W,SCREEN_H,makecol(255,0,255));
                blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);

                rectfill(temp,SCREEN_W/2-210,SCREEN_H/2-50,SCREEN_W/2+200,SCREEN_H/2+50, makecol(255,255,255));
                round_rect(temp,SCREEN_W/2-210,SCREEN_H/2-50,410,100,5,2,makecol(0,0,0),makecol(60,200,155));
                printTEXT(temp,Font,"Etes vous sur de vouloir quitter ?",SCREEN_W/2-200,SCREEN_H/2-40,0.5);

                round_rect(temp,SCREEN_W/2+47,SCREEN_H/2-5,50,30,3,2,makecol(0,0,0),makecol(60,255,60));
                round_rect(temp,SCREEN_W/2-103,SCREEN_H/2-5,50,30,3,2,makecol(0,0,0),makecol(255,60,60));


                printTEXT(temp,Font,"OUI",SCREEN_W/2+50,SCREEN_H/2,0.5);
                printTEXT(temp,Font,"NON",SCREEN_W/2-100,SCREEN_H/2,0.5);

                if(mouse_b&1 && mouse_x>=SCREEN_W/2+47 && mouse_x<=SCREEN_W/2+47+50 && mouse_y>=SCREEN_H/2-5 && mouse_y <=SCREEN_H/2-5+30){//pour le Oui
                    sure = 1;
                    regl.fermerParam = 1;
                    regl.enJeu = 0;
                    regl.attendreScore = 0;
                    regl.quit = 0;
                    while(mouse_b&1);
                }
                else if(mouse_b&1 && mouse_x>=SCREEN_W/2-103 && mouse_x<=SCREEN_W/2-103+50 && mouse_y>=SCREEN_H/2-5 && mouse_y <=SCREEN_H/2-5+30){//pour le Oui
                    sure = 1;
                    regl.fermerParam = 0;
                    while(mouse_b&1);
                }



                masked_blit(cursor,temp,0,0,mouse_x,mouse_y,cursor->w,cursor->h);
                masked_blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            destroy_bitmap(cursor);
            destroy_bitmap(temp);
        }
        else{
            regl.fermerParam = 1;
        }
    }



    return regl;
}


t_jeu sauvegarder(BITMAP * buffer,BITMAP * Font[120],t_jeu regl){

    int w = 120;
    int h = 30;
    int round = 5;
    int thick = 5;
    int x = SCREEN_W/2-60;
    int y = 450;

    if(regl.enJeu == 1){
        round_rect(buffer,x-10,y,w+20,h,round,thick,makecol(100,100,100), makecol(255,255,255));
        printTEXT(buffer,Font,"Sauvegarder",SCREEN_W/2-65,y+5,0.5);


        if(mouse_b&1 && mouse_x>=x-10 && mouse_x<=x+w+10 && mouse_y>=y && mouse_y <= y+h){
            ///Sauvegarde

            menu_et_sauvegarde(buffer, Font, regl);

            regl.fermerParam = 1;
        }

    }
    return regl;
}

t_jeu fermerParam(BITMAP * buffer,t_jeu regl){
    BITMAP * cross = load_bitmap("parametres/CROIX.bmp",NULL);

    round_rect(buffer,819,89,19+1,19,5,1,makecol(5,5,5),makecol(255,255,255));



    masked_blit(cross,buffer,0,0,820,90,cross->w,cross->h);



    if(regl.fermerParam == 0 && mouse_b&1 && mouse_x>=819 && mouse_x<=819+19 && mouse_y>=89 && mouse_y <= 89+19){
        regl.fermerParam = 1;
        while(mouse_b&1);
    }
    if(key[KEY_ESC]){
        regl.fermerParam = 1;
        while(key[KEY_ESC]);
    }

    destroy_bitmap(cross);
    return regl;
}


t_jeu parametre(BITMAP * buffer, BITMAP * Font[120],BITMAP * collVolume,t_jeu regl){


    rectfill(buffer,SCREEN_W/2-225,80,SCREEN_W/2+215,SCREEN_H-80,makecol(255,255,255));
    round_rect(buffer,SCREEN_W/2-230,75,450,SCREEN_H-150,15,7,makecol(10,10,10),makecol(100,200,200));
    floodfill(buffer,SCREEN_W/2,SCREEN_H/2,makecol(100,200,200));

    regl.sampl = bouton_volume(buffer,collVolume, regl.sampl, Font);

    regl = screenMode(buffer,Font,regl);

    regl = sauvegarder(buffer,Font, regl);



    regl = fermerParam(buffer,regl);

    regl = quitter(buffer,Font, regl);


    return regl;
}





void menu_et_sauvegarde(BITMAP* buffer, BITMAP* police[120], t_jeu regl){
    FILE* sauv1=NULL;
    FILE* sauv2=NULL;
    FILE* sauv3=NULL;

    int nb_fich=0;
    int cpt=0, i=0;

    BITMAP* souris = load_bitmap("mouse.bmp", NULL);

    if(souris == NULL){
        allegro_message("pbm");
    }

    while(mouse_b & 1){}

    while(nb_fich==0){
        //mise en forme du buffer pr l'affichage du menu
        clear_bitmap(buffer);
        afficher_menu_sauvegarde(buffer, police, cpt);
        masked_blit(souris, buffer, 0,0, mouse_x, mouse_y, souris->w, souris->h);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        //test d'appui sur les boutons et récup du choix
        if(mouse_x<=850 && mouse_x>=350){
            if(mouse_y<=300 && mouse_y>=200){
                cpt = 1;
                if(mouse_b&1){
                    nb_fich = 1;
                }
            }
            if(mouse_y<=450 && mouse_y>=350){
                cpt = 2;
                if(mouse_b&1){
                    nb_fich = 2;
                }
            }
            if(mouse_y<=600 && mouse_y>=500){
                cpt = 3;
                if(mouse_b&1){
                    nb_fich = 3;
                }
            }
        }
        else{
            cpt = 0;
        }

        //traitement des sauvegardes en fonction du choix
        if(nb_fich==1){
            sauv1 = fopen("sauvegarde/sauv1.txt", "w");
            for(i=0; i<regl.nbJoueurs; i++){
                fprintf(sauv1, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n", (regl.nbJoueurs), regl.tour, regl.joueur[i].x, regl.joueur[i].y, regl.joueur[i].dx, regl.joueur[i].dy, regl.joueur[i].nom, regl.joueur[i].PA, regl.joueur[i].PV, regl.joueur[i].PM, regl.joueur[i].classe.type,regl.joueur[i].podium,regl.joueur[i].estMort, regl.joueur[i].typeAction);
            }
            fclose(sauv1);

        }
        if(nb_fich==2){
            sauv2 = fopen("sauvegarde/sauv2.txt", "w");
            for(i=0; i<regl.nbJoueurs; i++){
                fprintf(sauv2, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n", (regl.nbJoueurs), regl.tour, regl.joueur[i].x, regl.joueur[i].y, regl.joueur[i].dx, regl.joueur[i].dy, regl.joueur[i].nom, regl.joueur[i].PA, regl.joueur[i].PV, regl.joueur[i].PM, regl.joueur[i].classe.type,regl.joueur[i].podium,regl.joueur[i].estMort, regl.joueur[i].typeAction);
            }
            fclose(sauv2);

        }
        if(nb_fich==3){
            sauv3 = fopen("sauvegarde/sauv3.txt", "w");
            for(i=0; i<regl.nbJoueurs; i++){
                fprintf(sauv3, "%d %d %d %d %d %d %s %d %d %d %d %d %d %d\n", (regl.nbJoueurs), regl.tour , regl.joueur[i].x, regl.joueur[i].y, regl.joueur[i].dx, regl.joueur[i].dy, regl.joueur[i].nom, regl.joueur[i].PA, regl.joueur[i].PV, regl.joueur[i].PM, regl.joueur[i].classe.type,regl.joueur[i].podium,regl.joueur[i].estMort, regl.joueur[i].typeAction);
            }
            fclose(sauv3);

        }
    }

    sauvegarde_en_cours(buffer, police);

    destroy_bitmap(souris);
}

void sauvegarde_en_cours(BITMAP* buffer, BITMAP* police[120]){
    int i=0;

    clear(buffer);
    afficher_menu_sauvegarde(buffer, police, 0);
    printTEXT(buffer, police, "Sauvegarde en cours", 930, 650, 0.5);
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    while(!(i==3)){
        rest(1000);
        clear(buffer);
        afficher_menu_sauvegarde(buffer, police, 0);
        printTEXT(buffer, police, "Sauvegarde en cours.", 930, 650, 0.5);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        rest(1000);
        clear(buffer);
        afficher_menu_sauvegarde(buffer, police, 0);
        printTEXT(buffer, police, "Sauvegarde en cours..", 930, 650, 0.5);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        rest(1000);
        clear(buffer);
        afficher_menu_sauvegarde(buffer, police, 0);
        printTEXT(buffer, police, "Sauvegarde en cours...", 930, 650, 0.5);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        i++;

    }

    while(!key[KEY_ENTER]){
        clear_bitmap(buffer);
        afficher_menu_sauvegarde(buffer, police, 0);
        printTEXT(buffer, police, "Sauvegarde terminee !", 880, 625, 0.5);
        printTEXT(buffer, police, "Appuyez sur ENTRER pour continuer.", 880, 650, 0.5);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    }

}
void afficher_menu_sauvegarde(BITMAP* buffer, BITMAP* police[120], int cpt){
    if(cpt==0){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "SAUVEGARDE", 360, 50, 2);
        printTEXT(buffer, police, "Sauvegarde 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Sauvegarde 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Sauvegarde 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==1){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "SAUVEGARDE", 360, 50, 2);
        printTEXT(buffer, police, "Sauvegarde 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Sauvegarde 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Sauvegarde 3", 490, 530, 0.7);
        round_rect(buffer, 300, 200, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==2){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "SAUVEGARDE", 360, 50, 2);
        printTEXT(buffer, police, "Sauvegarde 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Sauvegarde 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Sauvegarde 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 300, 350, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
        round_rect(buffer, 350, 500, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
    }
    if(cpt==3){
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 10, makecol(187,97,0), makecol(27,168,156));
        printTEXT(buffer, police, "SAUVEGARDE", 360, 50, 2);
        printTEXT(buffer, police, "Sauvegarde 1", 490, 230, 0.7);
        printTEXT(buffer, police, "Sauvegarde 2", 490, 380, 0.7);
        printTEXT(buffer, police, "Sauvegarde 3", 490, 530, 0.7);
        round_rect(buffer, 350, 200, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 350, 350, 500, 100, 10, 5, makecol(187,97,0), makecol(27,168,156));
        round_rect(buffer, 300, 500, 600, 100, 10, 5, makecol(246,127,0), makecol(42,229,213));
    }
}


