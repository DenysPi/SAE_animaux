#pragma once

#include "podium.h"
#include "joueur.h"


typedef struct {
	char* nom_commande;
}Commande;

typedef Vecteur Commandes;

Commande* creerCommande(const char* nom);


int initCommandes(Commandes* commandes, int capacite);
int ajouterCommande(Commandes* commandes, const char* nom);
Commande* obtenirCommande(const Commandes* commandes, int i);

int ajouterHaut(Podium* p, int index_animal);
int supprimerHaut(Podium* p, int* address_animal);
int supprimerBas(Podium* p, int* adress_animal);


int executerCommande(const char* nom, Podium* podium_b, Podium* podium_r);

int executerLigneCommandes(const char* commandes, Podium* podium_b, Podium* podium_r);