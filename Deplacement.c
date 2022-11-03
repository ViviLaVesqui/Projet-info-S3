#include "maBiblio.h"

t_jeu deplacement(BITMAP * buffer,t_jeu regl){
    int i,okx=0,oky=0;

    int x = regl.joueur[regl.tour].x;           //position du joueur
    int y = regl.joueur[regl.tour].y;

    int dx = regl.joueur[regl.tour].dx;         //futur position du joueur
    int dy = regl.joueur[regl.tour].dy;




    while(x < dx || x > dx || y < dy || y > dy){
        ///si il y a un obstacle (preshot)
        okx = 1;
        if(dx > x){
            for(i=x ; i<dx ; i++){
                if(regl.joueur[regl.tour].tabRange[i][dy] != 0)
                    okx = 0;
            }
        }
        if(dx < x){
            for(i=x ; i>dx ; i--){
                if(regl.joueur[regl.tour].tabRange[i][dy] != 0)
                    okx = 0;
            }
        }

        oky = 1;
        if(dy > y){
            for(i=y ; i<dy ; i++){
                if(regl.joueur[regl.tour].tabRange[dx][i] != 0)
                    oky = 0;
            }

        }
        if(dy < y){
            for(i=y ; i>dy ; i--){
                if(regl.joueur[regl.tour].tabRange[dx][i] != 0)
                    oky = 0;
            }
        }



        if(oky == 1){
            x = regl.joueur[regl.tour].x;           //position du joueur
            y = regl.joueur[regl.tour].y;
            if(dx>x && regl.joueur[regl.tour].tabRange[x+1][y] == 0){
                regl = deplacementX(buffer,regl);
            }
            x = regl.joueur[regl.tour].x;           //position du joueur
            y = regl.joueur[regl.tour].y;
            if(dx<x && regl.joueur[regl.tour].tabRange[x-1][y] == 0){
                regl = deplacementX(buffer,regl);
            }

        }
        if(okx == 1){
            x = regl.joueur[regl.tour].x;           //position du joueur
            y = regl.joueur[regl.tour].y;
            if(dy > y && regl.joueur[regl.tour].tabRange[x][y+1] == 0){
                regl = deplacementY(buffer,regl);
            }
            x = regl.joueur[regl.tour].x;           //position du joueur
            y = regl.joueur[regl.tour].y;
            if(dy < y && regl.joueur[regl.tour].tabRange[x][y-1] == 0){
                regl = deplacementY(buffer,regl);
            }
        }
        if(okx == 0 && oky == 0){
            break;
            regl.joueur[regl.tour].dx = regl.joueur[regl.tour].x;
            regl.joueur[regl.tour].dy = regl.joueur[regl.tour].y;
        }



        x = regl.joueur[regl.tour].x;           //position du joueur
        y = regl.joueur[regl.tour].y;
    }

    //regl.joueur[regl.tour].dx = regl.joueur[regl.tour].x;
    //regl.joueur[regl.tour].dy = regl.joueur[regl.tour].y;

    return regl;
}


t_jeu deplacementX(BITMAP * buffer, t_jeu regl){
    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
    int i;
    int x = regl.joueur[regl.tour].x;           //position du joueur
    int y = regl.joueur[regl.tour].y;

    int dx = regl.joueur[regl.tour].dx;         //futur position du joueur

    int anim = 0;
    int xdess;
    int ydess;

    if(dx > x){
        regl.joueur[regl.tour].x ++;
        printf("\n%d\n", regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][regl.joueur[regl.tour].y]);
        regl.joueur[regl.tour].PM--;
        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,x,y);
        anim = 0;
        for(i=0;i<15;i++){
            rest(25);
            clear_bitmap(temp);
            xdess+=2;
            ydess++;
            anim++;
            if(anim>=8){
                anim=0;
            }

            blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
            //circlefill(temp,xdess + 113,ydess+15 +87,7,makecol(255,255,255));
            //rectfill(temp,xdess-47,ydess-52, xdess-47 + 113, ydess-52 +87, makecol(255,255,255));
            draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].animSO[anim],xdess-60,ydess-52);
            //masked_blit(regl.joueur[regl.tour].classe.animSO[anim], temp, 0,0, xdess-47, ydess-52, 113, 87);///normalement reversed
            blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }

    }
    else if(dx < x){
        regl.joueur[regl.tour].x--;
        regl.joueur[regl.tour].PM--;
        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,x,y);
        printf("\n%d\n", regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][regl.joueur[regl.tour].y]);
        for(i=0;i<15;i++){
            rest(25);
            clear_bitmap(temp);
            xdess-=2;
            ydess--;
            anim++;
            if(anim>=8){
                anim=0;
            }

            blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].animNO[anim],xdess-60,ydess-52);
            //masked_blit(regl.joueur[regl.tour].classe.animNO[0], temp, 0,0, xdess-47, ydess-52, 113, 87);
            //circlefill(temp,xdess + 113,ydess+15 +87,7,makecol(255,255,255));
            //rectfill(temp,xdess-47,ydess-52, xdess-47 + 113, ydess-52 +87, makecol(255,255,255));
            blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
    }


    destroy_bitmap(temp);
    return regl;
}


t_jeu deplacementY(BITMAP * buffer, t_jeu regl){
    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
    int i;
    int x = regl.joueur[regl.tour].x;           //position du joueur
    int y = regl.joueur[regl.tour].y;

    int dy = regl.joueur[regl.tour].dy;         //futur position du joueur

    int anim = 0;
    int xdess ;
    int ydess;
    if(dy > y){
            printf("\n%d\n", regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][regl.joueur[regl.tour].y]);
        regl.joueur[regl.tour].y ++;
        regl.joueur[regl.tour].PM--;
        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,x,y);
        anim = 0;
        for(i=0;i<15;i++){
            rest(25);
            clear_bitmap(temp);
            xdess-=2;
            ydess++;
            anim++;
            if(anim>=8){
                anim=0;
            }

            blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].animSO[anim],xdess-60,ydess-52);
            //masked_blit(regl.joueur[regl.tour].classe.animSO[anim], temp, 0,0, xdess-47, ydess-52, 113, 87);
            //circlefill(temp,xdess + 113,ydess+15 +87,7,makecol(255,255,255));
            //rectfill(temp,xdess-47,ydess-52, xdess-47 + 113, ydess-52 +87, makecol(255,255,255));
            blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }

    }
    else if(dy < y){
            printf("\n%d\n", regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][regl.joueur[regl.tour].y]);
        regl.joueur[regl.tour].y--;
        regl.joueur[regl.tour].PM--;
        convertirPosLARGEPlateau_RealPos2(&xdess,&ydess,x,y);
        anim = 0;
        for(i=0;i<15;i++){
            rest(25);
            clear_bitmap(temp);
            xdess+=2;
            ydess--;
            anim++;
            if(anim>=8){
                anim=0;
            }
            blit(buffer,temp,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite_h_flip(temp,regl.tabClasses[regl.joueur[regl.tour].classe.type].animNO[anim],xdess-60,ydess-52);
            //masked_blit(regl.joueur[regl.tour].classe.animNO[anim], temp, 0,0, xdess-47, ydess-52, 113, 87); ///normalement reversed
            //circlefill(temp,xdess + 113,ydess+15 +87,7,makecol(255,255,255));
            //rectfill(temp,xdess-47,ydess-52, xdess-47 + 113, ydess-52 +87, makecol(255,255,255));
            blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
    }


    destroy_bitmap(temp);
    return regl;
}


int deplacementPossible(BITMAP * coll,t_jeu regl){
    int x = regl.joueur[regl.tour].x;
    int y = regl.joueur[regl.tour].y;
    int r = regl.joueur[regl.tour].Range;
    int i,j;
    int dx,dy;
    convertirPosMouse_PosLARGEPlateau2(&dx,&dy);

    if(getpixel(coll,mouse_x, mouse_y) == makecol(0,75,100) && estenRange(dx,dy,x,y,r) && regl.joueur[regl.tour].tabRange[dx][dy] == 0){
        printf("\ndeplacement : Possible\n");
        printf("\n\n");
        for(i=0;i<16;i++){
            for(j=0;j<16;j++){
                printf(" %d ", regl.joueur[regl.tour].tabRange[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        return 1;
    }
    return 0;


}

t_jeu initPositions(BITMAP * mouse,BITMAP * Font[120],BITMAP * map_collision,t_jeu regl){
    int i,j,l,k;
    int x=-1 ,y=-1 ;
    int x1, y1;
    BITMAP * temp = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(temp);
    for(i=0;i<regl.nbJoueurs;i++){
        regl.tour = i;
        x=-1 ;
        y=-1 ;
        while(x>15 || x<0 || y>15 || y<0){
            clear_bitmap(temp);

            if(mouse_b&1){
                convertirPosMouse_PosLARGEPlateau2(&x,&y);
                regl.joueur[i].x = x;
                regl.joueur[i].dx= x;
                regl.joueur[i].y = y;
                regl.joueur[i].dy= y;
                regl.joueur[i].typeAction = 0;
                regl.joueur[i].estMort = 0;
                if(regl.tabObstacles[x][y] != 0 || (regl.tabMap[x][y]>= 30 && regl.tabMap[x][y] <=33) || x<0 || y<0 || x>15 || y>15){
                    x=-1;
                    y=-1;
                }
                for(k=0;k<i;k++){
                    if(regl.joueur[k].x == x && regl.joueur[k].y==y){
                        x=-1;
                        y=-1;
                    }
                }
                while(mouse_b&1);
            }




            printTEXT(temp,Font,"Chois la case ou tu veux apparaitre ",SCREEN_W/2-355,50,0.7);
            printTEXT(temp,Font,regl.joueur[i].nom,SCREEN_W/2+200,50,0.7);

            masked_blit(regl.mapJeu,temp,0,0,0,0,SCREEN_W,SCREEN_H);

            affichage_LARGEpos2(temp,map_collision);
            affichage_LARGEgrille2(temp);


            detection_LARGEcase2(temp);


            for(l=0;l<16;l++){
                for(j=0;j<16;j++){
                    if(regl.tabObstacles[l][j] != 0 || (regl.tabMap[l][j]>= 30 && regl.tabMap[l][j] <=33)){
                        convertirPosLARGEPlateau_RealPos2(&x1,&y1,l,j);
                        line(temp,x1,y1,x1-30,y1+15,makecol(255,0,0));
                        line(temp,x1,y1,x1+30,y1+15,makecol(255,0,0));
                        line(temp,x1-30,y1+15,x1,y1+30,makecol(255,0,0));
                        line(temp,x1,y1+30,x1+30,y1+15,makecol(255,0,0));
                    }
                }
            }
            for(l=0;l<16;l++){
                for(j=0;j<16;j++){
                    for(k=0;k<i;k++){
                        if(l==regl.joueur[k].x && j==regl.joueur[k].y){
                            convertirPosLARGEPlateau_RealPos2(&x1,&y1,l,j);
                            line(temp,x1,y1,x1-30,y1+15,makecol(255,0,0));
                            line(temp,x1,y1,x1+30,y1+15,makecol(255,0,0));
                            line(temp,x1-30,y1+15,x1,y1+30,makecol(255,0,0));
                            line(temp,x1,y1+30,x1+30,y1+15,makecol(255,0,0));
                        }
                    }
                }
            }
            affichageAutresJoueurs(temp,regl,i+1);
            convertirPosMouse_PosLARGEPlateau2(&x1,&y1);
            masked_blit(mouse,temp,0,0,mouse_x,mouse_y,mouse->w,mouse->h);
            blit(temp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }


    }
    destroy_bitmap(temp);
    return regl;
}






