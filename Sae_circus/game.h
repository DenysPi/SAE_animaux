/**
 * @file game.h
 * @brief Gestion de l’état du jeu, initialisation et boucle principale.
 *
 * Ce module définit la structure `Game`, l’initialisation complète d’une partie
 * et la boucle principale qui pilote les tours, l’exécution des commandes
 * et la distribution des cartes.
 */

#pragma once
#pragma warning(disable:4996)

#include "affichage.h"

/**
 * @brief Structure représentant l’état d’une partie.
 */
typedef struct {
    Animaux* animaux;
    Commandes* commandes;
    Joueurs* joueurs;

    Podium* podium_b;
    Podium* podium_r;

    Podium* target_b;
    Podium* target_r;

    Vecteur* cartes;
} Game;

/**
 * @brief Initialise une partie à partir d’un fichier de configuration et d’une liste de joueurs.
 *
 * @param[in,out] game État du jeu à initialiser.
 * @param[in] fichier Fichier de configuration.
 * @param[in] nb_joueurs Nombre de joueurs.
 * @param[in] noms Tableau contenant les noms des joueurs.
 * @return `0` si l’initialisation réussit, `-1` sinon.
 * @pre `game`, `fichier` et `noms` ne sont pas `NULL`.
 */
int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms);

/**
 * @brief Lance la boucle principale du jeu.
 *
 * @param[in,out] game État du jeu.
 * @return `0` à la fin normale du jeu.
 * @pre `game` est initialisé.
 */
int gameLoop(Game* game);

/**
 * @brief Distribue aléatoirement des cartes vers les podiums courants et cibles.
 *
 * @param[in] cartes Collection de cartes pour les podiums courants.
 * @param[in] nb_animaux Nombre total d’animaux.
 * @param[in,out] game État du jeu.
 * @pre `cartes` n’est pas `NULL`, `cartes->nbElements > 0` et `game` est initialisé.
 */
void distribuerCarteAleatoire(Vecteur* cartes, int nb_animaux, Game* game);


