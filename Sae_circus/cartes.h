/**
 * @file cartes.h
 * @brief Génération et manipulation des cartes de répartition des animaux sur les podiums.
 *
 * Ce module produit l’ensemble des cartes possibles à partir d’une permutation
 * des animaux et d’un point de séparation (split) qui partage la permutation
 * entre le podium Bleu (préfixe) et le podium Rouge (suffixe).
 *
 * Une carte est représentée par un tableau d’entiers :
 * - arr[0]  : la position de séparation split (0 ≤ split ≤ n),
 * - arr[1..n] : la permutation des indices d’animaux.
 */

#pragma once

#include "commandes.h"

/**
 * @brief Génère toutes les cartes possibles pour les animaux fournis.
 *
 * Toutes les permutations des indices `[0..n-1]` sont générées, et pour chacune,
 * toutes les valeurs possibles de `split` (de 0 à n) sont utilisées pour créer
 * une carte ajoutée au vecteur `cartes`.
 *
 * @param[in]  animaux Référentiel des animaux.
 * @param[out] cartes  Vecteur recevant des pointeurs `int*` vers les cartes générées.
 * @pre `animaux` et `cartes` doivent être initialisés.
 */
void genererToutesLesCartes(Animaux* animaux, Vecteur* cartes);

/**
 * @brief Crée une carte à partir d’une permutation et d’un split, puis l’ajoute à `cartes`.
 *
 * La carte créée vérifie : `arr[0] = split` et `arr[1..n] = perm`.
 *
 * @param[in] perm   Permutation des indices d’animaux.
 * @param[in] n      Taille de la permutation.
 * @param[in] split  Position de séparation (0 ≤ split ≤ n).
 * @param[out] cartes Vecteur recevant la carte créée.
 * @pre `perm` pointe vers au moins `n` éléments et `0 ≤ split ≤ n`.
 */
void push_split_for_perm(int* perm, int n, int split, Vecteur* cartes);

/**
 * @brief Ajoute à `cartes` toutes les cartes correspondant aux splits d’une permutation.
 *
 * Pour une permutation donnée, les valeurs de `split` de 0 à `n` sont utilisées.
 *
 * @param[in] perm   Permutation des indices d’animaux.
 * @param[in] n      Taille de la permutation.
 * @param[out] cartes Vecteur recevant les cartes.
 * @pre `perm` pointe vers au moins `n` éléments.
 */
void push_all_splits(int* perm, int n, Vecteur* cartes);

/**
 * @brief Génère toutes les permutations par l’algorithme de Heap et crée les cartes associées.
 *
 * @param[in] k  Paramètre de récursion de l’algorithme.
 * @param[in] A  Tableau contenant la permutation courante.
 * @param[in] n  Nombre total d’animaux.
 * @param[out] cartes Vecteur recevant les cartes.
 * @pre `A` pointe vers au moins `n` éléments.
 */
void heap_generer(int k, int* A, int n, Vecteur* cartes);

/**
 * @brief Sélectionne aléatoirement une carte parmi celles stockées dans `cartes`.
 *
 * @param[in] cartes Vecteur contenant des cartes.
 * @return Un indice valide dans l’intervalle `[0, cartes->nbElements - 1]`.
 * @pre `cartes->nbElements > 0`.
 */
int choisirRandomCarte(Vecteur* cartes);

/**
 * @brief Distribue les animaux d’une carte vers les podiums Bleu et Rouge.
 *
 * Le champ `arr[0]` indique la valeur `split` :
 * les indices `arr[1]` à `arr[split]` vont vers le podium Bleu,
 * les indices `arr[split+1]` à `arr[n]` vont vers le podium Rouge.
 *
 * @param[in] arr Carte contenant le split et la permutation.
 * @param[in] n   Nombre total d’animaux.
 * @param[out] podium_b Podium Bleu.
 * @param[out] podium_r Podium Rouge.
 * @pre `arr` pointe vers au moins `n+1` éléments et `0 ≤ arr[0] ≤ n`.
 */
void distrbuerAuxPodiums(int* arr, int n, Podium* podium_b, Podium* podium_r);

