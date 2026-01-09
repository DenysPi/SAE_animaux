#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affichage.h"



typedef struct {
	Animaux* animaux;
	Commandes* commandes;
	Joueurs* joueurs;
	Podium* podium_b;
	Podium* podium_r;

	Podium* target_b;
	Podium* target_r;

	Vecteur* cartes;
}Game;


int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms);
int gameLoop(Game* game); 


void distribuerCarteAleatoire(Vecteur* cartes, int nb_animaux, Game* game);
//void freeGame(Game* game);