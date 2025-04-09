#include "sommet.h"
#include "arretes.h"
#include "graphe.h"
#include <stdbool.h>
#include <stdlib.h>

//Ouverture du fichier
FILE* ouvrirFichier(const char* fichier);

// Fermeture du fichier
void fermerFichier(FILE* fichier);

// Lire le fichier
Graphe* lireGraphe(FILE* fichier);