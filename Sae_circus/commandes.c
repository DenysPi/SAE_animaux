#include "commandes.h"

Commande* creerCommande(const char* nom) {
	Commande* c = (Commande*)malloc(sizeof(Commande));
	
	c->nom_commande = (char*)malloc(strlen(nom) + 1);
	strcpy(c->nom_commande, nom);
	return c;
}


int initCommandes(Commandes* commandes, int capacite) {
	return initVecteur(commandes, capacite);
}
int ajouterCommande(Commandes* commandes, const char* nom) {
	Commande* c = creerCommande(nom);
	ajouter(commandes, c);
}
Commande* obtenirCommande(const Commandes* commandes, int i) {
	return obtenir(commandes, i);
}