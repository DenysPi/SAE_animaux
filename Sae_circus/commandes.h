
/**
 * @file commandes.h
 * @brief Définition du type Commande et opérations de gestion/exécution des commandes.
 *
 * Ce module introduit le type élémentaire `Commande` (nom abrégé de commande),
 * un conteneur `Commandes` (alias de @ref Vecteur) et les opérations pour :
 * - créer/initialiser/ajouter/obtenir des commandes,
 * - manipuler le sommet et la base des podiums,
 * - vérifier et exécuter une commande unitaire,
 * - exécuter une ligne de commandes composée de couples de lettres.
 *
 * Les commandes prises en charge sont : **KI**, **LO**, **SO**, **NI**, **MA**.
 *
 * @note Les types `Podium`, `Joueur` et `Vecteur` sont déclarés respectivement
 *       dans `podium.h`, `joueur.h` et `vecteur.h`.
 * @warning Gestion mémoire : `Commandes` stocke (selon `ItemV`) des `Commande*`.
 *          Si c’est le cas, chaque `Commande` (et son `nom_commande`) doit être libérée
 *          avant la destruction du vecteur, pour éviter les fuites.
 */

#pragma once

#include "podium.h"
#include "joueur.h"

/**
 * @brief Représente une commande (son nom abrégé).
 *
 * Exemple de valeurs valides : "KI", "LO", "SO", "NI", "MA".
 */
typedef struct {
    char* nom_commande; /**< Chaîne C allouée dynamiquement contenant le code de la commande. */
} Commande;

/**
 * @brief Conteneur de commandes.
 *
 * Alias direct de @ref Vecteur. Vérifier la définition de `ItemV` :
 * - si `ItemV` == `Commande*`, le conteneur stocke des pointeurs,
 * - si `ItemV` == `Commande`, le stockage est par valeur.
 */
typedef Vecteur Commandes;

/**
 * @brief Crée une commande en allouant et copiant son nom.
 *
 * @param[in] nom Chaîne C terminée par '\0' (ex. "KI").
 * @return Pointeur vers une `Commande` initialisée en cas de succès, `NULL` si mémoire insuffisante.
 * @pre `nom` doit être non nul et pointer vers une chaîne valide.
 * @post `c->nom_commande` alloué dynamiquement et contenant une copie de `nom`.
 * @note L’appelant est responsable de `free(c->nom_commande)` puis `free(c)`.
 */
Commande* creerCommande(const char* nom);

/**
 * @brief Initialise un conteneur de commandes (vecteur) avec une capacité initiale.
 *
 * @param[out] commandes Adresse du conteneur à initialiser.
 * @param[in]  capacite  Capacité initiale (>= 1).
 * @return `1` en cas de succès, `0` en cas de mémoire insuffisante.
 * @pre `commandes` non nul ; `capacite >= 1`.
 * @post Vecteur interne alloué, `nbElements == 0`.
 */
int initCommandes(Commandes* commandes, int capacite);

/**
 * @brief Ajoute une commande (par son nom) au conteneur si elle est autorisée.
 *
 * Les commandes autorisées sont : "KI", "LO", "SO", "NI", "MA".
 *
 * @param[in,out] commandes Conteneur de commandes initialisé.
 * @param[in]     nom       Nom abrégé de la commande à ajouter.
 * @return `1` si l’ajout a réussi, `0` sinon (commande non autorisée ou mémoire insuffisante).
 * @pre `commandes` initialisé ; `nom` non nul.
 * @post `nbElements` est incrémenté si succès.
 * @note Dans l’implémentation actuelle (`commandes.c`), la fonction **ne retourne pas** de valeur.
 *       Il faut ajouter un `return` approprié (par ex. `return ajouter(commandes, c);` ou `return 1`).
 * @sa creerCommande(), verifierCommande()
 */
int ajouterCommande(Commandes* commandes, const char* nom);

/**
 * @brief Obtient la `Commande` à l’indice `i`.
 *
 * @param[in] commandes Conteneur source.
 * @param[in] i         Indice (0 ≤ i < taille(commandes)).
 * @return Pointeur vers `Commande` si présent, sinon `NULL`.
 * @pre `commandes` initialisé et contient au moins `i+1` éléments.
 */
Commande* obtenirCommande(const Commandes* commandes, int i);

/**
 * @brief Ajoute en haut du podium l’index d’un animal.
 *
 * @param[in,out] p            Podium cible.
 * @param[in]     index_animal Index d’animal à empiler.
 * @return `1` si réussite, `0` sinon (mémoire insuffisante).
 * @post Le sommet du podium contient le nouvel index.
 */
int ajouterHaut(Podium* p, int index_animal);

/**
 * @brief Supprime l’index au sommet du podium et le renvoie par adresse.
 *
 * @param[in,out] p               Podium cible.
 * @param[out]    address_animal  Adresse recevant l’index retiré.
 * @return `1` si réussite, `0` si le podium est vide ou erreur.
 * @post Le sommet est retiré ; `*address_animal` reçoit l’index.
 */
int supprimerHaut(Podium* p, int* address_animal);

/**
 * @brief Supprime l’index en bas du podium et le renvoie par adresse.
 *
 * @param[in,out] p             Podium cible.
 * @param[out]    adress_animal Adresse recevant l’index retiré.
 * @return `1` si réussite, `0` si le podium est vide ou erreur.
 * @post La base est retirée ; `*adress_animal` reçoit l’index.
 */
int supprimerBas(Podium* p, int* adress_animal);

/**
 * @brief Exécute une commande unitaire sur les deux podiums.
 *
 * Sémantique :
 * - `KI` : Haut Bleu → Haut Rouge
 * - `LO` : Haut Rouge → Haut Bleu
 * - `SO` : Échange des Hauts (Rouge ↔ Bleu)
 * - `NI` : Bas Bleu → Haut Bleu
 * - `MA` : Bas Rouge → Haut Rouge
 *
 * @param[in] nom       Nom de la commande (ex. "KI").
 * @param[in,out] podium_b Podium Bleu.
 * @param[in,out] podium_r Podium Rouge.
 * @return `1` si exécution réussie, `0` sinon (mouvement impossible ou commande inconnue).
 * @pre `nom` non nul ; `podium_b`/`podium_r` valides.
 * @warning Dans l’implémentation actuelle, la clause `else if (strcmp(nom, "Q"))` devrait
 *          être `else if (strcmp(nom, "Q") == 0)` si "Q" est une commande à interdire/arrêter.
 */
int executerCommande(const char* nom, Podium* podium_b, Podium* podium_r);

/**
 * @brief Vérifie si une commande est présente dans le conteneur.
 *
 * @param[in] commandes Conteneur de commandes.
 * @param[in] commande  Chaîne C (ex. "KI").
 * @return `1` si présente, `0` sinon.
 * @pre `commandes` initialisé ; `commande` non nul.
 */
int verifierCommande(Commandes* commandes, char* commande);

/**
 * @brief Exécute une ligne de commandes (couples de lettres successifs).
 *
 * La ligne `com` doit contenir un nombre **pair** de caractères ; chaque couple (2 lettres)
 * représente une commande (ex. `"KILO"` → `KI`, `LO`).
 *
 * @param[in] commandes Conteneur des commandes autorisées.
 * @param[in] com       Chaîne C contenant la séquence (longueur paire).
 * @param[in,out] podium_b Podium Bleu.
 * @param[in,out] podium_r Podium Rouge.
 * @return
 *   - `1` si toute la séquence a été exécutée avec succès,
 *   - `0` s’il existe un couple inconnu/non autorisé,
 *   - `2` si la longueur est **impair** ou si l’exécution d’un couple échoue (mouvement impossible).
 * @pre `commandes` initialisé ; `com` non nul.
 * @note Chaque couple est vérifié avec @ref verifierCommande avant exécution par @ref executerCommande.
 */
int executerLigneCommandes(Commandes* commandes, const char* com, Podium* podium_b, Podium* podium_r);
