#include "maBiblio.h"



int showScores(t_jeu regl, BITMAP* buffer, BITMAP* Font[120]){

    BITMAP* box = load_bitmap("menu/tableaufinfinal.bmp", NULL);
    BITMAP* souris = load_bitmap("mouse.bmp", NULL);


    //while(choix!=1 || choix!=2 || choix!=3 ){
    while(!key[KEY_ESC]){
    rectfill(buffer, 0,0,SCREEN_W, SCREEN_H, makecol(255,255,255));
    switch (regl.nbJoueurs){
    case 2 :
        //affichage des 2 cases
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,200, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,400, 800,122);
        printTEXT(buffer, Font, "1", 275, 225, 2);
        printTEXT(buffer, Font, "2", 275, 425, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[0]].nom, 380, 225, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[1]].nom, 380, 425, 2);

        round_rect(buffer, 100, 550, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 500, 550, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 900, 550, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        if(mouse_x > 100 && mouse_x < 400 && mouse_y > 550 && mouse_y <650){
            //change couleur
            round_rect(buffer, 100, 550, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 1;
            }
        }
        if(mouse_x > 500 && mouse_x < 800 && mouse_y > 550 && mouse_y <650){
            //change couleur
            round_rect(buffer, 500, 550, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 2;
            }
        }
        if(mouse_x > 900 && mouse_x < 1200 && mouse_y > 550 && mouse_y <650){
            //change couleur
            round_rect(buffer, 900, 550, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 3;
            }
        }
        printTEXT(buffer, Font, "Quitter", 160,580, 1);
        printTEXT(buffer, Font, "Menu", 585,580,1);
        printTEXT(buffer, Font, "Rejouer",960,580,1);


        break;
    case 3:
        //affichage des 3 cases
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,150, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,300, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,450, 800,122);
        printTEXT(buffer, Font, "1", 275, 175, 2);
        printTEXT(buffer, Font, "2", 275, 320, 2);
        printTEXT(buffer, Font, "3", 275, 470, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[0]].nom, 380, 175, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[1]].nom, 380, 315, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[2]].nom, 380, 475, 2);
        round_rect(buffer, 100, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 500, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 900, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));

        if(mouse_x > 100 && mouse_x < 400 && mouse_y > 550 && mouse_y <700){
            //change couleur
            round_rect(buffer, 100, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 1;
            }
        }
        if(mouse_x > 500 && mouse_x < 800 && mouse_y > 550 && mouse_y <700){
            //change couleur
            round_rect(buffer, 500, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 2;
            }
        }
        if(mouse_x > 900 && mouse_x < 1200 && mouse_y > 550 && mouse_y <700){
            //change couleur
            round_rect(buffer, 900, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 3;
            }
        }
        printTEXT(buffer, Font, "Quitter", 160,630, 1);
        printTEXT(buffer, Font, "Menu", 585,630,1);
        printTEXT(buffer, Font, "Rejouer",960,630,1);
        break;
    case 4:
        //affichage des 4 cases
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,100, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,220, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,340, 800,122);
        masked_stretch_blit(box, buffer, 0,0, box->w, box->h, 250,460, 800,122);
        printTEXT(buffer, Font, "1", 275, 120, 2);
        printTEXT(buffer, Font, "2", 275, 240, 2);
        printTEXT(buffer, Font, "3", 275, 360, 2);
        printTEXT(buffer, Font, "4", 275, 480, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[0]].nom, 380, 135, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[1]].nom, 380, 255, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[2]].nom, 380, 375, 2);
        printTEXT(buffer, Font, regl.joueur[regl.rankTab[3]].nom, 380, 495, 2);
        round_rect(buffer, 100, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 500, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));
        round_rect(buffer, 900, 600, 300, 100, 5, 5, makecol(255,213,40), makecol(209,252,255));

        if(mouse_x > 100 && mouse_x < 400 && mouse_y > 600 && mouse_y <700){
            //change couleur
            round_rect(buffer, 100, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 1;
            }
        }
        if(mouse_x > 500 && mouse_x < 800 && mouse_y > 600 && mouse_y <700){
            //change couleur
            round_rect(buffer, 500, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 2;
            }
        }
        if(mouse_x > 900 && mouse_x < 1200 && mouse_y > 600 && mouse_y <700){
            //change couleur
            round_rect(buffer, 900, 600, 300, 100, 5, 5, makecol(209,252,255), makecol(255,224,154));
            if(mouse_b&1){
                return 3;
            }
        }
        printTEXT(buffer, Font, "Quitter", 160,630, 1);
        printTEXT(buffer, Font, "Menu", 585,630,1);
        printTEXT(buffer, Font, "Rejouer",960,630,1);
        break;
    }
    masked_blit(souris, buffer, 0,0, mouse_x, mouse_y, souris->w, souris->h);
    blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    }


    return 10;
}
