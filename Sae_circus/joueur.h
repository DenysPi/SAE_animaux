/**
 * @file joueur.h
 * @brief Gestion des joueurs : création, ajout, recherche et gestion des tours.
 *
 * Ce module définit le type `Joueur`, le conteneur `Joueurs` et les fonctions
 * permettant de créer, stocker et manipuler les joueurs et leurs scores.
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteur.h"

/**
 * @brief Représente un joueur.
 */
typedef struct {
    char* nom;
    int tour;
    int points;
} Joueur;

/**
 * @brief Conteneur de joueurs.
 */
typedef Vecteur Joueurs;

/**
 * @brief Crée un joueur à partir de son nom.
 *
 * @param[in] nom Nom du joueur.
 * @return Un pointeur vers un joueur initialisé, ou `NULL` en cas d’erreur.
 * @pre `nom` n’est pas `NULL`.
 */
Joueur* creerJoueur(const char* nom);

/**
 * @brief Initialise un conteneur de joueurs.
 *
 * @param[out] joueurs Conteneur à initialiser.
 * @param[in] capacite Capacité initiale.
 * @return `1` si l’initialisation réussit, `0` sinon.
 * @pre `joueurs` n’est pas `NULL` et `capacite >= 1`.
 */
int initJoueurs(Joueurs* joueurs, int capacite);

/**
 * @brief Ajoute un joueur au conteneur.
 *
 * @param[in,out] joueurs Conteneur de joueurs.
 * @param[in] nom Nom du joueur.
 * @return `1` si l’ajout réussit, `0` sinon.
 * @pre `joueurs` est initialisé et `nom` n’est pas `NULL`.
 */
int ajouterJoueur(Joueurs* joueurs, const char* nom);

/**
 * @brief Accède à un joueur par son indice.
 *
 * @param[in] joueurs Conteneur de joueurs.
 * @param[in] i Indice du joueur.
 * @return Un pointeur vers le joueur ou `NULL` si l’indice est invalide.
 */
Joueur* obtenirJoueur(const Joueurs* joueurs, int i);

/**
 * @brief Recherche un joueur par son nom.
 *
 * @param[in] joueurs Conteneur de joueurs.
 * @param[in] nom Nom du joueur.
 * @return Un pointeur vers le joueur ou `NULL` si non trouvé.
 */
Joueur* obtenirJoueurParNom(const Joueurs* joueurs, const char* nom);

/**
 * @brief Indique si un joueur est autorisé à jouer.
 *
 * @param[in] joueurs Conteneur de joueurs.
 * @param[in] nom Nom du joueur.
 * @return `1` si le joueur existe et peut jouer, `0` sinon.
 */
int peutJouer(const Joueurs* joueurs, char* nom);

/**
 * @brief Indique si un joueur existe.
 *
 * @param[in] joueurs Conteneur de joueurs.
 * @param[in] nom Nom du joueur.
 * @return `1` si le joueur est trouvé, `0` sinon.
 */
int joueurExiste(const Joueurs* joueurs, char* nom);

/**
 * @brief Ajoute un point à un joueur.
 *
 * @param[in,out] joueurs Conteneur de joueurs.
 * @param[in] nom_j Nom du joueur.
 * @pre Le joueur existe.
 */
void ajouterPointJoueur(Joueurs* joueurs, char* nom_j);

/**
 * @brief Réactive le tour de tous les joueurs.
 *
 * @param[in,out] joueurs Conteneur de joueurs.
 */
void remetreTours(Joueurs* joueurs);

/**
 * @brief Retourne le dernier joueur actif.
 *
 * @param[in] joueurs Conteneur de joueurs.
 * @return Le joueur dont le tour est actif, ou `NULL` s’il n’y en a aucun.
 */
Joueur* lastPerson(Joueurs* joueurs);
