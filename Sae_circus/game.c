#include "game.h"

int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms) {

	game->animaux = NULL;
	game->commandes = NULL;
	game->joueurs = NULL;


	game->animaux = (Animaux*)malloc(sizeof(Animaux));
	game->commandes = (Commandes*)malloc(sizeof(Commandes));
	game->joueurs = (Joueurs*)malloc(sizeof(Joueurs));
	

	if (loadConfig(fichier,game->animaux, game->commandes) != 0) {
		printf("Erreur chargement config\n");
		return -1;
	}

	if (loadJoueurs(game->joueurs, nb_joueurs, noms) != 0) {
		printf("Erreur chargement joueurs");
		return -1;
	}
	for (int i = 0; i < game->animaux->nbElements; ++i) {
		Animal* a = obtenirAnimal((Animaux*)game->animaux, i);
		if (a && a->nom_animal)
			printf("DEBUG: Animal [%d] = '%s'\n", i, a->nom_animal);
		else
			printf("DEBUG: Animal [%d] = (NULL)\n", i);
	}

	for (int i = 0; i < game->commandes->nbElements; ++i) {
		Commande* c = obtenirCommande((Commandes*)game->commandes, i);
		if (c && c->nom_commande)
			printf("DEBUG: Commande [%d] = '%s'\n", i, c->nom_commande);
		else
			printf("DEBUG: Commande [%d] = (NULL)\n", i);
	}

	for (int i = 0; i < game->joueurs->nbElements; ++i) {
		Joueur* j = obtenirJoueur((Joueurs*)game->joueurs, i);
		if (j && j->nom) {
			printf("DEBUG: Commande [%d] = '%s'\n", i, j->nom);
			printf("DEBUG: Commande [%d] = '%d'\n", i, j->tour);
		}
		else
			printf("DEBUG: Commande [%d] = (NULL)\n", i);
	}

	
	
	
	
	

}