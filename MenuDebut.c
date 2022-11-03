#include "maBiblio.h"


void startAnimation(BITMAP* buffer){

    BITMAP* studio = NULL;
    SAMPLE* loadingmusic = load_sample("menu/One Piece - Whitebeard Theme (Most Epic Theme).wav");
    studio = load_bitmap("menu/studiologo.bmp", NULL);
    play_sample(loadingmusic, 150,128,1000,0);

    rectfill(screen,0,0,SCREEN_W, SCREEN_H, makecol(255,255,255));
    rest(4000);

    //loading screen
    for(int i=0;i<200;++i){
        clear_bitmap(buffer);
        masked_stretch_blit(studio, buffer, 385,929, 1931+5*i,700+5*i, -10+i, 80+i, SCREEN_W, SCREEN_H);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(25);
    }

    rest(5000);
    clear_bitmap(screen);
    rest(4000);
    destroy_bitmap(studio);
    //stop_sample(loadingmusic);
}

////////////////////////////
////////////////////////////

t_jeu startMenu(BITMAP* buffer, BITMAP* Font[120],t_jeu regl){

    BITMAP* fond = NULL;


    BITMAP* tempo = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* menu[4];
    BITMAP* mapmenu = NULL;
    BITMAP * cursor = load_bitmap("mouse.bmp", NULL);
    BITMAP * decor = load_bitmap("cities-skylines.bmp", NULL);
    BITMAP * logo = load_bitmap("menu/ECE_CITY.bmp", NULL);
    SAMPLE* soundboard[2];

    //regl.sampl.smpl = load_sample("menu/One Piece - Whitebeard Theme (Most Epic Theme).wav");


    /////ajout
    BITMAP * RoueCrantee = load_bitmap("parametres/roueCrantee.bmp", NULL);


    int choix=-1;
    int prevstate=0;
    int i;

    menu[0]=load_bitmap("menu/menuf.bmp",NULL);
    menu[1]=load_bitmap("menu/menu1.bmp",NULL);
    menu[2]=load_bitmap("menu/menu2.bmp",NULL);
    menu[3]=load_bitmap("menu/menu3.bmp",NULL);
    mapmenu = load_bitmap("menu/menuback.bmp",NULL);

    decor = load_bitmap("menu/cities-skylines.bmp", NULL);

    soundboard[0] = load_sample("menu/tap.wav");
    soundboard[1] = load_sample("menu/selected.wav");



    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);



    stretch_blit(mapmenu, tempo, 0,0,mapmenu->w, mapmenu->h, 0,0,SCREEN_W, SCREEN_H);


    blit(RoueCrantee, tempo, 0,0,110,180,RoueCrantee->w,RoueCrantee->h);

    //play_sample(regl.sampl.smpl,regl.sampl.vol,regl.sampl.pan,regl.sampl.freq,regl.sampl.loop);

    while(choix==-1){

        if(regl.sampl.loop<=10)
            regl.sampl.loop++;

        clear_bitmap(buffer);

        stretch_blit(decor,buffer,0,0,decor->w, decor->h,0,0,SCREEN_W,SCREEN_H);

        masked_blit(logo,buffer, 0, 0, 320, 50, logo->w, logo->h);




        //rectfill(buffer, 0,0,1280,720,makecol(32,138,187));

        if(mouse_b&1 && mouse_x>=1240 && mouse_x<=1280 && mouse_y <=40 ){
                BITMAP *collVolume;
                collVolume =create_bitmap(SCREEN_W, SCREEN_H);
                BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);

                rest(100);
                regl.fermerParam = 0;
                masked_stretch_blit(menu[0],buffer, 0,0,menu[0]->w, menu[0]->h, 0,0,SCREEN_W, SCREEN_H);
                while(regl.fermerParam == 0){
                    clear_bitmap(temp);
                    blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);

                    regl = parametre(temp,Font,collVolume,regl);
                    masked_blit(cursor, temp, 0,0,mouse_x, mouse_y, 13,19);

                    //blit(buffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);
                    blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                }
                //rest(200);

                while(mouse_b&1);
                destroy_bitmap(collVolume);
                destroy_bitmap(temp);
        }

        if(getpixel(tempo, mouse_x, mouse_y)==makecol(0,255,0)){
                vline(buffer, 260, 220,300,makecol(255,255,255));
                vline(buffer, 1020, 220,300,makecol(255,255,255));
                if(prevstate!=1){
                    stop_sample(soundboard[0]);
                    prevstate=1;
                    play_sample(soundboard[0], 255, 128, 1000, 0);
                }
                textout_ex(buffer, font, "Creer une nouvelle partie.", 20, 690,makecol(255, 255, 255), -1);
                if(mouse_b & 1){
                    play_sample(soundboard[1], 150,128,1000,0);
                    rest(1000);
                    choix = 1;
                }
            masked_stretch_blit(menu[1],buffer, 0,0,menu[1]->w, menu[1]->h, 0,0,SCREEN_W, SCREEN_H);
        }
        else
            if(getpixel(tempo, mouse_x, mouse_y)==makecol(255,255,0)){
                vline(buffer, 260, 355,435,makecol(255,255,255));
                vline(buffer, 1020, 355,435,makecol(255,255,255));
                if(prevstate!=2){
                    stop_sample(soundboard[0]);
                    prevstate=2;
                    play_sample(soundboard[0], 255, 128, 1000, 0);
                }
                textout_ex(buffer, font, "Charger une partie existente.", 20, 690,makecol(255, 255, 255), -1);
                if(mouse_b & 1){
                    play_sample(soundboard[1], 150,128,1000,0);
                    rest(1000);
                    choix = 2;
                }
                masked_stretch_blit(menu[2],buffer, 0,0,menu[2]->w, menu[2]->h, 0,0,SCREEN_W, SCREEN_H);
        }
        else
            if(getpixel(tempo, mouse_x, mouse_y)==makecol(255,0,0)){
                vline(buffer, 260, 490,570,makecol(255,255,255));
                vline(buffer, 1020, 490,570,makecol(255,255,255));
                if(prevstate!=3){
                    stop_sample(soundboard[0]);
                    prevstate=3;
                    play_sample(soundboard[0], 255, 128, 1000, 0);
                }
                textout_ex(buffer, font, "Quitter le jeu. (quelle erreur..)", 20, 690,makecol(255, 255, 255), -1);
                if(mouse_b & 1){
                    play_sample(soundboard[1], 150,128,1000,0);
                    rest(1000);
                    choix = 0;
                }
                masked_stretch_blit(menu[3],buffer, 0,0,menu[3]->w, menu[3]->h, 0,0,SCREEN_W, SCREEN_H);
            }
        else{
            stop_sample(soundboard[1]);
            prevstate=0;
            masked_stretch_blit(menu[0],buffer, 0,0,menu[0]->w, menu[0]->h, 0,0,SCREEN_W, SCREEN_H);
        }
        masked_blit(RoueCrantee, buffer, 0,0,1240,0,RoueCrantee->w,RoueCrantee->h);
        masked_blit(cursor, buffer, 0,0,mouse_x, mouse_y, 13,19);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    destroy_bitmap(RoueCrantee);
    for(i=0;i<4;i++){
        destroy_bitmap(menu[i]);
    }
    destroy_bitmap(tempo);
    destroy_bitmap(mapmenu);
    destroy_bitmap(cursor);
    destroy_sample(soundboard[0]);
    destroy_sample(soundboard[1]);

    regl.choixMenu = choix;
    stop_sample(regl.sampl.smpl);
    destroy_sample(regl.sampl.smpl);
    return regl;

}

