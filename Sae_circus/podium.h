/**
 * @file podium.h
 * @brief Gestion des podiums : initialisation, manipulation, clonage et comparaison.
 *
 * Un podium est représenté par un `Vecteur` stockant des indices d’animaux.
 * Ce module fournit les opérations pour gérer ces podiums.
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include "animal.h"

/**
 * @brief Type représentant un podium.
 */
typedef Vecteur Podium;

/**
 * @brief Initialise un podium.
 *
 * @param[out] p Podium à initialiser.
 * @param[in] capacite Capacité initiale.
 * @return `1` si l’initialisation réussit, `0` sinon.
 */
int initPodium(Podium* p, int capacite);

/**
 * @brief Ajoute un animal en haut du podium.
 *
 * @param[in,out] p Podium cible.
 * @param[in] index_animal Indice de l’animal.
 * @return `1` si l’ajout réussit, `0` sinon.
 */
int ajouterPodiumAnimal(Podium* p, int index_animal);

/**
 * @brief Supprime un animal à une position donnée.
 *
 * @param[in,out] p Podium cible.
 * @param[in] index_animal Position à supprimer.
 */
void supprimerPodiumAnimal(Podium* p, int index_animal);

/**
 * @brief Indique si un animal est présent dans le podium.
 *
 * @param[in] p Podium.
 * @param[in] index_animal Indice à rechercher.
 * @return `1` si présent, `0` sinon.
 */
int presentAuPodium(Podium* p, int index_animal);

/**
 * @brief Compare deux podiums.
 *
 * @param[in] p_1 Premier podium.
 * @param[in] p_2 Second podium.
 * @return `1` si les deux podiums sont identiques, `0` sinon.
 */
int comparer2Podiums(Podium* p_1, Podium* p_2);

/**
 * @brief Crée une copie d’un podium.
 *
 * @param[in] src Podium source.
 * @return Un nouveau podium contenant les mêmes éléments, ou `NULL` en cas d’erreur.
 */
Podium* clonePodium(const Podium* src);

/**
 * @brief Libère un podium et son contenu.
 *
 * @param[in,out] p Podium à libérer.
 */
void freePodium(Podium* p);

/**
 * @brief Vide le contenu d’un podium.
 *
 * @param[in,out] p Podium à vider.
 */
void clearPodium(Podium* p);

/**
 * @brief Calcule la taille maximale parmi quatre podiums.
 *
 * @param[in] p_b Podium Bleu courant.
 * @param[in] p_r Podium Rouge courant.
 * @param[in] t_b Podium Bleu cible.
 * @param[in] t_r Podium Rouge cible.
 * @return Le nombre maximal d’éléments.
 */
int maxTaillePodiums(const Podium* p_b, const Podium* p_r, const Podium* t_b, const Podium* t_r);

/**
 * @brief Copie le contenu d’un podium vers un autre.
 *
 * @param[in,out] dest Podium destination.
 * @param[in] src Podium source.
 * @return `1` si la copie réussit, `0` sinon.
 */
int remplacerContenuPodium(Podium* dest, const Podium* src);

/**
 * @brief Trouve la longueur du nom d’animal le plus long dans un podium.
 *
 * @param[in] animaux Conteneur d’animaux.
 * @param[in] podium Podium à analyser.
 * @param[in] type Type du podium.
 * @return La longueur du nom le plus long, ou 0 si le podium est vide.
 */
int trouverAnimalPlusLongue(Animaux* animaux, Podium* podium, int type);


