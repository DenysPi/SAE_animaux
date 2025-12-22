#pragma once
#pragma warning(push)
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vecteur.h"

typedef struct {
	char* nom;
	int tour;
}Joueur;

typedef Vecteur Joueurs;

Joueur* creerJoueur(const char* nom);


int initJoueurs(Joueurs* joueurs, int capacite);
int ajouterJoueur(Joueurs* joueurs, const char* nom);
Joueur* obtenirJoueur(const Joueurs* joueurs, int i);