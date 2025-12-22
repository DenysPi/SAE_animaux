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