#include "game.h"


int main() {
	Config* config = loadConfig("crazy.cfg");
	printf("%d ", config->nb_animaux);
	printf("%d ", config->nb_commandes);

	printf("\n");
	for (int i = 0; i < config->nb_animaux; ++i) {
		printf("%s ", config->noms_animaux[i]);
	}
	printf("\n");
	for (int i = 0; i < config->nb_commandes; ++i) {
		printf("%s ", config->noms_commandes[i]);
	}

	
}