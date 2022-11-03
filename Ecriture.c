#include "maBiblio.h"



void initFont(BITMAP*lettre[120]){
    int i;
    int j;
    BITMAP * font = load_bitmap("Police/font.bmp",NULL);

    for(j=0;j<8;j++){
        for(i=0; i<15; i++){
            lettre[15*j+i]=create_bitmap(40,40);
            blit(font,lettre[15*j+i],i*40,j*40,0,0,40,40);
        }
    }

    //Pour M et N qui sont inversés on sait pas pourquoi mdrr
    blit(font,lettre[15*3],1*40,3*40,0,0,40,40);
    blit(font,lettre[15*3+1],0,3*40,0,0,40,40);


    destroy_bitmap(font);
}


void printTEXT(BITMAP * buffer, BITMAP * font[120], char * chaine, int x, int y, float coef){
    int i;
    int lettre;

    for(i=0;i<strlen(chaine);i++){
        lettre = chaine[i] - 32;
        masked_stretch_blit(font[lettre], buffer, 0,0,40,40,x + (int)((float)22*i*coef), y,(int)(float)(40*coef), (int)(float)(40*coef));
    }

}

void round_rect(BITMAP * buffer,int x,int y,int w,int h, int round, int thick, int edge_color, int inside_color){
    //création des bords

    circlefill(buffer, x+ 0 +round,     y+0 +round,     round, edge_color);
    circlefill(buffer, x+w -round,      y+round,        round, edge_color);
    circlefill(buffer, x+0 +round,      y+h -round,     round, edge_color);
    circlefill(buffer, x+w -round,      y+h -round,     round, edge_color);

    rectfill(buffer, x+0,           y+round,       x+round,       y+h-round,    edge_color);
    rectfill(buffer, x+round,       y+0,           x+w-round,     y+round,      edge_color);
    rectfill(buffer, x+w-round,     y+round,       x+w,           y+h-round,    edge_color);
    rectfill(buffer, x+round,       y+h-round,     x+w-round,     y+h,          edge_color);
    floodfill(buffer,x+w/2,y+h/2,edge_color);

    //création de l'intérieur
    circlefill(buffer, x+0 +round + thick,      y+0 +round +thick,        round, inside_color);
    circlefill(buffer, x+w -round - thick,      y+0 +round +thick,        round, inside_color);
    circlefill(buffer, x+0 +round + thick,      y+h -round -thick,        round, inside_color);
    circlefill(buffer, x+w -round - thick,      y+h -round -thick,        round, inside_color);


    rectfill(buffer, x+thick                ,y+round + thick    ,x+thick+10           ,y+h-round -thick , inside_color);//gauche
    rectfill(buffer, x+w-thick              ,y+round + thick    ,x+w-thick-10         ,y+h-round -thick , inside_color);//droite
    rectfill(buffer, x+round + thick        ,y+thick            ,x+w-round -thick     ,y+thick+10       , inside_color);//haut
    rectfill(buffer, x+round + thick        ,y+h-thick          ,x+w-round -thick     ,y+h-thick-10     , inside_color);//bas

    floodfill(buffer,x+w/2,y+h/2,inside_color);

}


