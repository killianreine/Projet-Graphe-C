#include "sommet.h"
#include "arretes.h"
#include "graphe.h"
#include <stdbool.h>
#include <stdlib.h>

FILE* ouvrirFichier(const char* fichier) {
    FILE* fichierp = fopen(fichier, "r");
    if (!fichierp) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", fichier);
    }
    return fichierp;
}


void fermerFichier(FILE* fichier){
    fclose(fichier);
    printf("Fichier ferme !");
}

Graphe* lireGraphe(FILE* fichier){
    int n, m;
    fscanf(fichier, "%d %d", &n, &m);  // Lire n et m
    printf("%d et %d \n", n, m);

    //Création du graphe
    Graphe* g = creerGraphe();

    // Lire les sommets
    for (int i = 0; i < n; i++) {
        int id = i;  // Chaque sommet reçoit un ID unique (0 à n-1)
        float x, y;
        fscanf(fichier, "%f %f", &x, &y);
        Sommet* sommet = creerSommet(id, x, y);  // Assurez-vous que creerSommet est défini
        ajouterSommet(g, sommet);
    }

    // Lire les arêtes
    for (int i = 0; i < m; i++) {
        int s1, s2;
        fscanf(fichier, "%d %d", &s1, &s2);
        if (s1 >= n || s2 >= n) {
            printf("Erreur : indice de sommet invalide dans les arêtes (%d, %d)\n", s1, s2);
            continue;
        }
        Arrete* arrete = creerArrete(i, g->L_sommets[s1], g->L_sommets[s2]);  // Assurez-vous que creerArrete est défini
        ajouterArrete(g, arrete);
    }
    printf("\n ------------------------------------------------------------- \n");
    afficherGraphe(g);
    return g;
}