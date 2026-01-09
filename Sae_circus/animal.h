
/**
 * @file animal.h
 * @brief Types et opérations pour manipuler des animaux et un conteneur d'animaux.
 *
 * Ce module définit le type élémentaire `Animal` (nom de l’animal),
 * un alias de conteneur `Animaux` basé sur @ref Vecteur, et les fonctions utilitaires
 * pour créer, initialiser, ajouter, obtenir des animaux, ainsi que générer une
 * permutation aléatoire d’indices d’animaux (`shuffleAnimaux`).
 *
 * @note Les fonctions utilisent l’allocation dynamique. L’appelant doit veiller
 *       à la **désallocation** (voir notes ci‑dessous).
 * @sa vecteur.h
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteur.h"

/**
 * @brief Représente un animal (actuellement, uniquement son nom).
 */
typedef struct {
    char* nom_animal; /**< Chaîne C allouée dynamiquement contenant le nom de l’animal. */
} Animal;

/**
 * @brief Conteneur d’animaux.
 *
 * Alias direct de @ref Vecteur. Selon la définition de `ItemV` (dans `itemvecteur.h`),
 * les éléments du vecteur peuvent être :
 * - des **pointeurs** vers `Animal` (cas le plus courant ici), ou
 * - des `Animal` **par valeur**.
 *
 * @note Vérifier la définition de `ItemV` utilisée par le projet pour savoir
 *       si le stockage se fait par valeur ou par pointeur. Les fonctions
 *       de ce module sont écrites pour un stockage **par pointeur** (`Animal*`).
 */
typedef Vecteur Animaux;

/**
 * @brief Crée un animal en allouant et copiant son nom.
 *
 * @param[in] nom Chaîne C terminée par '\\0' représentant le nom de l’animal.
 * @return Pointeur vers un `Animal` initialisé en cas de succès,
 *         `NULL` si la mémoire est insuffisante ou si `nom` est `NULL`.
 * @pre `nom` doit être non nul et pointer vers une chaîne valide.
 * @post `a->nom_animal` est alloué dynamiquement et contient une copie de `nom`.
 *
 * @note L’appelant est responsable de la libération de la mémoire :
 *       d’abord `free(a->nom_animal)`, puis `free(a)`.
 */
Animal* creerAnimal(const char* nom);

/**
 * @brief Initialise un conteneur d’animaux (`Vecteur`) avec une capacité initiale.
 *
 * @param[out] animaux Adresse du conteneur à initialiser.
 * @param[in]  capacite Capacité initiale (>= 1).
 * @return `1` en cas de succès, `0` en cas de mémoire insuffisante.
 * @pre `animaux` doit être non nul ; `capacite >= 1`.
 * @post Le vecteur interne est alloué et `nbElements == 0`.
 *
 * @sa detruireVecteur(), ajouterAnimal()
 */
int initAnimaux(Animaux* animaux, int capacite);

/**
 * @brief Crée un `Animal` et l’ajoute au conteneur.
 *
 * @param[in,out] animaux Conteneur cible (initialisé).
 * @param[in]     nom     Nom de l’animal à ajouter (chaîne C).
 * @return `1` si l’ajout a réussi, `0` sinon (mémoire insuffisante ou paramètres invalides).
 * @pre `animaux` doit être initialisé ; `nom` doit être non nul.
 * @post La taille logique (`nbElements`) de `animaux` est incrémentée si succès.
 *
 * @note L’implémentation actuelle dans `animal.c` :
 *       - crée l’animal avec @ref creerAnimal ;
 *       - appelle `ajouter(animaux, a)` (qui appartient au composant `Vecteur`) ;
 *       - **ne retourne pas de valeur** → il faut **retourner** le statut (par ex. `1` si succès, `0` si échec).
 *
 *       Si `ItemV` stocke des pointeurs, le conteneur doit être détruit en libérant
 *       d’abord chaque `Animal` (son `nom_animal` puis la structure), **avant**
 *       d’appeler `detruireVecteur(animaux)`.
 *
 * @sa creerAnimal(), obtenirAnimal(), detruireVecteur()
 */
int ajouterAnimal(Animaux* animaux, const char* nom);

/**
 * @brief Obtient l’`Animal` à l’indice `i` dans le conteneur.
 *
 * @param[in] animaux Conteneur source.
 * @param[in] i       Indice (0 ≤ i < taille(animaux)).
 * @return Pointeur vers l’`Animal` si présent, sinon `NULL`.
 * @pre `animaux` doit être initialisé et contenir au moins `i+1` éléments.
 *
 * @note Si le vecteur stocke des **pointeurs**, le retour est un `Animal*` direct.
 *       Si le stockage est **par valeur**, adapter la fonction d’accès/lecture.
 */
Animal* obtenirAnimal(const Animaux* animaux, int i);

/**
 * @brief Génère une permutation aléatoire des indices `[0, n_animaux)`.
 *
 * @param[in] n_animaux Nombre total d’animaux.
 * @return Tableau d’entiers alloué dynamiquement de taille `n_animaux`, contenant
 *         une permutation uniforme des indices, ou `NULL` si la mémoire est insuffisante
 *         ou si `n_animaux <= 0`.
 * @pre `n_animaux > 0`.
 * @post Le tableau retourné doit être libéré par l’appelant via `free()`.
 *
 * @note L’aléa dépend de l’état du générateur standard (`rand()`/`srand()`).
 *       L’algorithme utilisé est le **Fisher–Yates** (mélange en place, O(n)).
 */
int* shuffleAnimaux(int n_animaux);
