#include "maBiblio.h"

// menu pr sélec le nb de joueurs (passage par adresse, modification de nbjoueur de struct jeu) --> traitement alloc dyn tab joueur
// menu pr sélectionner la classe (passage par adresse d'un entier (ref au tab de classes et leurs indices) --> traitement créa joueur
// affichage des rectangles et textes pr chacun des menus
/// Affichage du menu correspondant aux coord de la souris
void affichage_menu_cpt(BITMAP* buffer, BITMAP* police[120], int cpt, t_classe c[4]){
    BITMAP* demon = load_bitmap("animation/0/deplacement/S1.bmp", NULL);
    BITMAP* valla = load_bitmap("animation/1/deplacement/S1.bmp", NULL);
    BITMAP* maid = load_bitmap("animation/2/deplacement/S1.bmp", NULL);
    BITMAP* witch = load_bitmap("animation/3/deplacement/S1.bmp", NULL);

    if(cpt==-1){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe
        round_rect(buffer, 700, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,100,144));
        round_rect(buffer, 950, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,100,144));
        round_rect(buffer, 700, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,100,144));
        round_rect(buffer, 950, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,100,144));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5,makecol(187,97,0), makecol(0,100,144));
        printTEXT(buffer, police, "_____", 260, 200, 0.5);

        //print des texts sur les boutons
        printTEXT(buffer, police, "_____", 745, 335, 0.5);
        printTEXT(buffer, police, "_____", 995, 335, 0.5);
        printTEXT(buffer, police, "____", 750, 475, 0.5);
        printTEXT(buffer, police, "_____", 995, 475, 0.5);

    }
    if(cpt==0){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        //round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe
        round_rect(buffer, 700, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 700, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5,makecol(187,97,0), makecol(0,121,175));
        printTEXT(buffer, police, "_____", 260, 200, 0.5);

        //print des texts sur les boutons
        printTEXT(buffer, police, "DEMON", 745, 335, 0.5);
        printTEXT(buffer, police, "VALLA", 995, 335, 0.5);
        printTEXT(buffer, police, "MAID", 750, 475, 0.5);
        printTEXT(buffer, police, "WITCH", 995, 475, 0.5);
    }
    if(cpt==1){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        //round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(152,198,245), makecol(104,104,104));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe
        round_rect(buffer, 680, 290, 200, 100, 10, 5,makecol(246,127,0), makecol(168,168,168));
        round_rect(buffer, 950, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 700, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5, makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "DEMON", 260, 200, 0.5);
        masked_stretch_blit(demon, buffer, 0,0, demon->w, demon->h, 220, 220, demon->w*2, demon->h*2);


        //print des texts sur les boutons
        printTEXT(buffer, police, "DEMON", 745, 335, 0.5);
        printTEXT(buffer, police, "VALLA", 995, 335, 0.5);
        printTEXT(buffer, police, "MAID", 750, 475, 0.5);
        printTEXT(buffer, police, "WITCH", 995, 475, 0.5);

        //appel du ss prgrm pr l'affichage des caractéristiques de la classe
        afficher_carac_class(police, buffer, c[0]);
        //affichage du texte sur les caractéristiques du personnage
        printTEXT(buffer, police, "...", 180, 480, 0.5);
    }
    if(cpt==2){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        //round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(152,198,245), makecol(104,104,104));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe
        round_rect(buffer, 700, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 930, 290, 200, 100, 10, 5, makecol(246,127,0), makecol(168,168,168));
        round_rect(buffer, 700, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5,makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "VALLA", 260, 200, 0.5);
        masked_stretch_blit(valla, buffer, 0,0, valla->w, valla->h, 220, 220, valla->w*2, valla->h*2);

        //print des texts sur les boutons
        printTEXT(buffer, police, "DEMON", 745, 335, 0.5);
        printTEXT(buffer, police, "VALLA", 995, 335, 0.5);
        printTEXT(buffer, police, "MAID", 750, 475, 0.5);
        printTEXT(buffer, police, "WITCH", 995, 475, 0.5);

        //appel du ss prgrm pr l'affichage des caractéristiques de la classe
        afficher_carac_class(police, buffer, c[1]);
        //affichage du texte sur les caractéristiques du personnage
        printTEXT(buffer, police, "...", 180, 480, 0.5);
    }
    if(cpt==3){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        //round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(152,198,245), makecol(104,104,104));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe
        round_rect(buffer, 700, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 680, 430, 200, 100, 10, 5, makecol(246,127,0), makecol(168,168,168));
        round_rect(buffer, 950, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5,makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "MAID", 260, 200, 0.5);
        masked_stretch_blit(maid, buffer, 0,0, maid->w, maid->h, 220, 220, maid->w*2, maid->h*2);

        //print des texts sur les boutons
        printTEXT(buffer, police, "DEMON", 745, 335, 0.5);
        printTEXT(buffer, police, "VALLA", 995, 335, 0.5);
        printTEXT(buffer, police, "MAID", 750, 475, 0.5);
        printTEXT(buffer, police, "WITCH", 995, 475, 0.5);

        //appel du ss prgrm pr l'affichage des caractéristiques de la classe
        afficher_carac_class(police, buffer, c[2]);
        //affichage du texte sur les caractéristiques du personnage
        printTEXT(buffer, police, "...", 180, 480, 0.5);
    }
    if(cpt==4){

        //cadre du menu
        round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

        //cadre pour le nom
        //round_rect(buffer, 615, 105, 565, 85, 10, 5, makecol(152,198,245), makecol(104,104,104));
        printTEXT(buffer, police, "ENTER YOUR NAME:", 635, 130, 0.5);

        //4 boutons pour selec la classe (boutons classe 3 zoom)
        round_rect(buffer, 700, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 950, 310, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 700, 450, 160, 70, 10, 5, makecol(187,97,0), makecol(0,121,175));
        round_rect(buffer, 930, 430, 200, 100, 10, 5, makecol(246,127,0), makecol(168,168,168));

        // cadre pour l'affichage des caractéristiques de la classe
        round_rect(buffer, 130, 185, 345, 395, 10, 5,makecol(246,127,0), makecol(168,168,168));
        printTEXT(buffer, police, "WITCH", 260, 200, 0.5);
        masked_stretch_blit(witch, buffer, 0,0, demon->w, demon->h, 220, 220, demon->w*2, demon->h*2);


        //print des texts sur les boutons
        printTEXT(buffer, police, "DEMON", 745, 335, 0.5);
        printTEXT(buffer, police, "VALLA", 995, 335, 0.5);
        printTEXT(buffer, police, "MAID", 750, 475, 0.5);
        printTEXT(buffer, police, "WITCH", 995, 475, 0.5);

        //appel du ss prgrm pr l'affichage des caractéristiques de la classe
        afficher_carac_class(police, buffer, c[3]);
        //affichage du texte sur les caractéristiques du personnage
        printTEXT(buffer, police, "...", 180, 480, 0.5);
    }

    destroy_bitmap(demon);
    destroy_bitmap(valla);
    destroy_bitmap(maid);
    destroy_bitmap(witch);
}
///------------------------------------------

/// Menu pour sélectionner la classe du joueur (passage par adresse de l'entier qui correspond à l'indice du tab de classe)
void menu_classe(int* t, BITMAP* police[120], char nom[30], t_classe c[4]){
    BITMAP* souris = load_bitmap("mouse.bmp", NULL);
    // cpt pr le ss pgrm d'affichage et initialisation du pt pr la boucle while
    int cpt=0;

    //création et vérification du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if(buffer==NULL){
        allegro_message("PBM");
    }

    //initialisation pr la boucle while
    *t = -1;

    //si bouton appuyé
    /*while(mouse_b & 1){
        rest(200);
    }*/

    //tant que pas de bouton sélectionné
    while(*t==-1){

        clear_bitmap(buffer);

        // ss prgrm d'affichage du menu en fonction des pos de la souris (grossissment du bon bouton)
        affichage_menu_cpt(buffer, police, cpt, c);

        //affichage du nom du joueur à l'endroit où il l'a entré avant (cf créa joueur)
        printTEXT(buffer, police, nom, 820, 130, 0.5);

        masked_blit(souris, buffer, 0,0, mouse_x, mouse_y, souris->w, souris->h);
        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        if(mouse_y<=380 && mouse_y>=310){
            // cas où on sélec le bouton haut gauche (classe indice 0)
            if(mouse_x<=860 && mouse_x>=700){
                cpt = 1;
                if(mouse_b & 1){
                    *t = 0;
                }
            }
            // cas où on séléctionne le bouton haut droit (classe indice 1)
            if(mouse_x<=1110 && mouse_x>=950){
                cpt = 2;
                if(mouse_b & 1){
                    *t = 1;
                }
            }
        }
        else if(mouse_y<=520 && mouse_y>=450){
            // cas où on sélec le bouton bas droit (classe indice 3)
            if(mouse_x<=1110 && mouse_x>=950){
                cpt = 4;
                if(mouse_b & 1){
                    *t = 3;
                }
            }
            // cas où on sélec le bouton bas gauche (classe indice 2)
            if(mouse_x<=860 && mouse_x>=700){
                cpt = 3;
                if(mouse_b & 1){
                    *t = 2;
                }
            }
        }
        else{
            // sinon remise à 0 du cpt (aucun bouton agrandi)
            cpt=0;
        }

    }
    while(mouse_b&1);
    destroy_bitmap(souris);
    destroy_bitmap(buffer);
}
///-----------------------------------------


/// Affichage du menu pr la sélec des joueurs en fonction de la position de la souris (mm principe que pr la saisie de la classe)
void affichage_nbjoueur_cpt(BITMAP* buffer, BITMAP* Font[120], int cpt){
        if(cpt == 0){
            //cadre du menu
            round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

            //affichage des boutons
            round_rect(buffer, 70, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 500, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 930, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));

            //affichage du text
            printTEXT(buffer, Font, "SELECT THE NUMBER OF PLAYERS:", 480, 200, 0.5);
            printTEXT(buffer, Font, "2", 180, 340, 1);
            printTEXT(buffer, Font, "3", 615, 340, 1);
            printTEXT(buffer, Font, "4", 1045, 340, 1);

        }
        if(cpt == 1){
            //cadre du menu
            round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

            //affichage des boutons
            round_rect(buffer, 50, 290, 310, 140, 10, 5, makecol(233,116,35), makecol(184,184,184));
            round_rect(buffer, 500, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 930, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));

            //affichage du text
            printTEXT(buffer, Font, "SELECT THE NUMBER OF PLAYERS:", 480, 200, 0.5);
            printTEXT(buffer, Font, "2", 180, 340, 1);
            printTEXT(buffer, Font, "3", 615, 340, 1);
            printTEXT(buffer, Font, "4", 1045, 340, 1);

        }
        if(cpt == 2){
            //cadre du menu
            round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

            //affichage des boutons
            round_rect(buffer, 70, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 480, 290, 310, 140, 10, 5, makecol(233,116,35), makecol(184,184,184));
            round_rect(buffer, 930, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));

            //affichage du text
            printTEXT(buffer, Font, "SELECT THE NUMBER OF PLAYERS:", 480, 200, 0.5);
            printTEXT(buffer, Font, "2", 180, 340, 1);
            printTEXT(buffer, Font, "3", 615, 340, 1);
            printTEXT(buffer, Font, "4", 1045, 340, 1);

        }
        if(cpt == 3){
            //cadre du menu
            round_rect(buffer, 0,0, SCREEN_W, SCREEN_H, 10, 5, makecol(104,104,104), makecol(0,100,144));

            //affichage des boutons
            round_rect(buffer, 70, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 500, 310, 270, 100, 10, 5, makecol(187,97,0), makecol(0,121,175));
            round_rect(buffer, 910, 290, 310, 140, 10, 5, makecol(233,116,35), makecol(184,184,184));

            //affichage du text
            printTEXT(buffer, Font, "SELECT THE NUMBER OF PLAYERS:", 480, 200, 0.5);
            printTEXT(buffer, Font, "2", 180, 340, 1);
            printTEXT(buffer, Font, "3", 615, 340, 1);
            printTEXT(buffer, Font, "4", 1045, 340, 1);
        }
}
///--------------------------------------------


/// Menu pr sélectionner le nb de joueur (sert pr alloc dyn ap)
void selec_nb_joueurs(int* choix, BITMAP* Font[120]){
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

        affichage_nbjoueur_cpt(transition, Font, cpt);

        //textprintf_ex(transition, font, 0, 40, makecol(255, 255, 255), makecol(0,0,0), "Position x souris: %d  Position y souris: %d", mouse_x, mouse_y);
        masked_blit(souris, transition, 0,0, mouse_x, mouse_y, souris->w, souris->h);
        blit(transition, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

        if((mouse_y<=410) && (mouse_y>=310)){
                // cas bouton 2 joueurs
                if((mouse_x<=340) && (mouse_x>=70)){
                    cpt = 1;
                    if(mouse_b & 1){
                        *choix = 2;
                    }
                }
                // cas boutons 3 joueurs
                if((mouse_x<=780) && (mouse_x>=508)){
                    cpt = 2;
                    if(mouse_b & 1){
                        *choix = 3;
                    }
                }
                // cas boutons 4 joueurs
                if((mouse_x<=1212) && (mouse_x>=940)){
                    cpt = 3;
                    if(mouse_b & 1){
                        *choix = 4;
                    }
                }
        }
        else{
            //sinon compteur à 0 (souris sur aucun boutons)
            cpt = 0;
        }
    }
    clear_bitmap(transition);
        destroy_bitmap(transition);
}


void afficher_carac_class(BITMAP* police[120], BITMAP* buffer, t_classe c){
    // chaine pr les récupérations
    char pv[4], pa[3], pm[3];
    char pv_t[7], pa_t[6], pm_t[6];

    //remplissage des chaines pr l'affichage
    sprintf(pv, "%d", c.PV_default);
    strcpy(pv_t, "PV:");
    strcat(pv_t, pv);

    sprintf(pa, "%d", c.PA_default);
    strcpy(pa_t, "PA:");
    strcat(pa_t, pa);

    sprintf(pm, "%d", c.PM_default);
    strcpy(pm_t, "PM:");
    strcat(pm_t, pm);

    //print des caractéristiques des personnages en fonction de leurs classes
    printTEXT(buffer, police, pv_t, 180, 400, 0.5);
    printTEXT(buffer, police, pa_t, 180, 420, 0.5);
    printTEXT(buffer, police, pm_t, 180, 440, 0.5);

}


// récupération du fichier classe (passage par adresse du tab de classes de la struct joueur)
// alloc de jeu.joueur après avoir récup le nb de joueur (menu nb joueur)
// création struct player (pas allocation) et remplissage
// saisie du nom du joueur
// regroupement des ss prgrm renvoie struct jeu


/// Remplissage struct player (passage par adresse, allouer dyn le tab de struct player ds struct jeu avec jeu.nbJoueurs)
void crea_player(t_player* p, t_classe c[4], BITMAP* police[120]){
    int type_cla = -1;
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    //appel du ss prgrm pr selec le nom
    saisieNOM(buffer, police, p->nom, 820, 130, c);

    //appel du menu pr choisir sa classe
    menu_classe(&type_cla, police, p->nom, c);

    p->PA = c[type_cla].PA_default;
    p->PM = c[type_cla].PM_default;
    p->PV = c[type_cla].PV_default;


    // remplispsage de la structure player en fonction de sa classe
    p->classe = c[type_cla];
    p->classe.PM_default = c[type_cla].PM_default;
    destroy_bitmap(buffer);
}
///---------------------------------------



/// Remplissage de la structure t_jeu à partir des autres ss prgrm (renvoi la structure)
t_jeu initialisation_complete(BITMAP* police[120], t_jeu partie){
     int i=0;

     recupfichier(partie.tabClasses);
     affichage_class(partie.tabClasses);

     //appel du ss-prgrm pr la sélec du nb de joueurs
     selec_nb_joueurs(&(partie.nbJoueurs), police);

     //allocation dynamique en f° du nb de joueur
     partie.joueur = (t_player*)malloc((partie.nbJoueurs)*sizeof(t_player));

     for(i=0; i<partie.nbJoueurs; i++){

        crea_player(&(partie.joueur[i]), partie.tabClasses, police);

        affichage_struct_player(&(partie.joueur[i]));
     }
    return partie;
}
///--------------------------------------


void saisieNOM(BITMAP* buffer, BITMAP* font[120], char nom[31], int x, int y, t_classe c[4]){
    int touche, touche1, touche2;
    int i = 0;

    BITMAP * cursor = load_bitmap("mouse.bmp",NULL);
    if(!cursor){
        allegro_message("mouse raté fdp");
    }

    //on intialise le nom pour ne pas avoir d'éléments perturbateurs
    for(i=0;i<30;i++){
        nom[i] = 0;
    }

    clear_keybuf();

    clear_bitmap(buffer);
    affichage_menu_cpt(buffer, font, -1, c); //mise en forme du buffer
    //printTEXT(buffer,font, "Bonjour, veuillez entrer votre nom", 100,100,0.5);

    i=0;

    printTEXT(buffer,font,"_",x+i*11, y+3,0.5);
    blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);



    while(!key[KEY_ENTER]){
        clear_bitmap(buffer);
        affichage_menu_cpt(buffer, font, -1, c); //mise en forme du buffer
        //printTEXT(buffer,font, "Bonjour, veuillez entrer votre nom", 100,100,0.5);
        clear_keybuf();
        rest(10);

        touche=readkey();
        touche1=touche & 0xFF; // code ASCII
        touche2=touche >> 8;   // scancode


        //Vérification de la touche enfoncée
        if ( touche2==KEY_BACKSPACE )
        {
            //joueur.nom[i] = " ";
            i--;
            if ( i<0 )
            i=0;
            nom[i] =  0;
            i--;
        }
        if(( touche1>31 && touche1<58) || ( touche1>64 && touche1<123)){
            nom[i] = touche1;
            nom[i+1] = 0;
        }

        printTEXT(buffer,font,nom,x,y,0.5);

        i++;
        if(i >= 30){
            i =30;
        }
        printTEXT(buffer,font,"_",x+i*11, y+3,0.5);
        masked_blit(cursor,buffer,0,0,mouse_x, mouse_y, cursor->w,cursor->h);
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

    }
    destroy_bitmap(cursor);
}


///////////////////////////////////////////////////////////////////POUR DEBUGGER DANS LA CONSOLE

/// Affichage d'une classe
void affichage_one_class(t_classe a){
    printf("\n%d %d %d %d %d %d %d %d %d %d %d %d", (a.type), (a.damage[0]), (a.damage[1]), (a.range_damage[0]), (a.range_damage[1]), (a.sorts[0]), (a.sorts[1]), (a.range_sorts[0]), (a.range_sorts[1]), (a.PM_default), (a.PV_default), (a.PA_default));
}
///-----------------------------

/// Affichage de ttes les classes
void affichage_class(t_classe a[4]){
    int i =0;
    for(i=0; i<4; i++){
        printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", (a[i].type), (a[i].damage[0]), (a[i].damage[1]), (a[i].range_damage[0]), (a[i].range_damage[1]), (a[i].sorts[0]), (a[i].sorts[1]), (a[i].range_sorts[0]), (a[i].range_sorts[1]), (a[i].PM_default), (a[i].PV_default), (a[i].PA_default));
    }
}
///-----------------------------

/// Affichage struct joueur
void affichage_struct_player(t_player* p){
    printf("\nNom: %s", p->nom);
    printf("\nPA: %d", p->PA);
    printf("\nPV: %d", p->PV);
    printf("\nPM: %d", p->PM);

    affichage_one_class(p->classe);
}
///-----------------------------
