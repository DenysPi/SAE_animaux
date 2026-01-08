
/**
 * @file config.h
 * @brief Chargement de la configuration du jeu, utilitaires de lecture de lignes/words et fonctions de préparation des joueurs/podiums.
 *
 * Ce module fournit :
 * - des utilitaires de lecture robuste de lignes depuis un flux et de découpage en tokens,
 * - le chargement de la configuration depuis un fichier (liste des animaux, liste des commandes autorisées),
 * - l'initialisation des joueurs à partir d'une liste de noms,
 * - une fonction utilitaire de sélection du plus grand podium parmi quatre (`max4`).
 *
 * @note Les types structurés sont déclarés dans les modules inclus :
 *       - `animal.h` pour `Animaux` (alias de `Vecteur`) et `Animal`,
 *       - `commandes.h` pour `Commandes` et `Commande`,
 *       - `joueur.h` pour `Joueurs` et `Joueur`,
 *       - `podium.h` (transitivement) pour `Podium`.
 * @warning Gestion mémoire : certaines fonctions retournent des zones **allouées dynamiquement**
 *          que l’appelant doit **libérer** (`free`) pour éviter les fuites (cf. `readFullLine`, `splitLineAndCount`).
 */

#pragma once
#pragma warning(push)
#pragma warning(disable:4996)

#include <stdio.h>

#include "animal.h"
#include "commandes.h"
#include "joueur.h"

/**
 * @brief Initialise une structure `Joueurs` et y ajoute `nb_joueurs` joueurs par leurs noms.
 *
 * @param[out] joueurs     Conteneur des joueurs à initialiser.
 * @param[in]  nb_joueurs  Nombre de joueurs à ajouter.
 * @param[in]  noms        Tableau de `nb_joueurs` chaînes C (terminées par '\\0') contenant les noms.
 * @return `0` en cas de succès ; un code d’erreur non nul si l’initialisation/ajout échoue (selon implémentation).
 * @pre `joueurs` non nul ; `nb_joueurs >= 0` ; `noms` non nul et de taille au moins `nb_joueurs`.
 * @post Le conteneur `joueurs` est initialisé et contient `nb_joueurs` entrées.
 * @sa initJoueurs(), ajouterJoueur()
 */
int loadJoueurs(Joueurs* joueurs, int nb_joueurs, char** noms);

/**
 * @brief Charge la configuration du jeu à partir d’un fichier texte.
 *
 * Format attendu (2 lignes) :
 * 1. Ligne 1 : noms d’animaux séparés par des espaces/tabulations.
 * 2. Ligne 2 : commandes autorisées séparées par des espaces/tabulations (ex. "KI LO SO NI MA").
 *
 * @param[in]  fichier Chemin du fichier de configuration.
 * @param[out] a       Conteneur d’animaux (initialisé et rempli).
 * @param[out] c       Conteneur de commandes (initialisé et rempli).
 * @return
 *   - `0` si la configuration est correctement chargée,
 *   - `1` si une commande non autorisée est détectée (ajout refusé),
 *   - `-1` si des paramètres invalides sont fournis (`fichier`, `a` ou `c` nuls),
 *   - (autres codes possibles selon les évolutions).
 * @pre `fichier` non nul ; `a` et `c` non nuls.
 * @post `a` et `c` sont initialisés, et remplis d’après le contenu du fichier.
 * @note Ouvre le fichier en lecture (`fopen`) ; utilise `readFullLine` et `splitLineAndCount`.
 * @warning Les chaînes retournées par `splitLineAndCount` sont **copiées** dans les conteneurs ;
 *          pense à libérer le tableau de tokens si tu l’étends (dans l’implémentation actuelle, chaque token est recopié).
 */
int loadConfig(const char* fichier, Animaux* a, Commandes* c);

/**
 * @brief Découpe une ligne en tokens (séparateurs : espace et tabulation) et retourne le tableau des mots.
 *
 * @param[in]  line   Chaîne C à découper (non modifiée par cette fonction).
 * @param[out] count  Adresse où stocker le nombre de tokens extraits.
 * @return Tableau **alloué dynamiquement** de `count` éléments (`char*`), chaque élément étant
 *         une **copie** de chaque token ; `NULL` en cas d’échec.
 * @pre `line` non nul ; `count` non nul.
 * @post L’appelant est responsable de libérer :
 *       - **chaque** `noms[i]` via `free(noms[i])`,
 *       - puis le tableau `noms` via `free(noms)`.
 * @note Les séparateurs sont `" \\t"`. Les tokens vides ne sont pas retournés.
 */
char** splitLineAndCount(char* line, int* count);

/**
 * @brief Lit une ligne complète depuis un flux `FILE*`, quelle que soit sa longueur.
 *
 * La lecture s’effectue par blocs de taille fixe et concatène jusqu’à rencontrer un `\\n`
 * (qui est **retiré**) ou une fin de fichier. Retourne la ligne sans retour à la ligne.
 *
 * @param[in] f Flux d’entrée (ouvert en lecture).
 * @return Chaîne **allouée dynamiquement** contenant la ligne lue (sans `\\n`), ou `NULL` si EOF immédiat/erreur.
 * @pre `f` doit pointer vers un flux valide, ouvert en lecture.
 * @post L’appelant doit libérer la chaîne via `free()`.
 * @warning Cette fonction utilise `realloc`/`strcat` successifs ; en cas d’échec d’allocation,
 *          elle retourne `NULL`. Pense à vérifier le retour dans l’appelant.
 */
char* readFullLine(FILE* f);

/**
 * @brief Retourne le podium ayant le plus grand nombre d’éléments parmi quatre.
 *
 * @param[in] p_b Podium Bleu courant.
 * @param[in] p_r Podium Rouge courant.
 * @param[in] t_b Podium cible Bleu.
 * @param[in] t_r Podium cible Rouge.
 * @return Pointeur vers le podium ayant la taille maximale ; en cas d’égalité,
 *         la politique de départage dépend de l’implémentation (ex. premier dans l’ordre).
 * @pre Tous les pointeurs doivent référencer des `Podium` valides.
 * @note Utile pour les affichages alignés (`afficherPodiums`), afin de déterminer la hauteur maximale.
 */
Podium* max4(Podium* p_b, Podium* p_r, Podium* t_b, Podium* t_r);
