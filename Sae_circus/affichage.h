
/**
 * @file affichage.h
 * @brief Fonctions d’affichage pour le jeu (commandes, podiums, résultats).
 */

#pragma once
#include "config.h"

/**
 * @brief Affiche la liste des commandes présentes sous forme compacte.
 * @param commandes Conteneur des commandes à afficher.
 */
void CommandesPresentes(Commandes* commandes);

/**
 * @brief Affiche un message indiquant qu’un ordre n’existe pas.
 */
void ordreExistePas(void);

/**
 * @brief Affiche un message indiquant qu’un ordre ne peut pas être exécuté.
 */
void ordreErreur(void);

/**
 * @brief Indique qu’une séquence ne mène pas à la situation attendue et que le joueur ne peut plus jouer durant ce tour.
 * @param j Joueur concerné.
 */
void ordreIncorect(Joueur* j);

/**
 * @brief Indique que le joueur ne peut pas jouer (version basée sur le nom).
 * @param j Nom du joueur (chaîne C).
 */
void joueurPeutPasJouer(char* j);

/**
 * @brief Affiche en colonnes la disposition des podiums (Bleu/Rouge) et des cibles (Bleu/Rouge).
 * @param a        Référentiel des animaux (pour les noms).
 * @param b        Podium Bleu courant.
 * @param r        Podium Rouge courant.
 * @param target_b Podium Bleu objectif.
 * @param target_r Podium Rouge objectif.
 */
void afficherPodiums(Animaux* a, Podium* b, Podium* r, Podium* target_b, Podium* target_r);

/**
 * @brief Affiche l’attribution d’un point à un joueur.
 * @param j         Nom du joueur (chaîne C).
 * @param situation Indicateur de situation (0 : point normal ; autre : point car lui seul peut encore jouer).
 */
void gagnerPoint(char* j, int situation);

/**
 * @brief Affiche les résultats (scores) pour l’ensemble des joueurs.
 * @param joueurs Ensemble des joueurs.
 */
void afficherResultats(Joueurs* joueurs);

/**
 * @brief Affiche un message d’erreur lors de l’identification de la commande au lancement.
 */
void lancementErrorCommande(void);

/**
 * @brief Affiche un message si le nombre de joueurs est insuffisant.
 */
void pasAssesDesJoueurs(void);

/**
 * @brief Indique qu’aucun joueur correspondant au nom fourni n’existe.
 */
void joueurJouePas(void);

