
/**
 * @file game.h
 * @brief Boucle de jeu, configuration et distribution aléatoire des cartes/podiums.
 *
 * Ce module centralise :
 * - la structure d’état du jeu (`Game`) : référentiels (animaux, commandes, joueurs),
 *   podiums courants (Bleu/Rouge), podiums cibles (Bleu/Rouge), et la collection de cartes ;
 * - l’initialisation complète d’une partie à partir d’un fichier de configuration et d’une liste de joueurs ;
 * - la boucle de jeu principale (lecture des ordres, exécution, scoring, rotation des tours) ;
 * - la distribution d’une carte aléatoire vers les podiums courants et les podiums cibles.
 *
 * @note Les dépendances incluent :
 *       - `commandes.h` (Commandes, exécution des ordres),
 *       - `affichage.h` (présentations et messages),
 *       - `config.h` (chargement config, I/O utilitaires),
 *       - `cartes.h` (génération/distribution de cartes),
 *       - `podium.h` (type Podium, opérations),
 *       - `joueur.h` (type Joueurs/Joueur, opérations).
 */

#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandes.h"
#include "affichage.h"
#include "config.h"
#include "cartes.h"

/**
 * @brief État global d’une partie.
 *
 * Contient les référentiels, les podiums courants/cibles et la collection de cartes
 * qui encode (split + permutation) la répartition des animaux.
 */
typedef struct {
    Animaux* animaux;   ///< Référentiel des animaux (alias de Vecteur contenant des `Animal*` selon ItemV).
    Commandes* commandes; ///< Ensemble des commandes autorisées et disponibles.
    Joueurs* joueurs;   ///< Ensemble des joueurs, leurs points et statut de tour.
    Podium* podium_b;   ///< Podium Bleu courant.
    Podium* podium_r;   ///< Podium Rouge courant.

    Podium* target_b;   ///< Podium Bleu cible (objectif à atteindre).
    Podium* target_r;   ///< Podium Rouge cible (objectif à atteindre).

    Vecteur* cartes;    ///< Collection de cartes (`int*`), chacune: `arr[0]=split`, `arr[1..n]=permutation`.
} Game;

/**
 * @brief Initialise l’état du jeu à partir d’un fichier de configuration et d’une liste de joueurs.
 *
 * Effectue :
 * 1. L’allocation des sous-structures (`Animaux`, `Commandes`, `Joueurs`, `Podium`…).
 * 2. Le chargement de la configuration via @ref loadConfig (animaux + commandes).
 * 3. L’initialisation des joueurs via @ref loadJoueurs.
 * 4. L’initialisation des podiums (Bleu/Rouge + cibles) avec une capacité minimale.
 * 5. La création et le remplissage de `cartes` via @ref genererToutesLesCartes.
 * 6. La distribution initiale aléatoire sur les podiums courants et cibles.
 *
 * @param[in,out] game     État du jeu à initialiser (structure préalablement allouée).
 * @param[in]     fichier  Chemin du fichier de configuration.
 * @param[in]     nb_joueurs Nombre de joueurs à inscrire.
 * @param[in]     noms     Tableau de `nb_joueurs` noms (chaînes C).
 * @return `0` si succès ; `-1` en cas d’erreur (commande invalide, init podiums/joueurs/config échouée).
 * @pre `game` non nul ; `fichier` non nul ; `noms` non nul et de taille ≥ `nb_joueurs`.
 * @post `game` est complètement initialisé et prêt pour @ref gameLoop.
 * @warning Ce module **alloue dynamiquement** toutes les sous-structures.
 *          Prévoir une fonction de destruction (`freeGame`) pour libérer :
 *          - chaque `Animal` (nom + struct) si stocké par pointeur,
 *          - chaque `Commande` (nom + struct) si stocké par pointeur,
 *          - chaque carte (`int*`) contenue dans `cartes`,
 *          - chaque `Podium` et son contenu,
 *          - puis les conteneurs (`detruireVecteur`) et la structure `Game`.
 * @sa loadConfig(), loadJoueurs(), initPodium(), genererToutesLesCartes(), distribuerCarteAleatoire()
 */
int initGameConfig(Game* game, const char* fichier, int nb_joueurs, char** noms);

/**
 * @brief Boucle principale du jeu : lecture des tours, exécution des commandes, scoring et rotation.
 *
 * Fonctionnement (résumé) :
 * - Affiche les commandes présentes et l’état des podiums.
 * - Lit une ligne depuis l’entrée standard : `<nom_joueur> <sequence_commandes>` (chaîne de couples).
 * - Vérifie que le joueur existe et qu’il peut jouer ; clone les podiums courants.
 * - Valide et exécute la séquence via @ref executerLigneCommandes sur les clones.
 * - Si les clones correspondent aux podiums cibles (Bleu/Rouge), attribue un point au joueur,
 *   redistribue une carte aléatoire et réinitialise les tours si fin de rotation.
 * - Sinon, signale l’ordre incorrect et continue.
 * - À la fin (EOF), affiche les résultats via @ref afficherResultats.
 *
 * @param[in,out] game État du jeu (doit avoir été initialisé par @ref initGameConfig).
 * @return `0` à la fin normale ; autre code si gestion d’erreur personnalisée.
 * @pre `game` non nul ; toutes les sous-structures valides et initialisées.
 * @note La lecture utilise @ref readFullLine ; la comparaison des podiums s’appuie sur `comparer2Podiums`.
 * @sa executerLigneCommandes(), afficherPodiums(), afficherResultats()
 */
int gameLoop(Game* game);

/**
 * @brief Distribue une carte aléatoire depuis `cartes` vers les podiums courants,
 *        et une carte aléatoire depuis `game->cartes` vers les podiums cibles.
 *
 * @param[in] cartes      Collection de cartes (`Vecteur` contenant des `int*` au format défini).
 * @param[in] nb_animaux  Taille de permutation pour les podiums courants.
 * @param[in,out] game    État du jeu (doit contenir podiums et `game->cartes` initialisés).
 * @pre `cartes` non nul et `cartes->nbElements > 0` ; `game` et ses podiums non nuls ;
 *      `game->cartes->nbElements > 0`.
 * @post Les podiums `game->podium_b/r` et `game->target_b/r` sont vidés puis remplis
 *       selon les deux cartes aléatoires.
 * @note Choix aléatoire via @ref choisirRandomCarte ; distribution via @ref distrbuerAuxPodiums.
 * @warning Les cartes sont des tableaux alloués dynamiquement (`int*`) ajoutés au vecteur.
 *          Ne pas oublier de les libérer lors de la destruction de `game`.
 */
void distribuerCarteAleatoire(Vecteur* cartes, int nb_animaux, Game* game);

// /**
//  * @brief Libère proprement toutes les ressources associées à un `Game`.
//  *
// //  À implémenter : itérer et libérer les éléments dynamiques (animaux, commandes, cartes),
//  //  détruire les vecteurs/podiums/joueurs, puis libérer les pointeurs de `Game`.
//  //  @param[in,out] game État du jeu à détruire.
//  //  @pre `game` non nul.
//  //  @post Toutes les ressources sont libérées ; pointeurs mis à NULL (si souhaité).
//  */
// // void freeGame(Game* game);

