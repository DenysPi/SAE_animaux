#include "podium.h"

int initPodium(Podium* p, int capacite) {
	return initVecteur(p, capacite);
}

int ajouterPodiumAnimal(Podium* p, int index_animal){
	int* it = (int*)malloc(sizeof(int));
	*it = index_animal;
	return ajouter(p, it);
}

void supprimerPodiumAnimal(Podium* p, int index_animal) {
	supprimer(p, index_animal);

}

int presentAuPodium(Podium* p, int index_animal) {
	if (!p) return 0;
	for (int i = 0; i < p->nbElements; ++i) {
		int* it = (int*)obtenir(p, i);
		if (it && *it == index_animal) return 1;
	}
	return 0;
}

int comparer2Podiums(Podium* p_1, Podium* p_2) {
	if (p_1->nbElements != p_2->nbElements) {
		return 0;
	}
	for (int i = 0; i < p_1->nbElements; ++i) {
		int* it1 = (int*)obtenir(p_1, i);
		int* it2 = (int*)obtenir(p_2, i);
		if (*it1 != *it2) return 0;
	}
	return 1;
}

Podium* clonePodium(const Podium* src) {
	if (!src) return NULL;
	Podium* p = (Podium*)malloc(sizeof(Podium));
	
	initPodium(p, src->capacite > 0 ? src->capacite : 1);
		
	for (int i = 0; i < src->nbElements; ++i) {
		int* it = (int*)obtenir(src, i);
		if (it) {
			
			ajouterPodiumAnimal(p, *it);
		}
	}
	return p;
}

void freePodium(Podium* p) {
	for (int i = 0; i < p->nbElements; ++i) {
		free(p->elements[i]);
	}
	detruireVecteur(p);
}

void clearPodium(Podium* p) {
	if (!p) return;
	for (int i = 0; i < p->nbElements; ++i) {
		free(p->elements[i]);
		p->elements[i] = NULL;
	}
	p->nbElements = 0;
}


int maxTaillePodiums(const Podium* p_b, const Podium* p_r, const Podium* t_b, const Podium* t_r) {
	int max = 0;
	if (p_b && p_b->nbElements > max) max = p_b->nbElements;
	if (p_r && p_r->nbElements > max) max = p_r->nbElements;
	if (t_b && t_b->nbElements > max) max = t_b->nbElements;
	if (t_r && t_r->nbElements > max) max = t_r->nbElements;
	return max;
}

int remplacerContenuPodium(Podium* dest, const Podium* src) {
	
	freePodium(dest);

	
	for (int i = 0; i < src->nbElements; ++i) {
		int* it_src = (int*)obtenir(src, i);

		int* it = (int*)malloc(sizeof(int));
		
		*it = *it_src;
		ajouterPodiumAnimal(dest, it);
	}
	return 1;
}