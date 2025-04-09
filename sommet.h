#ifndef SOMMET_H
#define SOMMET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition de la structure Sommet
typedef struct Sommet {
    int id;                 // Identifiant unique du sommet
    float x, y;             // Coordonnées du sommet
    int cardinalite;        // Nombre de voisins
    struct Sommet** voisins; // Liste des voisins
    int color;              // La couleur du sommet
    int pi;
    int parent;
} Sommet;

// Fonctions liées aux sommets

// Crée un sommet avec un identifiant unique et des coordonnées x, y
Sommet* creerSommet(int id, float x, float y);

// Ajoute un voisin à un sommet (graphe non orienté)
void ajouterVoisin(Sommet* sommet, Sommet* SommetVoisin);
void retirerVoisin(Sommet* sommet, Sommet* SommetEx);

// Recherche un voisin dans la listeVoisin du sommet
int rechercherVoisin(Sommet* sommet, Sommet* voisin);
void retirerVoisin(Sommet* sommet, Sommet* SommetEx);

// Libère la mémoire allouée à un sommet
void libererSommet(Sommet* sommet);

// Affiche les voisins d'un sommet
void afficherVoisins(Sommet* s);
void afficherSommet(Sommet* s);

#endif // SOMMET_H
