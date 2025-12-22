#include <assert.h> 
#include <stdlib.h> 
#include "vecteur.h"

int initVecteur(Vecteur* v, int capacite) {
	assert(capacite > 0);
	v->capacite = capacite;
	v->nbElements = 0;
	v->elements = (void**)malloc(sizeof(void*) * capacite);
	return v->elements != NULL;
}

int taille(const Vecteur* v) {
	return v->nbElements;
}

int ajouter(Vecteur* v, void* it) {
	const int FACTEUR = 2;
	if (v->nbElements == v->capacite) {
		void* tab = (void**)realloc(v->elements, sizeof(void*) * v->capacite * FACTEUR);
		if (tab == NULL)
			return 0;
		v->capacite *= FACTEUR;
		v->elements = tab;
	}
	v->elements[v->nbElements++] = it;
	return 1;
}

void* obtenir(const Vecteur* v, int i) {
	assert(i >= 0 && i < v->nbElements);
	return v->elements[i];
}

void modifier(Vecteur* v, int i, void* it) {
	assert(i >= 0 && i < v->nbElements);
	v->elements[i] = it;
}

void supprimer(Vecteur* v, int i) {
	assert(i >= 0 && i < v->nbElements);
	for (++i; i < v->nbElements; ++i)
		v->elements[i - 1] = v->elements[i];
	--v->nbElements;
}

int retailler(Vecteur* v, int taille) {
	assert(taille > 0);
	void** tab = (void**)realloc(v->elements, sizeof(void*) * taille);
	if (tab == NULL)
		return 0;
	v->elements = tab;
	v->capacite = taille;
	if (v->nbElements > taille)
		v->nbElements = taille;
	return 1;
}

void detruireVecteur(Vecteur* v) {
	free(v->elements);
}

