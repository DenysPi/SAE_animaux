/**
 * @file config.h
 * @brief Chargement de la configuration du jeu et utilitaires de lecture.
 *
 * Ce module fournit :
 * - des fonctions de lecture de lignes et de découpage en mots,
 * - le chargement des animaux et des commandes depuis un fichier,
 * - l’initialisation des joueurs,
 * - un utilitaire pour comparer la taille de plusieurs podiums.
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>
#include "cartes.h"

/**
 * @brief Initialise une structure de joueurs à partir d’une liste de noms.
 *
 * @param[out] joueurs Conteneur de joueurs à initialiser.
 * @param[in] nb_joueurs Nombre de joueurs.
 * @param[in] noms Tableau de chaînes contenant les noms des joueurs.
 * @return `0` si l’opération réussit, une valeur non nulle sinon.
 * @pre `joueurs` n’est pas `NULL`, `nb_joueurs >= 0` et `noms` n’est pas `NULL`.
 */
int loadJoueurs(Joueurs* joueurs, int nb_joueurs, char** noms);

/**
 * @brief Charge la configuration du jeu depuis un fichier.
 *
 * Le fichier contient deux lignes :
 * - la liste des animaux,
 * - la liste des commandes autorisées.
 *
 * @param[in] fichier Chemin du fichier de configuration.
 * @param[out] a Conteneur d’animaux.
 * @param[out] c Conteneur de commandes.
 * @return
 *   - `0` si le chargement réussit,
 *   - `1` si une commande est invalide,
 *   - `-1` si les paramètres sont invalides.
 * @pre `fichier`, `a` et `c` ne sont pas `NULL`.
 */
int loadConfig(const char* fichier, Animaux* a, Commandes* c);

/**
 * @brief Découpe une ligne en mots séparés par des espaces ou tabulations.
 *
 * @param[in] line Ligne à découper.
 * @param[out] count Nombre de mots trouvés.
 * @return Un tableau de chaînes alloué dynamiquement ou `NULL` en cas d’erreur.
 * @pre `line` et `count` ne sont pas `NULL`.
 */
char** splitLineAndCount(char* line, int* count);

/**
 * @brief Lit une ligne complète depuis un flux.
 *
 * @param[in] f Flux d’entrée.
 * @return Une chaîne allouée dynamiquement contenant la ligne, ou `NULL` si fin de fichier ou erreur.
 * @pre `f` est un flux valide ouvert en lecture.
 */
char* readFullLine(FILE* f);

/**
 * @brief Retourne le podium le plus grand parmi quatre.
 *
 * @param[in] p_b Podium Bleu courant.
 * @param[in] p_r Podium Rouge courant.
 * @param[in] t_b Podium Bleu cible.
 * @param[in] t_r Podium Rouge cible.
 * @return Le pointeur vers le podium ayant le plus grand nombre d’éléments.
 * @pre Tous les pointeurs référencent des podiums valides.
 */
Podium* max4(Podium* p_b, Podium* p_r, Podium* t_b, Podium* t_r);

