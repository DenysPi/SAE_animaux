#pragma once
#pragma warning(push)
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "animal.h"


typedef Vecteur Podium;

int initPodium(Podium* p, int capacite);

int ajouterPodiumAnimal(Podium* p, int index_animal);

void supprimerPodiumAnimal(Podium* p, int index_animal);

int presentAuPodium(Podium* p, int index_animal);
int comparer2Podiums(Podium* p_1, Podium* p_2);
Podium* clonePodium(const Podium* src);
void freePodium(Podium* p);

int maxTaillePodiums(const Podium* p_b, const Podium* p_r, const Podium* t_b, const Podium* t_r);

int remplacerContenuPodium(Podium* dest, const Podium* src);

void clearPodium(Podium* p);