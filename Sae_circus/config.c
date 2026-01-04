#include <string.h>

#include <assert.h> 
#include <stdlib.h> 


#include "config.h"


enum { BUFFER_SIZE = 64 };



char* readFullLine(FILE* f) {
	char buffer[BUFFER_SIZE];
	char* line = calloc(1, 1); 
	if (!line) return NULL;

	while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
		size_t taille = strlen(buffer);
		
		if (taille > 0 && buffer[taille - 1] == '\n') {

			buffer[taille - 1] = '\0';
			line = (char*)realloc(line, strlen(line) + taille);

			strcat(line, buffer);
			break;
		}
		else {

			line = (char*)realloc(line, strlen(line) + taille + 1);
			strcat(line, buffer);
		}
	}

	if (strlen(line) == 0) {
		free(line);
		return NULL;
	}
	return line;
}


char** splitLineAndCount(char* line, int* count) {
	
	char* tmp_ligne = strdup(line);
	char* element = strtok(tmp_ligne, " \t");
	int n = 0;

	while (element) {
		++n;
		
		element = strtok(NULL, " \t");
		
	}
	free(tmp_ligne);
	
	*count = n;
	char** noms = (char**)malloc(n * sizeof(char*));
	
	tmp_ligne = strdup(line);
	element = strtok(tmp_ligne, " \t");
	
	for (int i = 0; i < n; ++i) {
		
		noms[i] = (char*)malloc(strlen(element) + 1);
		
		strcpy(noms[i], element);
		
		
		element = strtok(NULL, " \t");
		
	}
	
	
	free(tmp_ligne);
	return noms;
}



int loadConfig(const char* fichier, Animaux* a, Commandes* c){
	if (!fichier || !a || !c) return -1;

	FILE* f = fopen(fichier, "r");
	


	char* line = readFullLine(f);
	if (line) {
		int n = 0;
		char** noms = splitLineAndCount(line, &n);
		
		initAnimaux(a, n);
		for (int i = 0; i < n; ++i) {
			ajouterAnimal(a, noms[i]);
		}
		
		free(line);
	}

	// +++++++++++++++++++++++++++++++++++++++++

	line = readFullLine(f);
	if (line) {
		int n = 0;
		char** noms = splitLineAndCount(line, &n);
		
		initCommandes(c, n);
		for (int i = 0; i < n; ++i) {
			ajouterCommande(c, noms[i]);
		}
		free(line);

	}

	//+++++++++++++++++++++++++++++++++++


	fclose(f);
	return 0;
}


int loadJoueurs(Joueurs* joueurs, int nb_joueurs, char** noms) {
	
	initJoueurs(joueurs, nb_joueurs);
	for (int i = 0; i < nb_joueurs; ++i) {
		ajouterJoueur(joueurs, noms[i]);
	}
	return 0;
}

Podium* max4(Podium* p_b, Podium* p_r, Podium* t_b, Podium* t_r) {
	Podium* max = p_b->nbElements;
	if (p_r->nbElements > max) {
		max = p_r;
	}
	if (t_b->nbElements > max) {
		max = t_b;
	}
	if (t_r->nbElements > max) {
		max = t_r;
	}
	return max;

}