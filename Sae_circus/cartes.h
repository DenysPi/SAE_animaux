#pragma once

#include "vecteur.h"
#include "podium.h"




void genererToutesLesCartes(Animaux* animaux, Vecteur* cartes);
void push_split_for_perm(int* perm, int n, int split, Vecteur* cartes);
void push_all_splits(int* perm, int n, Vecteur* cartes);
void heap_generer(int k, int* A, int n, Vecteur* cartes);

int choisirRandomCarte(Vecteur* cartes);

void distrbuerAuxPodiums(int* arr, int n, Podium* podium_b, Podium* podium_r);


