#include <stdio.h>
#include <stdlib.h>
#include "latex.h"
#include "graphe.h"
#include <math.h>
#include "graphe.h"

const char* color[] = {"red", "blue", "green", "yellow", "purple", "orange", "pink", "brown", 
        "gray", "cyan", "magenta", "lime", "navy", "teal", "olive", "maroon", "coral", 
        "gold", "silver", "indigo", "violet", 
        "turquoise", "salmon", "plum", "orchid", "khaki", "tan", "beige", "lavender", "crimson"};

void genererLatex(Graphe* g, const char* nomFichier) {
    if (!g || !nomFichier) {
        printf("Erreur : Graphe ou nom de fichier non valide.\n");
        return;
    }

    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur : Impossible de créer le fichier LaTeX.\n");
        return;
    }

    // Début du document LaTeX
    fprintf(fichier, "\\documentclass{article}\n");
    fprintf(fichier, "\\usepackage{tikz}\n");
    //
    fprintf(fichier, "\\usepackage[dvipsnames]{xcolor}");
    fprintf(fichier, "\\usepackage{geometry}");
    fprintf(fichier, "\\geometry{hmargin=0.5cm,vmargin=0.5cm}");
    fprintf(fichier, "\\begin{document}\n");
    fprintf(fichier, "\\begin{center}\n");
    fprintf(fichier, "\\begin{tikzpicture}[scale=2, transform shape]\n");

    // Dessiner les sommets
    fprintf(fichier, "%% Sommets\n");
    for (int i = 0; i < g->n; i++) {
        Sommet* s = g->L_sommets[i];
        if(s->color!=-1){
            fprintf(fichier, "\\node[draw, circle, fill=%s] (%d) at (%f, %f) {%d};\n", color[s->color], s->id, s->x, s->y, s->id);
        }
        else
        fprintf(fichier, "\\node[draw, circle] (%d) at (%f, %f) {%d};\n", s->id, s->x, s->y, s->id);
    }

     // Ajouter les arêtes
    for (int i = 0; i < g->m; i++) {
        Arrete* arrete = g->L_arretes[i];
        Sommet* s1 = rechercheSommetAvecID(g, arrete->s1);
        Sommet* s2 = rechercheSommetAvecID(g, arrete->s2);

        //Si les extrémités des arrêtes sont des sommets différents
        if (s1 != s2) {
            // Dessiner l'arête
            if(arrete->color!=-1){
                fprintf(fichier, "\\draw[color=orange!50!yellow!50!red, thick] (%d) -- (%d);\n", s1->id, s2->id);
            }else{
                fprintf(fichier, "\\draw (%d) -- (%d);\n", s1->id, s2->id);
            }

            // Calculer la position du poids au centre
            float centerX = (s1->x + s2->x) / 2.0;
            float centerY = (s1->y + s2->y) / 2.0;

            // Placer le poids avec un fond blanc et une police plus petite
            fprintf(fichier, "\\node[fill=white, inner sep=2pt, text=black, font=\\tiny] at (%.2f, %.2f) {%d};\n",
                    centerX, centerY, arrete->poids);
        } else {
            // Dessiner la boucle (autocirculation) pour le sommet
            float loopRadius = 0.4; // Rayon du cercle de la boucle
            float angle = 45.0; // Angle de décalage pour éviter que le texte ne soit superposé au sommet
            float loopX = s1->x + loopRadius * cos(angle * M_PI / 180.0)+0.1; // Calcul de la position X
            float loopY = s1->y + loopRadius * sin(angle * M_PI / 180.0); // Calcul de la position Y

            // Dessiner la boucle autour du sommet (cercle)
            fprintf(fichier, "\\draw[rotate around={%f:(%f,%f)}, color=blue] (%f,%f) circle (%f);\n", 
                    angle, s1->x, s1->y, s1->x, s1->y, loopRadius);

            // Placer le poids au centre de la boucle avec un fond blanc et une police plus petite
            fprintf(fichier, "\\node[->, inner sep=2pt, text=blue, font=\\tiny, fill=none] at (%.2f, %.2f) {%d};\n",
                    loopX, loopY, arrete->poids);
        }
    }

    // Fin du TikZ et du document
    fprintf(fichier, "\\end{tikzpicture}\n");
    fprintf(fichier, "\\end{center}\n");
    fprintf(fichier, "\\end{document}\n");

    fclose(fichier);
    printf("Fichier LaTeX généré : %s\n", nomFichier);
}
