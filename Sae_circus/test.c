#include "game.h"
#include <assert.h>

static void test_animal() {
    Animaux animaux;
    assert(initAnimaux(&animaux, 1) == 1);

    ajouterAnimal(&animaux, "p1");
    ajouterAnimal(&animaux, "p2");
    ajouterAnimal(&animaux, "p3");

    Animal* p1 = obtenirAnimal(&animaux, 0);
    assert(p1 != NULL);
    assert(strcmp(p1->nom_animal, "p1") == 0);

    
    
}

/* Tests pour Podium */
static void test_podium() {
    Podium p;
    assert(initPodium(&p, 1) == 1);

    assert(ajouterPodiumAnimal(&p, 0) == 1);
    assert(ajouterPodiumAnimal(&p, 1) == 1);
    assert(ajouterPodiumAnimal(&p, 2) == 1);

    assert(presentAuPodium(&p, 0) == 1);
    assert(presentAuPodium(&p, 5) == 0);

    Podium* clone = clonePodium(&p);
    assert(clone != NULL);
    assert(comparer2Podiums(&p, clone) == 1);

    /* cleanup : freePodium libère les éléments int* et detruireVecteur */
    freePodium(clone);
    freePodium(&p);
}

/* Tests pour Joueur */
static void test_joueur() {
    Joueurs js;
    assert(initJoueurs(&js, 1) == 1);

    ajouterJoueur(&js, "alice");
    ajouterJoueur(&js, "bob");

    Joueur* a = obtenirJoueurParNom(&js, "alice");
    Joueur* b = obtenirJoueurParNom(&js, "bob");
    assert(a != NULL && b != NULL);
    assert(joueurExiste(&js, "alice") == 1);
    assert(peutJouer(&js, "alice") == 1);

    ajouterPointJoueur(&js, "alice");
    assert(obtenirJoueurParNom(&js, "alice")->points == 1);

    remetreTours(&js);
    for (int i = 0; i < js.nbElements; ++i) {
        Joueur* j = obtenirJoueur(&js, i);
        assert(j->tour == 1);
    }

    /* cleanup : libérer chaque joueur puis le vecteur */
    for (int i = 0; i < js.nbElements; ++i) {
        Joueur* j = obtenirJoueur(&js, i);
        if (j) {
            free(j->nom);
            free(j);
        }
    }
    detruireVecteur(&js);
}

/* Tests pour Commandes (vérification + exécution basique) */
static void test_commandes() {
    Commandes cmds;
    assert(initCommandes(&cmds, 1) == 1);

    ajouterCommande(&cmds, "KI");
    ajouterCommande(&cmds, "LO");

    assert(verifierCommande(&cmds, "KI") == 1);
    assert(verifierCommande(&cmds, "XX") == 0);

    /* préparer deux podiums pour exécution */
    Podium pb, pr;
    assert(initPodium(&pb, 1) == 1);
    assert(initPodium(&pr, 1) == 1);

    /* ajouter un animal (index) dans pb */
    assert(ajouterPodiumAnimal(&pb, 42) == 1);

    /* exécuter "KI" (déplace le haut de pb vers pr) */
    int res = executerLigneCommandes(&cmds, "KI", &pb, &pr);
    assert(res == 1); /* doit réussir */

    /* cleanup commandes : libérer Commande* créées */
    for (int i = 0; i < cmds.nbElements; ++i) {
        Commande* c = obtenirCommande(&cmds, i);
        if (c) {
            free(c->nom_commande);
            free(c);
        }
    }
    detruireVecteur(&cmds);

    freePodium(&pb);
    freePodium(&pr);
}

int main(void) {

    test_animal();
    printf("test_animal OK\n");

    test_podium();
    printf("test_podium OK\n");

    test_joueur();
    printf("test_joueur OK\n");

    test_commandes();
    printf("test_commandes OK\n");

    printf("Tous les tests reussis.\n");
    return 0;
}