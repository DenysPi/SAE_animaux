#include "commandes.h"

Commande* creerCommande(const char* nom) {
	Commande* c = (Commande*)malloc(sizeof(Commande));
	
	c->nom_commande = (char*)malloc(strlen(nom) + 1);
	strcpy(c->nom_commande, nom);
	return c;
}


int initCommandes(Commandes* commandes, int capacite) {
	return initVecteur(commandes, capacite);
}
int ajouterCommande(Commandes* commandes, const char* nom) {
	Commande* c = creerCommande(nom);
	ajouter(commandes, c);
}
Commande* obtenirCommande(const Commandes* commandes, int i) {
	return obtenir(commandes, i);
}

int ajouterHaut(Podium* p, int index_animal) {
	int* it = (int*)malloc(sizeof(int));
	*it = index_animal;
	return ajouter(p, it);
}
int supprimerHaut(Podium* p, int* address_animal) {
	int index_last = p->nbElements - 1;
	if (index_last < 0) return 0;
	int* it = (int*)obtenir(p, index_last);

	*address_animal = *it;
	free(it);
	supprimer(p, index_last);
	return 1;
	
}
int supprimerBas(Podium* p, int* adress_animal) {
	int* it = (int*)obtenir(p, 0);
	*adress_animal = *it;
	free(it);
	supprimer(p, 0);
	return 1;

}

/*
	KI: Haut Bleu -> Haut Rouge
	LO: Haut rouge -> Haut Bleu
	SO: Haut rouge <-> Haut Bleu
	NI: Bas Bleu -> Haut Bleu
	MA: Bas Rouge -> Haut Rouge
*/
int executerCommande(const char* nom, Podium* podium_b, Podium* podium_r) {

	if (strcmp(nom, "KI") == 0) {
		int animal;
		if (!supprimerHaut(podium_b, &animal))
			return 0;
		if (!ajouterHaut(podium_r, animal))
			return 0;
		return 1;
	}
	else if (strcmp(nom, "LO") == 0) {
		int animal;
		if (!supprimerHaut(podium_r, &animal))
			return 0;
		if (!ajouterHaut(podium_b, animal))
			return 0;
		return 1;
	}
	else if (strcmp(nom, "SO") == 0) {
		int animal_r;
		int animal_b;
		if (!supprimerHaut(podium_r, &animal_r))
			return 0;
		if (!supprimerHaut(podium_b, &animal_b))
			return 0;
		if (!ajouterHaut(podium_b, animal_r))
			return 0;
		if (!ajouterHaut(podium_r, animal_b))
			return 0;
		return 1;
	}
	else if (strcmp(nom, "NI") == 0) {
		int animal;
		if (!supprimerBas(podium_b, &animal))
			return 0;
		if (!ajouterHaut(podium_b, animal))
			return 0;
		return 1;
	}
	else if (strcmp(nom, "MA") == 0) {
		int animal;
		if (!supprimerBas(podium_r, &animal))
			return 0;
		if (!ajouterHaut(podium_r, animal))
			return 0;
		return 1;
	}
	else if (strcmp(nom, "Q")) {
		return 0;
	}
	return 0;
}

int executerLigneCommandes(const char* commandes, Podium* podium_b, Podium* podium_r) {
	if (strlen(commandes) % 2 != 0) {
		return 0;
	}
	for (int i = 0; i < strlen(commandes); i += 2) {
		char commande[3];
		commande[0] = commandes[i];
		commande[1] = commandes[i + 1];
		commande[2] = '\0';

		if (!executerCommande(commande, podium_b, podium_r)) {
			return 0;
		}
	}
	return 1;
}