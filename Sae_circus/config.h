#pragma once
#pragma warning(push)
#pragma warning(disable:4996)


#include <stdio.h>

#include "animal.h"
#include "commandes.h"
#include "joueur.h"

int loadJoueurs(Joueurs* joueurs, int nb_joueurs, char** noms);
int loadConfig(const char* fichier, Animaux* a, Commandes* c);
char** splitLineAndCount(char* line, int* count);
char* readFullLine(FILE* f);