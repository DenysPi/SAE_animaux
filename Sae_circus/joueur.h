
/**
 * @file joueur.h
 * @brief Gestion des joueurs : création, ajout, recherche, scoring et rotation des tours.
 *
 * Ce module définit :
 * - le type `Joueur` (nom, statut de tour, points),
 * - le conteneur `Joueurs` (alias de @ref Vecteur),
 * - les fonctions pour créer, initialiser, ajouter et obtenir des joueurs,
 * - les opérations de jeu : vérification d’existence, autorisation de jouer, attribution de points,
 *   réinitialisation des tours et recherche du dernier joueur actif.
 *
 * @note Les fonctions utilisent l’allocation dynamique pour le champ `nom` des joueurs.
 * @warning L’appelant doit libérer correctement la mémoire (chaque `nom` puis la structure `Joueur`)
 *          avant la destruction du conteneur `Joueurs` pour éviter les fuites.
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
 *
 * Champs :
 * - `nom` : chaîne C allouée dynamiquement (nom du joueur),
 * - `tour` : indicateur (1 = peut jouer, 0 = ne peut pas jouer),
 * - `points` : score accumulé.
 */
typedef struct {
    char* nom;   ///< Nom du joueur (chaîne allouée dynamiquement).
    int tour;    ///< Statut du tour (1 = actif, 0 = inactif).
    int points;  ///< Nombre de points accumulés.
} Joueur;

/**
 * @brief Conteneur de joueurs.
 *
 * Alias direct de @ref Vecteur. Selon la définition de `ItemV`, il stocke des `Joueur*`.
 */
typedef Vecteur Joueurs;

/**
 * @brief Crée un joueur avec un nom donné.
 *
 * @param[in] nom Chaîne C terminée par '\0' (nom du joueur).
 * @return Pointeur vers un `Joueur` initialisé (tour = 1, points = 0), ou `NULL` si mémoire insuffisante.
 * @pre `nom` non nul.
 * @post Le champ `nom` est alloué et copié ; `tour = 1`, `points = 0`.
 * @note L’appelant doit libérer `nom` puis la structure `Joueur` via `free()`.
 */
Joueur* creerJoueur(const char* nom);

/**
 * @brief Initialise un conteneur de joueurs avec une capacité initiale.
 *
 * @param[out] joueurs Conteneur à initialiser.
 * @param[in]  capacite Capacité initiale (>= 1).
 * @return `1` si succès, `0` sinon.
 * @pre `joueurs` non nul ; `capacite >= 1`.
 */
int initJoueurs(Joueurs* joueurs, int capacite);

/**
 * @brief Ajoute un joueur (par son nom) au conteneur.
 *
 * @param[in,out] joueurs Conteneur cible.
 * @param[in]     nom     Nom du joueur à ajouter.
 * @return `1` si succès, `0` sinon (mémoire insuffisante).
 * @pre `joueurs` initialisé ; `nom` non nul.
 * @post Le joueur est créé via @ref creerJoueur et ajouté au vecteur.
 */
int ajouterJoueur(Joueurs* joueurs, const char* nom);

/**
 * @brief Obtient le joueur à l’indice `i`.
 *
 * @param[in] joueurs Conteneur source.
 * @param[in] i       Indice (0 ≤ i < taille(joueurs)).
 * @return Pointeur vers `Joueur` si présent, sinon `NULL`.
 */
Joueur* obtenirJoueur(const Joueurs* joueurs, int i);

/**
 * @brief Recherche un joueur par son nom.
 *
 * @param[in] joueurs Conteneur source.
 * @param[in] nom     Nom à rechercher.
 * @return Pointeur vers `Joueur` si trouvé, sinon `NULL`.
 */
Joueur* obtenirJoueurParNom(const Joueurs* joueurs, const char* nom);

/**
 * @brief Indique si un joueur peut jouer (tour actif).
 *
 * @param[in] joueurs Conteneur source.
 * @param[in] nom     Nom du joueur.
 * @return `1` si le joueur existe et `tour == 1`, `0` sinon.
 */
int peutJouer(const Joueurs* joueurs, char* nom);

/**
 * @brief Vérifie si un joueur existe dans le conteneur.
 *
 * @param[in] joueurs Conteneur source.
 * @param[in] nom     Nom du joueur.
 * @return `1` si trouvé, `0` sinon.
 */
int joueurExiste(const Joueurs* joueurs, char* nom);

/**
 * @brief Ajoute un point à un joueur et réactive son tour.
 *
 * @param[in,out] joueurs Conteneur source.
 * @param[in]     nom_j   Nom du joueur.
 * @pre Le joueur doit exister.
 * @post `points` est incrémenté ; `tour` est remis à 1.
 */
void ajouterPointJoueur(Joueurs* joueurs, char* nom_j);

/**
 * @brief Réinitialise le statut de tour pour tous les joueurs (tous peuvent rejouer).
 *
 * @param[in,out] joueurs Conteneur source.
 * @post Chaque joueur a `tour = 1`.
 */
void remetreTours(Joueurs* joueurs);

/**
 * @brief Retourne le dernier joueur actif (tour == 1).
 *
 * @param[in] joueurs Conteneur source.
 * @return Pointeur vers le joueur trouvé, ou `NULL` si aucun actif.
 */
Joueur* lastPerson(Joueurs* joueurs);
