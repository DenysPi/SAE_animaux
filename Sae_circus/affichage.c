#include "affichage.h";


void CommandesPresentes(Commandes* commandes) {
	for (int i = 0; i < commandes->nbElements; ++i) {
		Commande* commande = commandes->elements[i];
		if (strcmp(commande->nom_commande, "KI") == 0){
			printf("KI (B->R) ");
		}
		else if (strcmp(commande->nom_commande, "LO") == 0) {
			printf("LO (B<-R) ");
		}
		else if (strcmp(commande->nom_commande, "SO") == 0) {
			printf("SO (B<->R) ");
		}
		else if (strcmp(commande->nom_commande, "NI") == 0) {
			printf("NI (B ^) ");
		}
		else if (strcmp(commande->nom_commande, "MA") == 0) {
			printf("MA (R ^) ");
		}

		if (i != commandes->nbElements - 1) {
			printf("| ");
		}
	}
	printf("\n\n");
}
void ordreExistePas() {
	printf("Ordre n'existe pas\n\n");
}

void ordreErreur() {
	printf("Impossible d'executer\n\n");
}

void ordreIncorect(Joueur* j) {
	printf("La sequence ne conduit pas a la situation attendue -- %s ne peut plus jouer durant ce tour\n\n", j->nom);
}

void joueurPeutPasJouer(Joueur* j) {
	printf("%s ne peut pas jouer\n", j->nom);
}
void afficherPodiums(Animaux* a, Podium* b, Podium* r, Podium* target_b, Podium* target_r) {
	int max = maxTaillePodiums(b, r, target_b, target_r);
	for (int niveau = max - 1; niveau >= 0; --niveau) {
		
		if (niveau < b->nbElements) {
			int* p = obtenir(b, niveau);
			Animal* an = obtenirAnimal(a, *p);
			printf("%-12s", (an && an->nom_animal) ? an->nom_animal : "");
		}
		else {
			printf("%-12s", "");
		}

		printf("  ");

		
		if (r && niveau < r->nbElements) {
			int* p = (int*)obtenir(r, niveau);
			Animal* an = (p ? obtenirAnimal(a, *p) : NULL);
			printf("%-12s", (an && an->nom_animal) ? an->nom_animal : "");
		}
		else {
			printf("%-12s", "");
		}

		printf(" || ");

		/* Target Bleu */
		if (target_b && niveau < target_b->nbElements) {
			int* p = (int*)obtenir(target_b, niveau);
			Animal* an = (p ? obtenirAnimal(a, *p) : NULL);
			printf("%-12s", (an && an->nom_animal) ? an->nom_animal : "");
		}
		else {
			printf("%-12s", "");
		}

		printf("   ");

		/* Target Rouge */
		if (target_r && niveau < target_r->nbElements) {
			int* p = (int*)obtenir(target_r, niveau);
			Animal* an = (p ? obtenirAnimal(a, *p) : NULL);
			printf("%-12s", (an && an->nom_animal) ? an->nom_animal : "");
		}
		else {
			printf("%-12s", "");
		}

		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
	printf("%-12s  %-12s   %-12s  %-12s\n", "Bleu", "Rouge", "Bleu", "Rouge");
}

void gagnerPoint(char* j, int situation) {
	if (situation == 0) {
		printf("%s gagne un point\n", j);
	}
	else {
		printf("%s gagne un point car lui seul peut encore jouer durant ce tour\n", j);
	}
}


void lancementErrorCommande() {
	printf("A lancement du code, on n'a pas pu indentifier la commande\n");
}

void pasAssesDesJoueurs() {
	printf("!!Verifier le nombre des joueurs!!\n");
}

void joueurJouePas() {
	printf("Il n'existe pas de joueur avec ce nom ):\n");
}