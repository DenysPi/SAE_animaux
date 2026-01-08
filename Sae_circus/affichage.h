#pragma once


#include "config.h"



void CommandesPresentes(Commandes* commandes);
void ordreExistePas();
void ordreErreur();

void ordreIncorect(Joueur* j);
void joueurPeutPasJouer(char* j);
void afficherPodiums(Animaux* a, Podium* b, Podium* r, Podium* target_b, Podium* target_r);
void gagnerPoint(char* j, int situation);
void afficherResultats(Joueurs* joueurs);
void lancementErrorCommande();
void pasAssesDesJoueurs();
void joueurJouePas();