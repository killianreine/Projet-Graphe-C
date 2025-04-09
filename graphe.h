#ifndef GRAPHE_H
#define GRAPHE_H

#include "sommet.h"
#include "arretes.h"
#include <stdbool.h>
#define true 1
#define false 0

typedef struct Graphe {
    int n;  // nombre de sommets
    int m; // nombre d'arretes
    struct Sommet** L_sommets; 
    struct Arrete** L_arretes; 
} Graphe;



// Créer le graphe
Graphe* creerGraphe();

// Détruire le graphe
void detruireGraphe(Graphe* g);

// Ajouter[enlever] arrete, sommet
void ajouterArrete(Graphe* g, Arrete* a);
void ajouterSommet(Graphe* g, Sommet* s);
void retirerArrete(Graphe* g, Arrete* a);
void retirerArreteDeSommet(Graphe* g, Arrete* a);
void retirerSommet(Graphe* g, Sommet* s);

bool arreteExistante(Graphe* g, Arrete* a);
Sommet* rechercheSommetAvecID(Graphe* g, int idSommet);
int rechercheArrete(Graphe* g, Arrete* a);

// Afficher le graphe
void afficherGraphe(Graphe* g);
void genererCodeLatexGraphe(Graphe*);

// Inverser la liste des sommets trié
void inverserLSommets(Sommet** listeSommet, int nbSommet);

// Algorithmes de traitements, de colorations, ... relatif aux graphes
Sommet** trierSommets(Graphe* g);
void trierArretes(Graphe* g);
void algoWelshPowell(Graphe* g); //Algo de coloration de WELSH & POWELL
int algoDijkstra(Graphe* G, int idS1, int idS2); //Algo du plus court chemin
#endif // GRAPHE_H
