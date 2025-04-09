#include "arretes.h"
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour time()

// Implémente les fonctions déclarées dans arretes.h

Arrete* creerArrete(int id, Sommet* s1, Sommet* s2) {
    Arrete* nouvelleArrete = (Arrete*)malloc(sizeof(Arrete));
    if (!nouvelleArrete) {
        printf("Erreur : échec de l'allocation de mémoire pour une arête\n");
        exit(7);
    }
    nouvelleArrete->id = id;
    nouvelleArrete->s1 = s1->id;
    nouvelleArrete->s2 = s2->id;
    nouvelleArrete->poids = rand() % 21; // Initialisation du poids à 0
    nouvelleArrete->color=-1;
    return nouvelleArrete;
}


void libererArrete(Arrete* a) {
    free(a);
}

void afficherArrete(Arrete* a) {
    if (!a) {
        printf("Erreur d'affichage de l'arrête !\n");
        exit(6);
    }
    printf("Arrete [%d] : (%d-%d), p=(%d) de couleur=%d\n", a->id, a->s1, a->s2, a->poids, a->color);
}
