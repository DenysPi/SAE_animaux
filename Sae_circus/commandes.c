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

static int isAllowedCommande(const char* nom) {
	if (!nom) return 0;
	static const char* allowed[] = { "KI", "LO", "SO", "NI", "MA", NULL };
	for (int i = 0; allowed[i] != NULL; ++i) {
		if (strcmp(nom, allowed[i]) == 0) return 1;
	}
	return 0;
}

int ajouterCommande(Commandes* commandes, const char* nom) {
	if (!isAllowedCommande(nom)) return 0;
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
	if (p->nbElements == 0) {
		return 0;
	}
	int index_last = p->nbElements - 1;
	if (index_last < 0) return 0;
	int* it = (int*)obtenir(p, index_last);

	*address_animal = *it;
	free(it);
	supprimer(p, index_last);
	return 1;
	
}
int supprimerBas(Podium* p, int* adress_animal) {
	if (p->nbElements == 0) {
		return 0;
	}
	int* it = (int*)obtenir(p, 0);
	*adress_animal = *it;
	free(it);
	supprimer(p, 0);
	return 1;

}

int verifierCommande(Commandes* commandes, char* commande) {
	for (int i = 0; i < commandes->nbElements; ++i) {
		Commande* c = obtenirCommande(commandes, i);
		if (strcmp(c->nom_commande, commande)==0) {
			return 1;
		}
	}
	return 0;
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

int executerLigneCommandes(Commandes* commandes, const char* com, Podium* podium_b, Podium* podium_r) {
	if (strlen(com) % 2 != 0) {
		
		return 2;
	}
	for (int i = 0; i < strlen(com); i += 2) {
		char commande[3];
		commande[0] = com[i];
		commande[1] = com[i + 1];
		commande[2] = '\0';
		
		if (verifierCommande(commandes, commande)) {
			
			if (executerCommande(commande, podium_b, podium_r) == 0) {
				
				return 2;
			}
		}
		else {
			return 0;
		}
		
		
	}
	return 1;
}