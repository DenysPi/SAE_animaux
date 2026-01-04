
#include "cartes.h"


static void swap_int(int* a, int* b) {
	int t = *a; *a = *b; *b = t;
}
void genererToutesLesCartes(Animaux* animaux, Vecteur* cartes) {
	int n = animaux->nbElements;
		
	int* perm = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		perm[i] = i;
	}
	heap_generer(n, perm, n, cartes);
}
void push_all_splits(int* perm, int n, Vecteur* cartes) {
	for (int i = 0; i <= n; ++i) {
		push_split_for_perm(perm, n, i, cartes);
	}
	
}
void push_split_for_perm(int* perm, int n, int split, Vecteur* cartes) {
	int* arr = (int*)malloc(sizeof(int) * n + 1);
	arr[0] = split;
	for (int i = 0; i < n; ++i) {
		arr[i + 1] = perm[i];
	}
	ajouter(cartes, arr);

}
void heap_generer(int k, int* A, int n, Vecteur* cartes) {
	if (k == 1) {
		return push_all_splits(A, n, cartes);
	}
	else {
		heap_generer(k - 1, A, n, cartes);
		for (int i = 0; i <= k - 2; ++i) {
			if (k % 2 == 0) {
				swap_int(&A[i], &A[k - 1]);
			}
				
			else {
				swap_int(&A[0], &A[k - 1]);
			}
			heap_generer(k - 1, A, n, cartes);
		}
	}
}


int choisirRandomCarte(Vecteur* cartes) {
	return rand() % cartes->nbElements;
}

void distrbuerAuxPodiums(int* arr,int n,  Podium* podium_b, Podium* podium_r) {
	int split = arr[0];
	

	clearPodium(podium_b);
	clearPodium(podium_r);
		
	for (int i = 0; i < split; ++i) {
		int idx = arr[i + 1];
		ajouterPodiumAnimal(podium_b, idx);
		
	}
		
	for (int i = split; i < n; ++i) {
		int idx = arr[i + 1];
		ajouterPodiumAnimal(podium_r, idx);
	}
	
}