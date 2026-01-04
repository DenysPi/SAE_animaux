#include <string.h>

#include "joueur.h"


Joueur* creerJoueur(const char* nom) {
	Joueur* j = (Joueur*)malloc(sizeof(Joueur));

	j->tour = 1;
	j->nom = (char*)malloc(strlen(nom) + 1);
	strcpy(j->nom, nom);
	return j;
}

int initJoueurs(Joueurs* joueurs, int capacite) {
	return initVecteur(joueurs, capacite);
}
int ajouterJoueur(Joueurs* joueurs, const char* nom) {
	Joueur* j = creerJoueur(nom);
	ajouter(joueurs, j);
}
Joueur* obtenirJoueur(const Joueurs* joueurs, int i) {
	return obtenir(joueurs, i);
}


Joueur* obtenirJoueurParNom(const Joueurs* joueurs, const char* nom) {
	for (int i = 0; i < joueurs->nbElements; ++i) {
		Joueur* j = obtenirJoueur(joueurs, i);
		if (strcmp(j->nom, nom) == 0) {
			return j;
		}
	}
	return NULL;
}
int peutJouer(const Joueurs* joueurs, char* nom) {
	Joueur* j = obtenirJoueurParNom(joueurs, nom);
	if (j == NULL) {
		return 0;
	}
	return j->tour;
}

int joueurExiste(const Joueurs* joueurs, char* nom) {
	return (obtenirJoueurParNom(joueurs, nom) != NULL);
}

void ajouterPointJoueur(Joueurs* joueurs,char* nom_j) {
	Joueur* j = obtenirJoueurParNom(joueurs, nom_j);
	++j->points;
}

Joueur* lastPerson(Joueurs* joueurs){
	for (int i = 0; i < joueurs->nbElements; ++i) {
		Joueur* j = obtenirJoueur(joueurs, i);
		if (j->tour == 1) {
			return j;
		}
	}
	return NULL;
}

void afficherResultats(Joueurs* joueurs) {
	for (int i = 0; i < joueurs->nbElements; ++i) {
		Joueur* j = obtenirJoueur(joueurs, i);
		printf("%s %d\n", j->nom, j->points);
	}
	printf("\n\n");
}