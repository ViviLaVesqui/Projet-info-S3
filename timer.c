#include "maBiblio.h"

t_jeu printTime(BITMAP * buffer,t_jeu regl,BITMAP * Font[120]){
    regl.chrono.intervalle = ((double)regl.chrono.timer-regl.chrono.prevtime)/CLOCKS_PER_SEC;
    regl.chrono.chrono = (int)regl.chrono.  intervalle;
    regl.chrono.tpsRestant = 30-regl.chrono.chrono;
    if(regl.chrono.tpsRestant >= 0){
        sprintf(regl.chrono.time,"%d s", regl.chrono.tpsRestant);
    }
    else{
        sprintf(regl.chrono.time,"0");
    }
    printTEXT(buffer,Font,regl.chrono.time,420,650,1);
    return regl;
}
