#pragma once
#pragma warning(push)
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteur.h"

typedef struct {
	char* nom_animal;
}Animal;

typedef Vecteur Animaux;


Animal* creerAnimal(const char* nom);;

int initAnimaux(Animaux* animaux, int capacite);
int ajouterAnimal(Animaux* animaux, const char* nom);
Animal* obtenirAnimal(const Animaux* animaux, int i);

int* shuffleAnimaux(int n_animaux);
