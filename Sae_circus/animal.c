#include <string.h>

#include "animal.h"


Animal* creerAnimal(const char* nom) {
	
	Animal* a = (Animal*)malloc(sizeof(Animal));
	

	a->nom_animal = (char*)malloc(strlen(nom) + 1);
	if (!a->nom_animal) { free(a); return NULL; }
	strcpy(a->nom_animal, nom);
	return a;
}
int initAnimaux(Animaux* animaux, int capacite) {
	return initVecteur(animaux, capacite);
}

int ajouterAnimal(Animaux* animaux, const char* nom) {
	Animal* a = creerAnimal(nom);
	ajouter(animaux, a);
}

Animal* obtenirAnimal(const Animaux* animaux, int i) {
	return obtenir(animaux, i);
}