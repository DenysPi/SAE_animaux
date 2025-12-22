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