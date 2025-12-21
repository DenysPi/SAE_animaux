#include <string.h>

#include <assert.h> 
#include <stdlib.h> 


#include "config.h"


enum { BUFFER_SIZE = 10 };



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


char** splitLine(char* line) {
	
	char* tmp_ligne = strdup(line);
	char* element = strtok(tmp_ligne, " \t");
	int n = 0;

	while (element) {
		++n;
		
		element = strtok(NULL, " \t");
		
	}
	
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



int loadConfig(const char* fichier, char*** animaux_out, int* nb_animaux_out, char*** commandes_out, int* nb_commandes_out) {

	if (!fichier || !animaux_out || !nb_animaux_out || !commandes_out || !nb_commandes_out) return -1;

	FILE* f = fopen(fichier, "r");
	if (!f) { fprintf(stderr, "fichier non accessible: %s\n", fichier); return -1; }

	*animaux_out = NULL;
	*nb_animaux_out = 0;
	*commandes_out = NULL;
	*nb_commandes_out = 0;

	char* line = readFullLine(f);
	if (line) {
		*animaux_out = splitLine(line, nb_animaux_out);
		free(line);
	}

	line = readFullLine(f);
	if (line) {
		*commandes_out = splitLine(line, nb_commandes_out);
		free(line);
	}

	fclose(f);
	return 0;
}

