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
 * @pre `nom` n’est*
