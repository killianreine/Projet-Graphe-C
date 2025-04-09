#ifndef ARRETES_H
#define ARRETES_H

#include <stdbool.h>
#include "sommet.h"

// Définition de la structure Arrete
typedef struct Arrete {
    int id;  // Identifiant de l'arrête
    int s1;  // Identifiant du premier sommet
    int s2;  // Identifiant du second sommet
    int poids; // Poids de l'arrête
    int color; // Couleur de l'arrete
} Arrete;

// Fonctions liées aux arrêtes

// Crée une nouvelle arrête entre deux sommets
Arrete* creerArrete(int identifiant, Sommet* s1, Sommet* s2);

// Libère la mémoire allouée pour une arrête
void libererArrete(Arrete* a);

// Affiche les détails d'une arrête
void afficherArrete(Arrete* a);

#endif // ARRETES_H
