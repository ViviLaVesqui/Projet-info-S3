#include "maBiblio.h"
///Initialisation des boutons du jeu
void initBoutonA(BITMAP*bouton_jeu[17]){
    int i;

    BITMAP * BoutonA = load_bitmap("bouton/BoutonAttaque.bmp",NULL);


    for(i=0; i<17; i++)
    {
        bouton_jeu[i]=create_bitmap(40,40);
        blit(BoutonA,bouton_jeu[i],i*40,0,0,0,40,40);
    }

    destroy_bitmap(BoutonA);

}
void initBoutonJ(BITMAP*bouton_jeu[17]){
    int i;

    BITMAP * BoutonA = load_bitmap("bouton/BoutonJaune.bmp",NULL);


    for(i=0; i<17; i++)
    {
        bouton_jeu[i]=create_bitmap(40,40);
        blit(BoutonA,bouton_jeu[i],i*40,0,0,0,40,40);
    }

    destroy_bitmap(BoutonA);

}
///initialiser la map de collision de l'ATH



void touche_bouton(BITMAP* buffer,BITMAP * ath_collision,t_jeu regl,BITMAP * Font[120])
{
    BITMAP *notice;
    BITMAP * ath_graph = create_bitmap(SCREEN_W,SCREEN_H);
    notice=load_bitmap("bouton/notice.bmp",NULL);
    clear_bitmap(ath_graph);
    floodfill(ath_graph,100,100,makecol(255,0,255));
    char mot[20];

    ///COURIR

    //textprintf(buffer, font,10,600,makecol(255,255,255),"compteur  : %d", a);
     if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(255,255,0)){


        //draw_sprite(ath_graph,notice,780,600);//courir
        //textout_ex(buffer, font, "DESSUS.", 20, 690,makecol(255, 255, 255), -1);
        masked_stretch_blit(notice,ath_graph,0,0,93,47,760,595,140,70);
        sprintf(mot,"Cout en PM");
        printTEXT(ath_graph,Font,"Deplacement", 770,601,0.4);
        printTEXT(ath_graph,Font,mot, 770,618,0.4);


    }
    ///CORPS A CORPS
     else if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(255,0,0)){


        //draw_sprite(ath_graph,notice,530,600);//corps
        masked_stretch_blit(notice,ath_graph,0,0,93,47,510,595,140,70);
        sprintf(mot,"%d -> 2PA", regl.joueur[regl.tour].classe.corpsacorps);
        printTEXT(ath_graph,Font,"Corps a Corps", 520,601,0.4);
        printTEXT(ath_graph,Font,mot, 520,618,0.4);

    }
    ///GUERIR
    else if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,255,0)){

        //draw_sprite(ath_graph,notice,580,600);//guerir
        masked_stretch_blit(notice,ath_graph,0,0,93,47,560,595,140,70);
        sprintf(mot,"+%dPV -> 5PA", regl.joueur[regl.tour].classe.sorts[0]);
        printTEXT(ath_graph,Font,"Guerison", 570,601,0.4);
        printTEXT(ath_graph,Font,mot, 570,618,0.4);

    }
    ///SORT PROCHE
    else if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,0,255)){

        //textout_ex(buffer, font, "PRO 1.", 20, 690,makecol(255, 255, 255), -1);
        //draw_sprite(ath_graph,notice,630,600);//proche
        masked_stretch_blit(notice,ath_graph,0,0,93,47,610,595,140,70);
        sprintf(mot,"%dPV -> 3PA", regl.joueur[regl.tour].classe.damage[0]);
        printTEXT(ath_graph,Font,"Attaque 1", 620,601,0.4);
        printTEXT(ath_graph,Font,mot, 620,618,0.4);


    }
    ///SORT LOIN
    else if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,255,255)){


        //textout_ex(buffer, font, "L.", 20, 690,makecol(255, 255, 255), -1);
        //draw_sprite(ath_graph,notice,680,600);//loin
        masked_stretch_blit(notice,ath_graph,0,0,93,47,660,595,140,70);
        sprintf(mot,"%dPV -> 4PA", regl.joueur[regl.tour].classe.damage[1]);
        printTEXT(ath_graph,Font,"Attaque 2", 670,601,0.4);
        printTEXT(ath_graph,Font,mot, 670,618,0.4);


    }
    ///SORT PUISSANT
    else if(getpixel(ath_collision, mouse_x, mouse_y)==makecol(155,0,255)){

        //draw_sprite(ath_graph,notice,730,600);//puissant
        masked_stretch_blit(notice,ath_graph,0,0,93,47,710,595,140,70);
        sprintf(mot,"%dPV -> 6PA", regl.joueur[regl.tour].classe.sorts[1]);
        printTEXT(ath_graph,Font,"Sort Puissant", 720,601,0.4);
        printTEXT(ath_graph,Font,mot, 720,618,0.4);


    }
    masked_blit(ath_graph,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

    destroy_bitmap(notice);
    destroy_bitmap(ath_graph);
}
 void affichage_livre(BITMAP*buffer,BITMAP *ath_collision,t_jeu regl,BITMAP * Font[120])
{

    BITMAP *panneauInfo;

    char info[20];

    panneauInfo=load_bitmap("persoJeu/panneauInfo.bmp",NULL);
///notice
    switch(regl.joueur[regl.tour].livre)
    {
    case 0:
        {
            rectfill(buffer,150,0,475,200,makecol(255,0,255)); //barre menu en haut a droite
            break;
        }
    case 1:
        {
            draw_sprite(buffer,panneauInfo,150,0);
            sprintf(info,"PV max: %d", regl.joueur[regl.tour].classe.PV_default);
            printTEXT(buffer,Font,info,220,40,0.6);
            sprintf(info,"PA max: %d", regl.joueur[regl.tour].classe.PA_default);
            printTEXT(buffer,Font,info,220,70,0.6);
            sprintf(info,"PM max: %d", regl.joueur[regl.tour].classe.PM_default);
            printTEXT(buffer,Font,info,220,100,0.6);
            break;
        }
    }
    destroy_bitmap(panneauInfo);

}

t_jeu detectionTypeAction_etProfil(BITMAP * ath_collision,t_jeu regl)
{


        ///notice livre
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(255,155,5))&&(mouse_b&1) )
        {
            regl.joueur[regl.tour].livre=1;
            while(mouse_b&1){}

        }
        if((getpixel(ath_collision, mouse_x, mouse_y)!=makecol(255,155,5)))
        {
            regl.joueur[regl.tour].livre=0;

        }
            ///courir
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(255,255,0))&& (mouse_b&1))
        {
            regl.joueur[regl.tour].typeAction=0;
            while(mouse_b&1){}
        }
        ///corps à corps
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(255,0,0))&& (mouse_b&1))
        {

            regl.joueur[regl.tour].typeAction=1;
            while(mouse_b&1){}
        }
        ///guerir
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,255,0))&& (mouse_b&1))
        {

            regl.joueur[regl.tour].typeAction=2;
            while(mouse_b&1){}
        }
        ///proche
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,0,255))&& (mouse_b&1))
        {

           regl.joueur[regl.tour].typeAction=3;
            while(mouse_b&1){}
        }
        ///loin
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(0,255,255))&&(mouse_b&1) )
        {
            regl.joueur[regl.tour].typeAction=4;
            while(mouse_b&1){}
        }
        ///puissant
        if((getpixel(ath_collision, mouse_x, mouse_y)==makecol(155,0,255))&&( mouse_b&1))
        {
            regl.joueur[regl.tour].typeAction=5;
            while(mouse_b&1){}
        }


        return regl;
}
void affichage_boutons_selection(t_jeu regl,BITMAP*map_collision,BITMAP*ath_collision,BITMAP*buffer){
    BITMAP *bandeau;
    BITMAP *sablier;
    BITMAP *suivant;
    BITMAP *boutonA[17];
    BITMAP *boutonJ[17];
    int i;
    initBoutonA(boutonA);
    initBoutonJ(boutonJ);

    suivant=load_bitmap("bouton/Suivant.bmp",NULL);
    sablier=load_bitmap("bouton/sablier.bmp",NULL);
    bandeau=load_bitmap("bouton/bande.bmp",NULL);
    //touche_bouton(buffer,ath_collision,map_collision);
    ///Bandeau sablier suivant
    masked_blit(bandeau,map_collision,0,0,300, SCREEN_H-100,bandeau->w,bandeau->h);
    draw_sprite(map_collision,sablier,310, SCREEN_H-95);
    draw_sprite(map_collision,suivant,920, SCREEN_H-75);
    ///afficahge de tous les boutons

    //round_rect(buffer, 554, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 558, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[0], 560, SCREEN_H-70,boutonA[0]->w, boutonA[0]->h);

            //round_rect(buffer, 605, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 609, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[0]], 610, SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[0]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[0]]->h);

            //round_rect(buffer, 654, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 660, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[1]],660 , SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[1]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[1]]->h);

            //round_rect(buffer, 704, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 708, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[2]],710 , SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[2]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[2]]->h);

            //round_rect(buffer, 754, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 758, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[3]], 760, SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[3]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[3]]->h);

            //round_rect(buffer, 806, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 810, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[16], 810, SCREEN_H-70,boutonA[16]->w, boutonA[16]->h);






    ///affichage du bouton en jaune
    switch(regl.joueur[regl.tour].typeAction){

    case 0:
        {
            round_rect(map_collision, 810, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[16], 810, SCREEN_H-70,boutonJ[16]->w, boutonJ[16]->h);
            break;
        }
    case 1:
        {
            round_rect(map_collision, 558, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[0], 560, SCREEN_H-70,boutonJ[0]->w, boutonJ[0]->h);
            break;
        }
    case 2:
        {

            round_rect(map_collision, 609, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[regl.joueur[regl.tour].classe.pouvoir[0]], 610, SCREEN_H-70,boutonJ[regl.joueur[regl.tour].classe.pouvoir[0]]->w, boutonJ[regl.joueur[regl.tour].classe.pouvoir[0]]->h);
            break;
        }

    case 3:
        {
            //round_rect(buffer, 654, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 660, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[regl.joueur[regl.tour].classe.pouvoir[1]],660 , SCREEN_H-70,boutonJ[regl.joueur[regl.tour].classe.pouvoir[1]]->w, boutonJ[regl.joueur[regl.tour].classe.pouvoir[1]]->h);
            break;
        }
    case 4:
        {
            //round_rect(buffer, 704, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 708, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[regl.joueur[regl.tour].classe.pouvoir[2]],710 , SCREEN_H-70,boutonJ[regl.joueur[regl.tour].classe.pouvoir[2]]->w, boutonJ[regl.joueur[regl.tour].classe.pouvoir[2]]->h);
            break;
        }
    case 5:
        {
            //round_rect(buffer, 754, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 758, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonJ[regl.joueur[regl.tour].classe.pouvoir[3]], 760, SCREEN_H-70,boutonJ[regl.joueur[regl.tour].classe.pouvoir[3]]->w, boutonJ[regl.joueur[regl.tour].classe.pouvoir[3]]->h);
            break;
        }

    default:
        {
            ///afficahge de tous les boutons

            //round_rect(buffer, 554, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 558, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[0], 560, SCREEN_H-70,boutonA[0]->w, boutonA[0]->h);

            //round_rect(buffer, 605, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 609, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[0]], 610, SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[0]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[0]]->h);

            //round_rect(buffer, 654, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 660, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[1]],660 , SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[1]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[1]]->h);

            //round_rect(buffer, 704, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 708, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[2]],710 , SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[2]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[2]]->h);

            //round_rect(buffer, 754, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 758, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[regl.joueur[regl.tour].classe.pouvoir[3]], 760, SCREEN_H-70,boutonA[regl.joueur[regl.tour].classe.pouvoir[3]]->w, boutonA[regl.joueur[regl.tour].classe.pouvoir[3]]->h);

            //round_rect(buffer, 806, SCREEN_H-75, 50, 50, 5, 2, makecol(64,40,24), makecol(94,53,31));
            round_rect(map_collision, 810, SCREEN_H-71, 40, 40, 5, 2, makecol(64,40,24), makecol(105,71,42));
            stretch_sprite(map_collision, boutonA[16], 810, SCREEN_H-70,boutonA[16]->w, boutonA[16]->h);
                break;
        }


    }

    destroy_bitmap(bandeau);
    destroy_bitmap(sablier);
    destroy_bitmap(suivant);
    for(i=0;i<17;i++){
        destroy_bitmap(boutonA[i]);
        destroy_bitmap(boutonJ[i]);
    }


}
t_jeu remplissageDesPouvoir_etProfil(t_jeu regl,BITMAP*map_collision)
{
    BITMAP *panneau;
    BITMAP *sorciere;
    BITMAP *cuisiniere;
    BITMAP *archer;
    BITMAP *demon;
    BITMAP *info;


    panneau=load_bitmap("persoJeu/Panneau.bmp",NULL);
    sorciere=load_bitmap("persoJeu/sorciere.bmp",NULL);
    cuisiniere=load_bitmap("persoJeu/cuisiniere.bmp",NULL);
    demon=load_bitmap("persoJeu/demon.bmp",NULL);
    archer=load_bitmap("persoJeu/archer.bmp",NULL);
    info=load_bitmap("persoJeu/info.bmp",NULL);


    masked_blit(panneau,map_collision,0,0,0, 0,panneau->w,panneau->h);

    draw_sprite(map_collision,info,100,15);
    ///demon
    if(regl.joueur[regl.tour].classe.type==0)
    {

        draw_sprite(map_collision,demon,0,26);
        //guerrison
        regl.joueur[regl.tour].classe.pouvoir[0]=13;
        //sort proche
        regl.joueur[regl.tour].classe.pouvoir[1]=11;
        //sort loin
        regl.joueur[regl.tour].classe.pouvoir[2]=1;
        //sort puissant
        regl.joueur[regl.tour].classe.pouvoir[3]=14;
    }
    ///archer
    else if(regl.joueur[regl.tour].classe.type==1)
    {

        draw_sprite(map_collision,archer,25,26);
        //guerrison
        regl.joueur[regl.tour].classe.pouvoir[0]=15;
        //sort proche
        regl.joueur[regl.tour].classe.pouvoir[1]=2;
        //sort loin
        regl.joueur[regl.tour].classe.pouvoir[2]=3;
        //sort puissant
        regl.joueur[regl.tour].classe.pouvoir[3]=4;
    }
    ///maid
    else if(regl.joueur[regl.tour].classe.type==2)
    {

        draw_sprite(map_collision,cuisiniere,40,26);
        //guerrison
        regl.joueur[regl.tour].classe.pouvoir[0]=8;
        //sort proche
        regl.joueur[regl.tour].classe.pouvoir[1]=5;
        //sort loin
        regl.joueur[regl.tour].classe.pouvoir[2]=10;
        //sort puissant
        regl.joueur[regl.tour].classe.pouvoir[3]=7;
    }
    ///witch
    else if(regl.joueur[regl.tour].classe.type==3)
    {
        draw_sprite(map_collision,sorciere,25,28);
        //guerrison
        regl.joueur[regl.tour].classe.pouvoir[0]=13;
        //sort proche
        regl.joueur[regl.tour].classe.pouvoir[1]=6;
        //sort loin
        regl.joueur[regl.tour].classe.pouvoir[2]=12;
        //sort puissant
        regl.joueur[regl.tour].classe.pouvoir[3]=9;
    }

    destroy_bitmap(panneau);
    destroy_bitmap(sorciere);
    destroy_bitmap(cuisiniere);
    destroy_bitmap(archer);
    destroy_bitmap(demon);
    destroy_bitmap(info);
    return regl;
}

