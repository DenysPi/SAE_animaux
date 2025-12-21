#pragma once
#pragma warning(push)
#pragma warning(disable:4996)
#include <stdio.h>



int loadConfig(const char* fichier, char*** animaux_out, int* nb_animaux_out, char*** commandes_out, int* nb_commandes_out);
char** splitLine(char* line, int* nb);
char* readFullLine(FILE* f);

