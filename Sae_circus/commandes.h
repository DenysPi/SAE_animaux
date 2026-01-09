/**
 * @file commandes.h
 * @brief Définition du type Commande et gestion de l’exécution des commandes.
 *
 * Ce module définit le type `Commande`, le type `Commandes` (conteneur basé sur `Vecteur`)
 * et les opérations permettant de créer, stocker, vérifier et exécuter des commandes
 * sur deux podiums (Bleu et Rouge).
 *
 * Les commandes reconnues sont : KI, LO, SO, NI et MA.
 */

#pragma once

#include "podium.h"
#include "joueur.h"

/**
 * @brief Représente une commande par son code abrégé.
 */
typedef struct {
    char* nom_commande;
} Commande;

/**
 * @brief Conteneur de commandes.
 */
typedef Vecteur Commandes;

/**
 * @brief Crée une commande à partir de son nom.
 *
 * @param[in] nom Code de la commande (ex. "KI").
 * @return Un pointeur vers une commande initialisée ou `NULL` en cas d’erreur.
 * @pre `nom` n’est pas `NULL`.
 */
Commande* creerCommande(const char* nom);

/**
 * @brief Initialise un conteneur de commandes.
 *
 * @param[out] commandes Conteneur à initialiser.
 * @param[in] capacite Capacité initiale.
 * @return `1` si l’initialisation réussit, `0` sinon.
 * @pre `commandes` n’est pas `NULL` et `capacite >= 1`.
 */
int initCommandes(Commandes* commandes, int capacite);

/**
 * @brief Ajoute une commande autorisée au conteneur.
 *
 * @param[in,out] commandes Conteneur de commandes.
 * @param[in] nom Code de la commande à ajouter.
 * @return `1` si l’ajout réussit, `0` sinon.
 * @pre `commandes` est initialisé et `nom` n’est pas `NULL`.
 */
int ajouterCommande(Commandes* commandes, const char* nom);

/**
 * @brief Récupère une commande à partir de son indice.
 *
 * @param[in] commandes Conteneur de commandes.
 * @param[in] i Indice de la commande.
 * @return Un pointeur vers la commande ou `NULL` si l’indice est invalide.
 * @pre `commandes` est initialisé et `0 ≤ i < taille(commandes)`.
 */
Commande* obtenirCommande(const Commandes* commandes, int i);

/**
 * @brief Empile un animal au sommet d’un podium.
 *
 * @param[in,out] p Podium cible.
 * @param[in] index_animal Indice de l’animal.
 * @return `1` si l’opération réussit, `0` sinon.
 */
int ajouterHaut(Podium* p, int index_animal);

/**
 * @brief Retire l’animal situé au sommet d’un podium.
 *
 * @param[in,out] p Podium cible.
 * @param[out] address_animal Adresse recevant l’indice retiré.
 * @return `1` si l’opération réussit, `0` sinon.
 */
int supprimerHaut(Podium* p, int* address_animal);

/**
 * @brief Retire l’animal situé à la base d’un podium.
 *
 * @param[in,out] p Podium cible.
 * @param[out] adress_animal Adresse recevant l’indice retiré.
 * @return `1` si l’opération réussit, `0` sinon.
 */
int supprimerBas(Podium* p, int* adress_animal);

/**
 * @brief Exécute une commande sur les deux podiums.
 *
 * Les commandes effectuent les mouvements suivants :
 * - KI : Haut Bleu → Haut Rouge  
 * - LO : Haut Rouge → Haut Bleu  
 * - SO : échange des deux sommets  
 * - NI : Bas Bleu → Haut Bleu  
 * - MA : Bas Rouge → Haut Rouge
 *
 * @param[in] nom Code de la commande.
 * @param[in,out] podium_b Podium Bleu.
 * @param[in,out] podium_r Podium Rouge.
 * @return `1` si la commande est exécutée, `0` sinon.
 * @pre `nom` n’est pas `NULL`.
 */
int executerCommande(const char* nom, Podium* podium_b, Podium* podium_r);

/**
 * @brief Indique si une commande est présente dans le conteneur.
 *
 * @param[in] commandes Conteneur de commandes.
 * @param[in] commande Code de la commande.
 * @return `1` si la commande est trouvée, `0` sinon.
 * @pre `commandes` est initialisé et `commande` n’est pas `NULL`.
 */
int verifierCommande(Commandes* commandes, char* commande);

/**
 * @brief Exécute une suite de commandes codées par paires de lettres.
 *
 * Chaque paire de caractères de `com` représente une commande.
 *
 * @param[in] commandes Conteneur des commandes autorisées.
 * @param[in] com Chaîne contenant la séquence de commandes.
 * @param[in,out] podium_b Podium Bleu.
 * @param[in,out] podium_r Podium Rouge.
 * @return
 *   - `1` si toutes les commandes sont exécutées avec succès,
 *   - `0` si une commande n’est pas autorisée,
 *   - `2` si la chaîne est invalide ou si une exécution échoue.
 * @pre `commandes` est initialisé et `com` n’est pas `NULL`.
 */
int executerLigneCommandes(Commandes* commandes, const char* com, Podium* podium_b, Podium* podium_r);
