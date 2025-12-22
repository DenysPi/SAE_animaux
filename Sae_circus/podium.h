#pragma once

#include "animal.h"
#include "vecteur.h"

typedef enum ItemV ItemP;
typedef struct Vecteur Podium;

int initPodium(Podium* p, int capacite);

int ajouterPodiumAnimal(Podium* p, ItemP index_animal);

int supprimerPodiumAnimal(Podium* p, ItemP index_animal);

int presentAuPodium(Podium* p, ItemP index_animal);
 
void freePodium(Podium* p);