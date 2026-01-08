
/**
 * @file cartes.h
 * @brief Génération et manipulation des cartes de répartition des animaux sur les podiums.
 *
 * Ce module produit l’ensemble des cartes possibles à partir d’une permutation
 * des animaux et d’un point de séparation (split) qui partage la permutation
 * entre le podium Bleu (prefixe) et le podium Rouge (suffixe).
 *
 * @par Format d’une carte
 * Une carte est représentée par un tableau d’entiers alloué dynamiquement :
 * - `arr[0]` : la position de séparation `split` (0 ≤ split ≤ n),
 * - `arr[1..n]` : la permutation des indices d’animaux (taille n).
 *
 * @note Les tableaux `arr` ajoutés dans le vecteur `cartes` doivent être libérés
 *       par l’appelant lorsque la collection n’est plus nécessaire (cf. gestion mémoire).
 */

#pragma once

#include "vecteur.h"
#include "podium.h"
// Recommandé pour la définition du type Animaux (alias de Vecteur dans ton projet).
// #include "animal.h"

/**
 * @brief Génère toutes les cartes possibles pour les animaux fournis.
 *
 * Construit toutes les permutations d’indices `[0..n-1]` puis, pour chaque permutation,
 * pousse toutes les cartes associées à tous les `split` possibles (de 0 à n).
 *
 * @param[in]  animaux Référentiel des animaux (sa taille logique `nbElements` est utilisée).
 * @param[out] cartes  Vecteur recevant des pointeurs `int*` vers les cartes générées.
 * @pre `animaux` doit être initialisé ; `cartes` doit être initialisé.
 * @post Pour chaque permutation et chaque `split`, un tableau `int*` est alloué et ajouté à `cartes`.
 * @note La génération de permutations utilise l’algorithme de **Heap** (référencé via `heap_generer`).
 * @sa heap_generer(), push_all_splits(), push_split_for_perm()
 */
void genererToutesLesCartes(Animaux* animaux, Vecteur* cartes);

/**
 * @brief Construit et pousse dans `cartes` une carte pour une permutation donnée et un split.
 *
 * @param[in] perm  Permutation des indices d’animaux (taille n).
 * @param[in] n     Taille de la permutation (nombre d’animaux).
 * @param[in] split Position de séparation (0 ≤ split ≤ n).
 * @param[out] cartes Vecteur recevant un `int*` nouvellement alloué :
 *                    `arr[0] = split`, `arr[1..n] = perm`.
 * @pre `perm` doit pointer vers un tableau d’au moins `n` éléments ; `0 ≤ split ≤ n`.
 * @post Alloue `arr` (taille `n + 1`) et l’ajoute à `cartes`.
 * @note L’appelant est responsable de la libération des cartes lorsque `cartes` est détruit.
 */
void push_split_for_perm(int* perm, int n, int split, Vecteur* cartes);

/**
 * @brief Pousse dans `cartes` toutes les cartes associées aux splits `0..n` pour une permutation donnée.
 *
 * @param[in] perm  Permutation des indices d’animaux (taille n).
 * @param[in] n     Taille de la permutation (nombre d’animaux).
 * @param[out] cartes Vecteur recevant les `n+1` cartes (`split` de 0 à n).
 * @pre `perm` doit être valide et de taille `n`.
 * @post Ajoute `n+1` cartes au vecteur `cartes`.
 * @sa push_split_for_perm()
 */
void push_all_splits(int* perm, int n, Vecteur* cartes);

/**
 * @brief Génère toutes les permutations (algorithme de Heap) et pousse les cartes (tous les splits).
 *
 * @param[in] k  Profondeur de génération (initialement = n).
 * @param[in] A  Tableau de travail contenant la permutation courante.
 * @param[in] n  Taille totale (nombre d’animaux).
 * @param[out] cartes Vecteur recevant toutes les cartes générées.
 * @pre `A` doit pointer vers un tableau d’au moins `n` éléments.
 * @post Pour chaque permutation, `push_all_splits(A, n, cartes)` est invoqué.
 * @note Implémente l’algorithme **Heap’s algorithm** de génération de permutations en place.
 */
void heap_generer(int k, int* A, int n, Vecteur* cartes);

/**
 * @brief Choisit aléatoirement une carte parmi `cartes`.
 *
 * @param[in] cartes Vecteur contenant des cartes (`int*`).
 * @return Un indice aléatoire valide dans `[0..cartes->nbElements-1]`.
 * @pre `cartes->nbElements > 0`.
 * @note La distribution dépend de l’état du générateur (`rand()`/`srand()`).
 */
int choisirRandomCarte(Vecteur* cartes);

/**
 * @brief Distribue les animaux d’une carte vers les deux podiums (Bleu et Rouge).
 *
 * `arr[0]` détermine `split` :
 * - Les `split` premiers indices (dans `arr[1..split]`) sont ajoutés au podium **Bleu**.
 * - Les indices restants (dans `arr[split+1..n]`) sont ajoutés au podium **Rouge**.
 *
 * @param[in] arr      Carte au format défini (`arr[0]=split`, `arr[1..n]`=perm).
 * @param[in] n        Nombre total d’animaux (taille de la permutation).
 * @param[out] podium_b Podium Bleu (réinitialisé puis rempli).
 * @param[out] podium_r Podium Rouge (réinitialisé puis rempli).
 * @pre `arr` doit pointer vers au moins `n+1` éléments ; `0 ≤ arr[0] ≤ n`.
 * @post Les podiums sont vidés (`clearPodium`) puis remplis selon la carte.
 * @sa genererToutesLesCartes(), push_split_for_perm()
 */
void distrbuerAuxPodiums(int* arr, int n, Podium* podium_b, Podium* podium_r);

