/**
 * @file animal.h
 * @brief Types et opérations pour gérer des animaux et un conteneur d’animaux.
 *
 * Ce module définit le type `Animal`, le type `Animaux` (basé sur `Vecteur`)
 * et les fonctions permettant de créer, stocker, accéder et mélanger des animaux.
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteur.h"

/**
 * @brief Représente un animal par son nom.
 */
typedef struct {
    char* nom_animal; /**< Chaîne C contenant le nom de l’animal. */
} Animal;

/**
 * @brief Conteneur d’animaux basé sur un vecteur dynamique.
 */
typedef Vecteur Animaux;

/**
 * @brief Crée un animal en copiant son nom.
 *
 * @param[in] nom Chaîne C représentant le nom de l’animal.
 * @return Un pointeur vers un `Animal` initialisé, ou `NULL` en cas d’erreur.
 * @pre `nom` n’est pas `NULL`.
 */
Animal* creerAnimal(const char* nom);

/**
 * @brief Initialise un conteneur d’animaux.
 *
 * @param[out] animaux Adresse du conteneur à initialiser.
 * @param[in] capacite Capacité initiale du conteneur.
 * @return `1` si l’initialisation a réussi, `0` sinon.
 * @pre `animaux` n’est pas `NULL` et `capacite >= 1`.
 */
int initAnimaux(Animaux* animaux, int capacite);

/**
 * @brief Crée un animal et l’ajoute au conteneur.
 *
 * @param[in,out] animaux Conteneur d’animaux.
 * @param[in] nom Nom de l’animal à ajouter.
 * @return `1` si l’ajout a réussi, `0` sinon.
 * @pre `animaux` est initialisé et `nom` n’est pas `NULL`.
 */
int ajouterAnimal(Animaux* animaux, const char* nom);

/**
 * @brief Accède à un animal du conteneur par son indice.
 *
 * @param[in] animaux Conteneur d’animaux.
 * @param[in] i Indice de l’animal.
 * @return Un pointeur vers l’`Animal`, ou `NULL` si l’indice est invalide.
 * @pre `animaux` est initialisé et `0 <= i < taille(animaux)`.
 */
Animal* obtenirAnimal(const Animaux* animaux, int i);

/**
 * @brief Génère une permutation aléatoire des indices d’animaux.
 *
 * @param[in] n_animaux Nombre d’animaux.
 * @return Un tableau d’entiers de taille `n_animaux` contenant une permutation
 *         des indices, ou `NULL` en cas d’erreur.
 * @pre `n_animaux > 0`.
 */
int* shuffleAnimaux(int n_animaux);
