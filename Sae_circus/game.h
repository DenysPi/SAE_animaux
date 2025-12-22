#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandes.h"
#include "config.h"


typedef struct {
	Animaux* animaux;
	Commandes* commandes;
	Joueurs* joueurs;
	Podium* podium_b;
	Podium* podium_r;
}Game;


int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms);

void freeGame(Game* game);