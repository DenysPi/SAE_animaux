#include "game.h"


int main(int argc, char** argv) {
	
	if (argc < 3) {
		pasAssesDesJoueurs();
		return -1;
	}
	
	int nb_joueurs = argc - 1;
	char** noms = &argv[1];
	Game game;
	
	
	if (initGameConfig(&game, "crazy.cfg", nb_joueurs, noms) == -1) {
		printf("Changez des parametres du jeu\n");
		return -1;
	}
	
	gameLoop(&game);
	
}