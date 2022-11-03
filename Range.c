#include "maBiblio.h"



t_jeu refreshRange(t_jeu regl){
    int i,j,k;
    int x = regl.joueur[regl.tour].x;
    int y = regl.joueur[regl.tour].y;
    int m,n;
    int dx,dy;
    int okx,oky;
    int range;

    switch (regl.joueur[regl.tour].typeAction){
        case 0:
            regl.joueur[regl.tour].Range = regl.joueur[regl.tour].PM;
            range = regl.joueur[regl.tour].Range;
            ///mise en place de la range disponible
            for(i=0;i<16;i++){//parcours du tableau
                for(j=0;j<16;j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                    if(estenRange(i,j,x,y,range)){      ///si la case est dans la range
                        regl.joueur[regl.tour].tabRange[i][j] = 0;///alors la case est jouable
                    }
                }
            }

            ///ajout au tableau de range les éléments tels que la riviere ou les objets
            for(i=0;i<16;i++){
                for(j=0;j<16;j++){
                    ///pour les obstacles (cactus, buisson)
                    if(regl.tabObstacles[i][j] != 0)
                        regl.joueur[regl.tour].tabRange[i][j] = 2;  ///si il y a un obstacle
                    if(regl.tabMap[i][j] >= 30 && regl.tabMap[i][j] <= 33)
                        regl.joueur[regl.tour].tabRange[i][j] = 3;  ///si il y a de l'eau
                }
            }




            ///
            //RAJOUTER SI IL Y A UNE DROITE DE CASE IMPOSSIBLES
            ///

            ///pour empecher d'aller sur la case d'un joueur
            for(i=0;i<16;i++){
                for(j=0;j<16;j++){
                    for(k=0;k<regl.nbJoueurs;k++){
                        if(k != regl.tour && i == regl.joueur[k].x && j == regl.joueur[k].y){
                            regl.joueur[regl.tour].tabRange[i][j] = 4;
                        }
                    }
                }
            }
            ///pour les cases derriere le joueur si il est alligné
            for(k=0;k<regl.nbJoueurs;k++){
                if(k!=regl.tour){
                    if(regl.joueur[k].x == regl.joueur[regl.tour].x){
                        if(regl.joueur[k].y > regl.joueur[regl.tour].y){
                            for(i=regl.joueur[k].y ; i<regl.joueur[regl.tour].y + range;i++){
                                if(i<16){
                                    regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][i] = 1;
                                }
                            }
                        }
                        if(regl.joueur[k].y < regl.joueur[regl.tour].y){
                            for(i=regl.joueur[k].y ; i>regl.joueur[regl.tour].y - range ; i--){
                                if(i>=0){
                                    regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][i] = 1;
                                }
                            }
                        }
                    }
                    if(regl.joueur[k].y == regl.joueur[regl.tour].y){
                        if(regl.joueur[k].x > regl.joueur[regl.tour].x){
                            for(i=regl.joueur[k].x ; i<regl.joueur[regl.tour].x + range ; i++){
                                if(i<16){
                                    regl.joueur[regl.tour].tabRange[i][regl.joueur[regl.tour].y] = 1;
                                }
                            }
                        }
                        if(regl.joueur[k].x < regl.joueur[regl.tour].x){
                            for(i=regl.joueur[k].x ; i>regl.joueur[regl.tour].x - range; i--){
                                if(i>=0){
                                    regl.joueur[regl.tour].tabRange[i][regl.joueur[regl.tour].y] = 1;
                                }
                            }
                        }
                    }
                }
            }
             ///POUR LES OBJETS ALIGNES AVEC LE JOUEUR
            for(i=0;i<16;i++){
                for(j=0;j<16;j++){
                    if(estenRange(i,j,x,y,range) && regl.joueur[regl.tour].tabRange[i][j] != 0){
                        if(y == j){
                            if(i>x){
                                for(k=i;k<=x+range;k++){
                                    if(k<16){
                                        regl.joueur[regl.tour].tabRange[k][j] = 1;
                                    }
                                }
                            }
                            if(i<x){
                                for(k=i;k>=x-range;k--){
                                    if(k>=0){
                                        regl.joueur[regl.tour].tabRange[k][j] = 1;
                                    }
                                }
                            }
                        }
                        if(x == i){
                            if(y>j){
                                for(k=j;k>=y-range;k--){
                                    if(k>=0){
                                        regl.joueur[regl.tour].tabRange[i][k] = 1;
                                    }
                                }
                            }
                            if(y<j){
                                for(k=j;k<=y+range;k++){
                                    if(k<16){
                                        regl.joueur[regl.tour].tabRange[i][k] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for(m=0;m<16;m++){
                for(n=0;n<16;n++){
                    okx = 1;
                    dx = m;
                    dy = n;
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


                    if(okx == 0 && oky == 0){
                        regl.joueur[regl.tour].tabRange[dx][dy] = 1;
                    }



                    x = regl.joueur[regl.tour].x;           //position du joueur
                    y = regl.joueur[regl.tour].y;
                }
            }



            break;

        case 1 :
            range = 1;
            regl.joueur[regl.tour].Range = 1;
            for(i=0; i<16 ;i++){
                for(j=0; j<16; j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                }
            }

            for(i=0;i<regl.nbJoueurs; i++){
                if(i!=regl.tour  && estenRange(regl.joueur[i].x,regl.joueur[i].y,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y,regl.joueur[regl.tour].Range)){
                    regl.joueur[regl.tour].tabRange[regl.joueur[i].x][regl.joueur[i].y] = 0;
                }
            }

            break;
        case 2:
            regl.joueur[regl.tour].Range = 0;
            for(i=0; i<16 ;i++){
                for(j=0; j<16; j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                }
            }
            regl.joueur[regl.tour].tabRange[regl.joueur[regl.tour].x][regl.joueur[regl.tour].y] = 0;
            break;
        case 3:
            range = regl.joueur[regl.tour].classe.range_damage[0];
            regl.joueur[regl.tour].Range = regl.joueur[regl.tour].classe.range_damage[0];
            for(i=0; i<16 ;i++){
                for(j=0; j<16; j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                }
            }
            for(i=0;i<regl.nbJoueurs; i++){
                if(i!=regl.tour  && estenRange(regl.joueur[i].x,regl.joueur[i].y,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y,regl.joueur[regl.tour].Range)){
                    regl.joueur[regl.tour].tabRange[regl.joueur[i].x][regl.joueur[i].y] = 0;
                }
            }
            break;
        case 4:
            range = regl.joueur[regl.tour].classe.range_damage[1];
            regl.joueur[regl.tour].Range = regl.joueur[regl.tour].classe.range_damage[1];
            for(i=0; i<16 ;i++){
                for(j=0; j<16; j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                }
            }
            for(i=0;i<regl.nbJoueurs; i++){
                if(i!=regl.tour  && estenRange(regl.joueur[i].x,regl.joueur[i].y,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y,regl.joueur[regl.tour].Range)){
                    regl.joueur[regl.tour].tabRange[regl.joueur[i].x][regl.joueur[i].y] = 0;
                }
            }
            break;
        case 5:
            range = regl.joueur[regl.tour].classe.range_sorts[1];
            regl.joueur[regl.tour].Range = regl.joueur[regl.tour].classe.range_sorts[1];
            for(i=0; i<16 ;i++){
                for(j=0; j<16; j++){
                    regl.joueur[regl.tour].tabRange[i][j] = 1;
                }
            }
            for(i=0;i<regl.nbJoueurs; i++){
                if(i!=regl.tour && estenRange(regl.joueur[i].x,regl.joueur[i].y,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y,regl.joueur[regl.tour].Range)){
                    regl.joueur[regl.tour].tabRange[regl.joueur[i].x][regl.joueur[i].y] = 0;
                }
            }
            break;

    }


    return regl;
}


int estenRange(int i, int j, int x, int y, int r){
    if(i<=x && i>=x-r){
        if(j<=y+r && j>=y){
            if((x-i+j-y)<=r)
                return 1;
        }
        if(j>=y-r && j<=y){
            if((x-i+y-j)<=r)
                return 1;
        }
    }
    if(i>=x && i<=x+r){
        if(j<=y+r && j>=y){
            if((i-x+j-y)<=r)
                return 1;
        }
        if(j>=y-r && j<=y){
            if((i-x+y-j)<=r)
                return 1;
        }
    }

    return 0;
}


void affichageRange(BITMAP * buffer, t_jeu regl){
    int i,j;
    int x,y;    //positions ou il faut afficher
    int ax = regl.joueur[regl.tour].x;//positions du joueur
    int ay = regl.joueur[regl.tour].y;

    int r = regl.joueur[regl.tour].Range;   //range disponible

    int vert = makecol(0,255,0);
    int rouge = makecol(255,0,0);

    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            if(regl.joueur[regl.tour].tabRange[i][j] == 0){
                convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                line(buffer,x,y,x-30,y+15,vert);
                line(buffer,x,y,x+30,y+15,vert);
                line(buffer,x-30,y+15,x,y+30,vert);
                line(buffer,x,y+30,x+30,y+15,vert);
            }
        }
    }
    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            if(estenRange(i,j,ax,ay,r) && regl.joueur[regl.tour].tabRange[i][j] !=0){
                convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                line(buffer,x,y,x-30,y+15,rouge);
                line(buffer,x,y,x+30,y+15,rouge);
                line(buffer,x-30,y+15,x,y+30,rouge);
                line(buffer,x,y+30,x+30,y+15,rouge);
            }
        }
    }

    if(regl.joueur[regl.tour].typeAction != 0){
        for(i=0;i<16;i++){
            for(j=0;j<16;j++){
                if(regl.joueur[regl.tour].tabRange[i][j] == 0){
                    convertirPosLARGEPlateau_RealPos2(&x,&y,i,j);
                    line(buffer,x,y,x-30,y+15,vert);
                    line(buffer,x,y,x+30,y+15,vert);
                    line(buffer,x-30,y+15,x,y+30,vert);
                    line(buffer,x,y+30,x+30,y+15,vert);
                }
            }
        }
    }

}
