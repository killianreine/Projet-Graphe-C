#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sommet.h"
#include "arretes.h"
#include "graphe.h"
#include "lectureFichierGraphe.h"
#include "latex.h"

// Fonction pour générer un PDF à partir d'un fichier .tex
void generepdf(const char* fichierTex) {
    char commande[256];
    
    // Construire la commande pour pdflatex
    snprintf(commande, sizeof(commande), "pdflatex -interaction=nonstopmode -output-directory=./ %s", fichierTex);
    
    // Exécuter la commande
    int retour = system(commande);
    
    // Vérifier si la commande a réussi
    if (retour != 0) {
        fprintf(stderr, "Erreur : Échec de la génération du PDF pour %s\n", fichierTex);
    } else {
        printf("PDF généré avec succès pour %s\n", fichierTex);
    }
}


int main() {
    srand(time(NULL));
    
    //Ouverture du fichier
    FILE* fichier = ouvrirFichier("graphe1.txt");
    if (!fichier) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier");
        return -1;
    }
    Graphe* g = lireGraphe(fichier);

    //Ajout d'une arrete
    /*Arrete* a07 = creerArrete(14, g->L_sommets[0], g->L_sommets[7]);
    Arrete* a00 = creerArrete(14, g->L_sommets[0], g->L_sommets[4]);
    Arrete* a11 = creerArrete(14, g->L_sommets[4], g->L_sommets[2]);
    Arrete* a22 = creerArrete(14, g->L_sommets[0], g->L_sommets[1]);
    Arrete* a33 = creerArrete(14, g->L_sommets[0], g->L_sommets[9]);
    Arrete* a44 = creerArrete(14, g->L_sommets[4], g->L_sommets[4]);
    a07->poids=14;
    ajouterArrete(g, a07);
    ajouterArrete(g, a00);
    ajouterArrete(g, a11);
    ajouterArrete(g, a22);
    ajouterArrete(g, a33);
    ajouterArrete(g, a44);*/

    
    //Tri de mon graphe
    Sommet** listeTriee = trierSommets(g);
    //trierArretes(g);

    //algoWelshPowell(g);
    int distance = algoDijkstra(g, 4, 6);
    //Génération LATEX puis PDF
    genererLatex(g, "grapheCourant.tex");
    generepdf("grapheCourant.tex");

    //Affichage du graphe "trié"
    afficherGraphe(g);
    printf("Distance : %d \n", distance);
    afficherGraphe(g);
    //inverserLSommets(g);
    //Fermeture du fichier
    fermerFichier(fichier);
    return 0;
}