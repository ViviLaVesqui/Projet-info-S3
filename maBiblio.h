#ifndef MABIBLIO_H_INCLUDED
#define MABIBLIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <unistd.h>

#define MARGEX 220
#define MARGEY 150


typedef struct classe{
    int type;   //0, 1,2 ou 3 pour identifier la classe choisie

    int corpsacorps;

    int damage[2];
    int range_damage[2];

    int sorts[2];
    int range_sorts[2];

    int PM_default; //points de mouvement par défaut
    int PV_default; //points de vie par défaut
    int PA_default; //points d'attaque par défaut

    int pouvoir[4];

    BITMAP * animNO[8];
    BITMAP * animSO[8];
    BITMAP * mort[16];
    int nbAnimationsAttaque;
    BITMAP ** attaqueNO;
    BITMAP ** attaqueSO;

}t_classe;

typedef struct player{
    char nom[31];
    int podium;
    int x,y;
    int dx, dy;

    int PV; //points de vie
    int PM; //points de mouvement
    int PA; //points d'attaque

    int typeAction; //0 pour courir 1 corps 2 guerison 3 proche 4 loin 5 puissant
    int livre;
    int Range;
    int tabRange[16][16]; //0 si la case est jouable, 1 si elle est hors de portée, 2 si il y a un obstacle, 3 si il y a de l'eau, 4 si il y a un joueur dessus
    t_classe classe;

    int estMort;
}t_player;

typedef struct sample{
    SAMPLE * smpl;
    float vol;
    int pan;
    int freq;
    int loop;
    int xm;
    int on;
}t_sample;



typedef struct chronometre{
    char time[50];
    int chrono;
    int tpsRestant;
    clock_t timer;
    clock_t prevtime;
    double intervalle;

}t_chrono;

typedef struct jeu{
    int * rankTab;
    int attendreScore;
    int enJeu;
    int tour;
    int affichage;//si 1 : plein écran sinon si -1 : fenetré
    int nbJoueurs;
    int choixMenu;
    int fermerParam;
    int quit;
    t_sample sampl;
    t_player * joueur;
    t_classe tabClasses[4];
    int tabObstacles[16][16];
    int tabMap[16][16];
    BITMAP * mapJeu;
    t_chrono chrono;
}t_jeu;

///Init_______________________________________________________________________________________
void basicInit();
void recupfichier(t_classe tab[4]);
t_jeu nouvPartie(BITMAP * buffer, BITMAP * font[120],t_jeu regl);
t_jeu initTabMap(t_jeu regl);
t_jeu initMapJeu(t_jeu regl);
t_jeu initTabObstacles(t_jeu regl);
void afficher_charg(BITMAP* buffer, BITMAP* police[120], int cpt);
void selec_charg(int* choix, BITMAP* Font[120]);
t_jeu chargementGlobal(t_jeu regl,int cpt);
t_jeu chargement(t_jeu regl,int nbr,int cpt);
int premierChargement(int cpt);
///___________________________________________________________________________________________





///MenuDebut___________________________________________________________________________________
void startAnimation(BITMAP* buffer);
t_jeu startMenu(BITMAP* buffer, BITMAP* Font[120],t_jeu regl);
///____________________________________________________________________________________________






///MenuSelection_______________________________________________________________________________
void affichage_menu_cpt(BITMAP* buffer, BITMAP* police[120], int cpt, t_classe c[4]);
void menu_classe(int* t, BITMAP* police[120], char nom[30], t_classe c[4]);
void affichage_nbjoueur_cpt(BITMAP* buffer, BITMAP* Font[120], int cpt);
void selec_nb_joueurs(int* choix, BITMAP* Font[120]);
void afficher_carac_class(BITMAP* police[120], BITMAP* buffer, t_classe c);

void crea_player(t_player* p, t_classe c[4], BITMAP* police[120]);
t_jeu initialisation_complete(BITMAP* police[120], t_jeu partie);

void saisieNOM(BITMAP* buffer, BITMAP* font[120], char nom[31], int x, int y, t_classe c[4]);
//débug
void affichage_struct_player(t_player* p);
void affichage_one_class(t_classe a);
void affichage_class(t_classe a[4]);

///____________________________________________________________________________________________






///Parametre___________________________________________________________________________________
t_sample bouton_volume(BITMAP * buffer,BITMAP * collVolume, t_sample sampl, BITMAP * Font[120]);
t_jeu screenMode(BITMAP * buffer, BITMAP * Font[120], t_jeu regl);
t_jeu quitter(BITMAP * buffer, BITMAP * Font[120], t_jeu regl);
t_jeu sauvegarder(BITMAP * buffer,BITMAP * Font[120],t_jeu regl);
t_jeu fermerParam(BITMAP * buffer,t_jeu regl);
t_jeu parametre(BITMAP * buffer, BITMAP * Font[120],BITMAP * collVolume,t_jeu regl);
void menu_et_sauvegarde(BITMAP* buffer, BITMAP* police[120], t_jeu regl);
void sauvegarde_en_cours(BITMAP* buffer, BITMAP* police[120]);
void afficher_menu_sauvegarde(BITMAP* buffer, BITMAP* police[120], int cpt);
///____________________________________________________________________________________________





///GrilleEtATH_________________________________________________________________________________
void affichage_LARGEgrille2(BITMAP * buffer);
void detection_LARGEcase2(BITMAP * buffer);
void convertirPosMouse_PosLARGEPlateau2(int * x, int * y);
void convertirPosLARGEPlateau_RealPos2(int * x, int *y, int xPlateau, int yPlateau);
void affichage_LARGEpos2(BITMAP * buffer,BITMAP * map_collision);
void affichage_LARGEcaseDeplacement(BITMAP * buffer,int xP,int yP);

void init_ATH(BITMAP * buffer);
void init_MAPCollPlateau(BITMAP * buffer);
int detection_map(BITMAP * map_collision);
void afficher_carac_autres_joueurs(BITMAP* buffer, BITMAP* police[120], t_jeu regl);
void afficher_carac_player2(BITMAP* buffer, BITMAP* police[120], t_player p, float coef, int x, int y);
///____________________________________________________________________________________________





///Ecriture____________________________________________________________________________________
void initFont(BITMAP*lettre[120]);
void printTEXT(BITMAP * buffer, BITMAP * font[120], char * chaine, int x, int y, float coef);
void round_rect(BITMAP * buffer,int x,int y,int w,int h, int round, int thick, int edge_color, int inside_color);
///____________________________________________________________________________________________



///Range_______________________________________________________________________________________
t_jeu refreshRange(t_jeu regl);
int estenRange(int i, int j, int x, int y, int r);
void affichageRange(BITMAP * buffer, t_jeu regl);
///____________________________________________________________________________________________



///Deplacement_________________________________________________________________________________
t_jeu deplacement(BITMAP * buffer,t_jeu regl);
t_jeu deplacementX(BITMAP * buffer, t_jeu regl);
t_jeu deplacementY(BITMAP * buffer, t_jeu regl);
int deplacementPossible(BITMAP * coll,t_jeu regl );
t_jeu initPositions(BITMAP * mouse,BITMAP * Font[120],BITMAP * map_collision,t_jeu regl);
///____________________________________________________________________________________________


///AffichageJoueur_____________________________________________________________________________
void affichageAutresJoueurs(BITMAP * buffer,t_jeu regl,int nbfois);
void affichageJoueurActuel(BITMAP * buffer, t_jeu regl);
///____________________________________________________________________________________________

///POUVOIR_____________________________________________________________________________________
    void initBoutonA(BITMAP*bouton_jeu[17]);
    void initBoutonJ(BITMAP*bouton_jeu[17]);
//Fonction pouvoir et profil
    t_jeu detectionTypeAction_etProfil(BITMAP * ath_collision,t_jeu regl);
    void touche_bouton(BITMAP* buffer,BITMAP * ath_collision,t_jeu regl,BITMAP * Font[120]);
    void affichage_livre(BITMAP*buffer,BITMAP *ath_collision,t_jeu regl,BITMAP * Font[120]);
    void affichage_boutons_selection(t_jeu regl,BITMAP*map_collision,BITMAP*ath_collision,BITMAP*buffer);
    t_jeu remplissageDesPouvoir_etProfil(t_jeu regl,BITMAP*map_collision);
    t_jeu affichage_compilation(BITMAP* buffer, BITMAP* ath_collision,BITMAP*map_collision,t_jeu regl);
///_____________________________________________________________________________________________


///Attaque______________________________________________________________________________________
t_jeu attaque(BITMAP * buffer,BITMAP * Font[120],t_jeu partie);
void animationAttaque(BITMAP * buffer, t_jeu regl, int dx,int dy);
void animationPerteVie(BITMAP * buffer,BITMAP * Font[120],t_jeu regl, int dx, int dy, int degats);
void animationGuerison(BITMAP * buffer,BITMAP * Font[120],t_jeu regl, int dx, int dy, int degats);
void animationMort(BITMAP * buffer,t_jeu regl,int indice);
///_____________________________________________________________________________________________


///MenuFin______________________________________________________________________________________
int showScores(t_jeu regl, BITMAP* buffer, BITMAP* Font[120]);
///_____________________________________________________________________________________________


///timer________________________________________________________________________________________
t_jeu printTime(BITMAP * buffer,t_jeu regl,BITMAP * Font[120]);
///_____________________________________________________________________________________________

#endif // MABIBLIO_H_INCLUDED

