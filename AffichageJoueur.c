#include "maBiblio.h"


void affichageAutresJoueurs(BITMAP * buffer,t_jeu regl,int nbfois){
    int i;
    int x,y;
    for(i=0;i<nbfois;i++){
        if(i != regl.tour && regl.joueur[i].estMort == 0){
            convertirPosLARGEPlateau_RealPos2(&x,&y,regl.joueur[i].x,regl.joueur[i].y);
            draw_sprite(buffer,regl.tabClasses[regl.joueur[i].classe.type].animSO[0], x-60,y-52);
        }

    }


}


void affichageJoueurActuel(BITMAP * buffer, t_jeu regl){
    int x,y;
    convertirPosLARGEPlateau_RealPos2(&x,&y,regl.joueur[regl.tour].x,regl.joueur[regl.tour].y);

    circlefill(buffer,x,y+15,10,makecol(87,232,51));
    draw_sprite(buffer,regl.tabClasses[regl.joueur[regl.tour].classe.type].animSO[0], x-60,y-52);

}
