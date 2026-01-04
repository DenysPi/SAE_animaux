#include "game.h"
#include "affichage.h"
int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms) {
	srand((unsigned)time(NULL));
	game->animaux = NULL;
	game->commandes = NULL;
	game->joueurs = NULL;
	game->podium_b = NULL;
	game->podium_r = NULL;
	game->target_b = NULL;
	game->target_r = NULL;
	game->cartes = NULL;

	game->animaux = (Animaux*)malloc(sizeof(Animaux));
	game->commandes = (Commandes*)malloc(sizeof(Commandes));
	game->joueurs = (Joueurs*)malloc(sizeof(Joueurs));
	game->podium_b = (Podium*)malloc(sizeof(Podium));
	game->podium_r = (Podium*)malloc(sizeof(Podium));
	game->target_b = (Podium*)malloc(sizeof(Podium));
	game->target_r = (Podium*)malloc(sizeof(Podium));

	if (loadConfig(fichier, game->animaux, game->commandes) != 0) {
		printf("Erreur chargement config\n");
		return -1;
	}

	if (loadJoueurs(game->joueurs, nb_joueurs, noms) != 0) {
		printf("Erreur chargement joueurs");
		return -1;
	}


	int capacite = game->animaux->nbElements > 0 ? game->animaux->nbElements : 1;
	if (!initPodium(game->podium_b, capacite) || !initPodium(game->podium_r, capacite)
		|| !initPodium(game->target_b, capacite) || !initPodium(game->target_r, capacite)) {
		printf("Erreur initialisation podiums\n");
		return -1;
	}


	/* ================== initialisation et test des cartes ================== */
	game->cartes = (Vecteur*)malloc(sizeof(Vecteur));
	if (!game->cartes || !initVecteur(game->cartes, 1)) {
		printf("Erreur initialisation cartes\n");
		/* continuer sans cartes éventuellement */
		if (game->cartes) { free(game->cartes); game->cartes = NULL; }
	}
	genererToutesLesCartes(game->animaux, game->cartes);
	
	int idx = choisirRandomCarte(game->cartes);
	int* arr = obtenir(game->cartes, idx);

	distrbuerAuxPodiums(arr, game->animaux->nbElements, game->podium_b, game->podium_r);

	int idxs = choisirRandomCarte(game->cartes);
	int* arrs = obtenir(game->cartes, idxs);

	distrbuerAuxPodiums(arrs, game->animaux->nbElements, game->target_b, game->target_r);


	

}

int gameLoop(Game* game)
{
	char* ligne = NULL;
	char* commande = NULL;
	char* nom_j = NULL;

	int nb_jouees = 0;
	
	CommandesPresentes(game->commandes);
	while (1) {
		afficherPodiums(game->animaux, game->podium_b, game->podium_r, game->target_b, game->target_r);
		ligne = readFullLine(stdin);
		if (!ligne) {
			break;
		}
		

		
		nom_j = strtok(ligne, " \t");
		commande = strtok(NULL, " \t");

		
		Podium* podium_b = clonePodium(game->podium_b);
		Podium* podium_r = clonePodium(game->podium_r);
		if (peutJouer(game->joueurs, nom_j) == 1) {
			if (!executerLigneCommandes(commande, podium_b, podium_r)) {
				afficherResultats(game->joueurs);
				break;
			}

			
			if (comparer2Podiums(podium_b, game->target_b) == 1 && comparer2Podiums(podium_r, game->target_r) == 1) {
				ajouterPointJoueur(game->joueurs, nom_j);
				gagnerPoint(nom_j, 0);

				int idx = choisirRandomCarte(game->cartes);
				int* arr = obtenir(game->cartes, idx);

				distrbuerAuxPodiums(arr, game->animaux->nbElements, game->podium_b, game->podium_r);

				int idxs = choisirRandomCarte(game->cartes);
				int* arrs = obtenir(game->cartes, idxs);

				distrbuerAuxPodiums(arrs, game->animaux->nbElements, game->target_b, game->target_r);
			}

			else {
				ordreIncorect(nom_j);
			}

			Joueur* j = obtenirJoueurParNom(game->joueurs, nom_j);
			j->tour = 0;
			++nb_jouees;
		
		}
		else {
			printf("%s ne peut pas jouer\n", nom_j);
		}
		printf("%d ", nb_jouees);
		printf("%d", game->joueurs->nbElements - 1);
		if (nb_jouees == game->joueurs->nbElements-1) {
			Joueur* j = lastPerson(game->joueurs);
			ajouterPointJoueur(game->joueurs, j->nom);
			gagnerPoint(j->nom, 1);
		}
		
	}

		free(ligne);
	

	return 0;
}