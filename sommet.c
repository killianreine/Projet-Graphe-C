#include "sommet.h"
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Implémente les fonctions déclarées dans sommet.h

Sommet* creerSommet(int id, float x, float y) {
    Sommet* nouveauSommet = (Sommet*)malloc(sizeof(Sommet));
    if (!nouveauSommet) {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }

    nouveauSommet->id = id;
    nouveauSommet->x = x;
    nouveauSommet->y = y;
    nouveauSommet->cardinalite = 0;
    nouveauSommet->voisins = NULL;
    nouveauSommet->color=-1;
    nouveauSommet->pi=(int)INFINITY; 
    nouveauSommet->parent=-1;
    return nouveauSommet;
}

void ajouterVoisin(Sommet* sommet, Sommet* SommetVoisin) {
    sommet->cardinalite++;
    sommet->voisins = (Sommet**)realloc(sommet->voisins, sommet->cardinalite * sizeof(Sommet*));
    if (!sommet->voisins) {
        printf("Erreur lors de la réallocation de mémoire pour sommet\n");
        exit(2);
    }
    sommet->voisins[sommet->cardinalite - 1] = SommetVoisin;

    SommetVoisin->cardinalite++;
    SommetVoisin->voisins = (Sommet**)realloc(SommetVoisin->voisins, SommetVoisin->cardinalite * sizeof(Sommet*));
    if (!SommetVoisin->voisins) {
        printf("Erreur lors de la réallocation de mémoire pour SommetVoisin\n");
        exit(3);
    }
    SommetVoisin->voisins[SommetVoisin->cardinalite - 1] = sommet;
}

int rechercherVoisin(Sommet* sommet, Sommet* voisin){
    for(int i = 0; i<sommet->cardinalite; i++){
        if(sommet->voisins[i]==voisin){
            return i;
        }
    }
    exit(4);
}

void retirerVoisin(Sommet* sommet, Sommet* sommetEx){
    // Recherche dans voisin sommet la position du sommet a supprimer
    // Décale les sommets qui reste
    int i = rechercherVoisin(sommet, sommetEx);
    int j = rechercherVoisin(sommetEx, sommet);
    for (int k = i; k<sommet->cardinalite-1; k++){
        sommet->voisins[k]=sommet->voisins[k+1];
    }
    for (int l = j; l<sommetEx->cardinalite-1; l++){
        sommetEx->voisins[l]=sommetEx->voisins[l+1];
    }
    sommet->cardinalite-=1;
    sommetEx->cardinalite-=1;
    sommet->voisins = (Sommet**)realloc(sommet->voisins, sommet->cardinalite * sizeof(Sommet*));
    sommetEx->voisins = (Sommet**)realloc(sommetEx->voisins, sommetEx->cardinalite * sizeof(Sommet*));
}

void libererSommet(Sommet* sommet) {
    if (sommet) {
        free(sommet->voisins);
        free(sommet);
    }
}

void afficherVoisins(Sommet* s) {
    printf("Voisins du sommet %d : [", s->id);
    for (int i = 0; i < s->cardinalite; i++) {
        printf("%d", s->voisins[i]->id);
        if (i < s->cardinalite - 1) printf(", ");
    }
    printf("]\n");
}

void afficherSommet(Sommet* s){
    if (!s) {
        printf("Erreur d'affichage de le sommet !\n");
        return;
    }
    printf("Sommet [%d] : (%.2f, %.2f) |%d| Parent=%d.\n", s->id, s->x, s->y, s->cardinalite, s->parent);
}
