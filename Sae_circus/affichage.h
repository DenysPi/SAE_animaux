
/**
 * @file affichage.h
 * @brief Fonctions d’affichage et de reporting pour le jeu (commandes, podiums, résultats).
 *
 * Ce module regroupe les services d'affichage destinés à :
 * - présenter les commandes en cours,
 * - reporter les erreurs/états liés aux ordres,
 * - afficher la disposition des podiums (actuels et cibles),
 * - annoncer l’attribution de points,
 * - lister les résultats des joueurs.
 *
 * @note Les types structurés (`Commandes`, `Joueur`, `Animaux`, `Podium`, `Joueurs`) sont déclarés dans @ref config.h.
 */

#pragma once

#include "config.h"

/**
 * @brief Affiche la liste des commandes présentes sous forme compacte.
 *
 * Chaque commande est affichée par son code (ex. "KI", "LO", "SO", "NI", "MA")
 * suivie d’une abréviation de l’effet, et séparée par "|".
 *
 * @param[in] commandes Pointeur vers la structure regroupant les commandes à afficher.
 * @pre `commandes` doit être non nul ; `commandes->elements[i]` et les champs utilisés
 *      (dont `nom_commande`) doivent être valides pour `0 <= i < commandes->nbElements`.
 * @sa ordreExistePas(), ordreErreur()
 */
void CommandesPresentes(Commandes* commandes);

/**
 * @brief Affiche un message indiquant qu’un ordre n’existe pas.
 *
 * @note Message informatif, aucune exception n’est levée.
 */
void ordreExistePas();

/**
 * @brief Affiche un message indiquant qu’un ordre ne peut pas être exécuté.
 *
 * @note Message informatif, aucune exception n’est levée.
 */
void ordreErreur();

/**
 * @brief Informe qu’une séquence ne mène pas à la situation attendue et
 *        que le joueur ne peut plus jouer durant ce tour.
 *
 * @param[in] j Pointeur vers le joueur concerné.
 * @pre `j` doit être non nul et `j->nom` doit référencer une chaîne valide.
 * @sa joueurPeutPasJouer()
 */
void ordreIncorect(Joueur* j);

/**
 * @brief Indique que le joueur ne peut pas jouer (version basée sur le nom).
 *
 * @param[in] j Nom du joueur (chaîne C terminée par '\0').
 * @pre `j` doit être non nul (chaîne valide).
 * @note La définition dans le fichier source doit correspondre à cette signature
 *       pour éviter tout conflit d’édition de liens.
 */
void joueurPeutPasJouer(char* j);

/**
 * @brief Affiche en colonnes la disposition des podiums (Bleu/Rouge) et des cibles (Bleu/Rouge).
 *
 * Présente chaque niveau des podiums actuels et des podiums cibles, en alignant les noms
 * d’animaux sur la même ligne. Le nombre de lignes affichées est le maximum des hauteurs
 * des quatre podiums.
 *
 * @param[in] a        Référentiel des animaux (pour résoudre les noms).
 * @param[in] b        Podium Bleu courant.
 * @param[in] r        Podium Rouge courant.
 * @param[in] target_b Podium cible Bleu.
 * @param[in] target_r Podium cible Rouge.
 * @pre Tous les pointeurs passés doivent être valides ; les indices accédés doivent
 *      être dans les bornes de chaque `Podium`.
 * @note Les colonnes sont formatées avec une largeur fixe pour lisibilité.
 */
void afficherPodiums(Animaux* a, Podium* b, Podium* r, Podium* target_b, Podium* target_r);

/**
 * @brief Affiche l’attribution d’un point à un joueur.
 *
 * @param[in] j         Nom du joueur (chaîne C terminée par '\0').
 * @param[in] situation Indicateur de situation :
 *                      - `0` : point gagné « normal »,
 *                      - autre : point gagné car « lui seul peut encore jouer ».
 * @pre `j` doit être non nul (chaîne valide).
 * @note Affiche un message différent selon la valeur de `situation`.
 */
void gagnerPoint(char* j, int situation);

/**
 * @brief Affiche les résultats (classement, scores, etc.) pour l’ensemble des joueurs.
 *
 * @param[in] joueurs Ensemble des joueurs pour ce tour/partie.
 * @pre `joueurs` doit être non nul et contenir des entrées valides.
 */
void afficherResultats(Joueurs* joueurs);

/**
 * @brief Message d’erreur lors de l’identification de la commande au lancement.
 *
 * @note À utiliser si une commande n’est pas reconnue au démarrage.
 */
void lancementErrorCommande();

/**
 * @brief Affiche un message si le nombre de joueurs est insuffisant.
 *
 * @note Message d’alerte, utile pour la validation des préconditions de partie.
 */
void pasAssesDesJoueurs();

/**
 * @brief Indique qu’aucun joueur correspondant au nom fourni n’existe.
 *
 * @note Message d’information à la suite d’une recherche infructueuse.
 */
void joueurJouePas();
