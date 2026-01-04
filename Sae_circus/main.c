#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"


int main(int argc, char** argv) {
	
	if (argc < 3) {
		printf("Il faut au moins 2 jouers");
	}
	
	int nb_joueurs = argc - 1;
	char** noms = &argv[1];
	Game game;
	initGameConfig(&game, "crazy.cfg", nb_joueurs, noms);
	
	gameLoop(&game);
	

	/*for (int i = 0; i < game.animaux->nb_animaux; ++i) {
		printf("%s ", game.animaux->nom_animaux[i]);
	}
	printf("\n");
	for (int i = 0; i < game.commandes->nb_commandes; ++i) {
			printf("%s ", game.commandes->noms_commandes[i]);
		}*/
}