cmake_minimum_required(VERSION 3.23)
project(ECE_Arena C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ECE_Arena
        AffichageJoueur.c
        attaque.c
        Deplacement.c
        Ecriture.c
        grilleEtATH.c
        Init.c
        maBiblio.h
        main.c
        MenuDebut.c
        MenuFin.c
        MenuSelection.c
        parametre.c
        parametres.c
        pouvoir.c
        Range.c
        timer.c)
