#include "game.h"
#include "affichage.h"




void distribuerCarteAleatoire(Vecteur* cartes, int nb_animaux, Game* game) {
	if (!cartes || cartes->nbElements == 0) return;
	int idx = choisirRandomCarte(cartes);
	int* arr = (int*)obtenir(cartes, idx); 
	distrbuerAuxPodiums(arr, nb_animaux, game->podium_b, game->podium_r);

	int idxs = choisirRandomCarte(game->cartes);
	int* arrs = obtenir(game->cartes, idxs);

	distrbuerAuxPodiums(arrs, game->animaux->nbElements, game->target_b, game->target_r);

}

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
	int resultat = loadConfig(fichier, game->animaux, game->commandes);
	
	if (resultat != 0) {
		if (resultat == 1) {
			lancementErrorCommande();
			return -1;
		}
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


	game->cartes = (Vecteur*)malloc(sizeof(Vecteur));
	initVecteur(game->cartes, 1);
	genererToutesLesCartes(game->animaux, game->cartes);
	
	distribuerCarteAleatoire(game->cartes, game->animaux->nbElements, game);
	
	
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
		
		if (!joueurExiste(game->joueurs, nom_j)) {
			joueurJouePas();
		}
		
		
		else if (peutJouer(game->joueurs, nom_j) == 1) {
			
			int reponse = executerLigneCommandes(game->commandes,commande, podium_b, podium_r);
			
			if (reponse == 0) {
				ordreExistePas();
				
			}
			else if(reponse == 2 ) {
				ordreErreur();
			}
			else {
				Joueur* j = obtenirJoueurParNom(game->joueurs, nom_j);
				j->tour = 0;
				++nb_jouees;

				if (comparer2Podiums(podium_b, game->target_b) == 1 && comparer2Podiums(podium_r, game->target_r) == 1) {
					ajouterPointJoueur(game->joueurs, nom_j);
					gagnerPoint(nom_j, 0);
					nb_jouees = 0;

					distribuerCarteAleatoire(game->cartes, game->animaux->nbElements, game);

					printf("%d\n", j->points);
				}

				else {
					ordreIncorect(nom_j);
				}

				if (nb_jouees == game->joueurs->nbElements - 1) {
					nb_jouees = 0;
					distribuerCarteAleatoire(game->cartes, game->animaux->nbElements, game);
					Joueur* j = lastPerson(game->joueurs);
					ajouterPointJoueur(game->joueurs, j->nom);
					gagnerPoint(j->nom, 1);
					remetreTours(game->joueurs);
					
				}
			}

			

			
		
		}
		else {
			printf("%s ne peut pas jouer\n", nom_j);
		}
		
		
		
	}

	afficherResultats(game->joueurs);
	

	return 0;
}