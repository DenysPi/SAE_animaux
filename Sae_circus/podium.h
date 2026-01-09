
/**
 * @file podium.h
 * @brief Gestion des podiums : initialisation, ajout/suppression d’animaux, clonage et comparaison.
 *
 * Un podium est représenté par un conteneur `Vecteur` (alias `Podium`) stockant des indices d’animaux (`int*`).
 * Ce module fournit :
 * - des fonctions pour initialiser et manipuler un podium,
 * - des utilitaires pour comparer, cloner, vider et libérer un podium,
 * - des fonctions pour déterminer la taille maximale parmi plusieurs podiums et remplacer un contenu.
 *
 * @note Chaque élément ajouté au podium est un pointeur vers un entier (`int*`) alloué dynamiquement.
 * @warning L’appelant doit libérer correctement la mémoire (via @ref freePodium ou @ref clearPodium)
 *          pour éviter les fuites.
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"


/**
 * @brief Alias de Vecteur pour représenter un podium.
 *
 * Chaque élément est un `int*` (index d’animal).
 */
typedef Vecteur Podium;

/**
 * @brief Initialise un podium avec une capacité donnée.
 *
 * @param[out] p        Podium à initialiser.
 * @param[in]  capacite Capacité initiale (>= 1).
 * @return `1` si succès, `0` sinon.
 */
int initPodium(Podium* p, int capacite);

/**
 * @brief Ajoute un animal (par son index) en haut du podium.
 *
 * @param[in,out] p            Podium cible.
 * @param[in]     index_animal Index de l’animal à ajouter.
 * @return `1` si succès, `0` sinon (mémoire insuffisante).
 * @post Alloue un `int*` et l’ajoute au vecteur.
 */
int ajouterPodiumAnimal(Podium* p, int index_animal);

/**
 * @brief Supprime un animal à une position donnée dans le podium.
 *
 * @param[in,out] p            Podium cible.
 * @param[in]     index_animal Position (indice) à supprimer.
 * @note Ne libère pas la mémoire associée à l’élément supprimé (prévoir @ref clearPodium ou @ref freePodium).
 */
void supprimerPodiumAnimal(Podium* p, int index_animal);

/**
 * @brief Vérifie si un animal (par son index) est présent dans le podium.
 *
 * @param[in] p            Podium cible.
 * @param[in] index_animal Index à rechercher.
 * @return `1` si présent, `0` sinon.
 */
int presentAuPodium(Podium* p, int index_animal);

/**
 * @brief Compare deux podiums (contenu et ordre).
 *
 * @param[in] p_1 Premier podium.
 * @param[in] p_2 Second podium.
 * @return `1` si identiques, `0` sinon.
 */
int comparer2Podiums(Podium* p_1, Podium* p_2);

/**
 * @brief Clone un podium (copie profonde).
 *
 * @param[in] src Podium source.
 * @return Nouveau podium alloué et rempli, ou `NULL` si échec.
 * @note Chaque élément est recopié (nouveau `int*`).
 */
Podium* clonePodium(const Podium* src);

/**
 * @brief Libère complètement un podium (contenu + vecteur).
 *
 * @param[in,out] p Podium à libérer.
 * @post Tous les `int*` sont libérés, puis le vecteur est détruit.
 */
void freePodium(Podium* p);

/**
 * @brief Vide un podium sans le détruire.
 *
 * @param[in,out] p Podium à vider.
 * @post Tous les `int*` sont libérés ; `nbElements = 0`.
 */
void clearPodium(Podium* p);

/**
 * @brief Retourne la taille maximale parmi quatre podiums.
 *
 * @param[in] p_b Podium Bleu courant.
 * @param[in] p_r Podium Rouge courant.
 * @param[in] t_b Podium Bleu cible.
 * @param[in] t_r Podium Rouge cible.
 * @return Taille maximale (nombre d’éléments).
 */
int maxTaillePodiums(const Podium* p_b, const Podium* p_r, const Podium* t_b, const Podium* t_r);

/**
 * @brief Remplace le contenu d’un podium par celui d’un autre.
 *
 * @param[in,out] dest Podium destination (vidé avant copie).
 * @param[in]     src  Podium source.
 * @return `1` si succès.
 * @post Chaque élément est recopié (nouveau `int*`).
 */
int remplacerContenuPodium(Podium* dest, const Podium* src);
