#include "sommet.h"
#include "arretes.h"
#include "graphe.h"
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

Graphe* creerGraphe(){
    Graphe* nouveauGraphe = (Graphe*)malloc(sizeof(Graphe));
    if (!nouveauGraphe) {
        printf("Erreur d'allocation de mémoire\n");
        exit(7);
    }

    nouveauGraphe->L_sommets = NULL;  // Pas de sommets au départ
    nouveauGraphe->L_arretes = NULL;  // Pas d'arêtes au départ
    nouveauGraphe->n = 0;
    nouveauGraphe->m = 0;
    return nouveauGraphe;
}

void detruireGraphe(Graphe* g){
    if (g) {
        // Libération des arêtes et des sommets, s'ils existent
        if (g->L_arretes) {
             for (int i = 0; i < g->m; i++) {
                free(g->L_arretes[i]);  // Libération de chaque sommet
            }
            free(g->L_arretes);
        }
        if (g->L_sommets) {
            for (int i = 0; i < g->n; i++) {
                free(g->L_sommets[i]);  // Libération de chaque sommet
            }
            free(g->L_sommets);  // Libération du tableau des sommets
        }
        free(g);  // Libération du graphe lui-même
    }
}

void ajouterSommet(Graphe* g, Sommet* s){
    if (!g || !s) {
        printf("Erreur : le graphe ou le sommet n'existe pas.\n");
        exit(8);
    }

    g->n += 1;
    g->L_sommets = (Sommet**)realloc(g->L_sommets, g->n * sizeof(Sommet*));
    if (!g->L_sommets) {
        printf("Erreur : échec de la réallocation de mémoire pour les sommets.\n");
        exit(9);
    }

    g->L_sommets[g->n - 1] = s;  // Ajout du nouveau sommet à la fin
}


int rechercheSommet(Graphe* g, Sommet* s) {
    for (int i = 0; i < g->n; i++) {
        if (g->L_sommets[i] == s) {
            return i;
        }
    }
}


int rechercheArrete(Graphe* g, Arrete* a){
    for (int i=0; i<g->m; i++){
        if((g->L_arretes[i]->s1==a->s1 && g->L_arretes[i]->s2==a->s2)
        || (g->L_arretes[i]->s2==a->s1 && g->L_arretes[i]->s1==a->s2)){
            return i;
        }
    }
    return -1;
}

Sommet* rechercheSommetAvecID(Graphe* g, int idSommet){
    for (int i=0; i<g->n; i++){
        if(g->L_sommets[i]->id==idSommet){
            return g->L_sommets[i];
        }
    }
    exit(11);
}

bool arreteExistante(Graphe* g, Arrete* a){
    if(!g || !a){
        return false;
    }
    for (int i=0; i<g->m; i++){
        if(g->L_arretes[i]->s1==a->s1 && g->L_arretes[i]->s2==a->s2){
            printf("Arrete existante !\n");
            return true;
        }
    }
    return false;
}

void ajouterArrete(Graphe* g, Arrete* a){
    if (!g || !a){
        printf("Erreur : Le graphe et/ou l'arrete n'existe pas?\n");
        return;
    }
    Sommet* s1a = rechercheSommetAvecID(g, a->s1);
    Sommet* s2a = rechercheSommetAvecID(g, a->s2);
    Arrete* arreteInverse = creerArrete(g->m+1, s2a, s1a);
    afficherArrete(arreteInverse);
    if (arreteExistante(g, arreteInverse)){
        printf("L'arrete que vous souhaitez ajouter au graphe existe deja\n");
        return;
    }
    g->m += 1;
    g->L_arretes = (Arrete**)realloc(g->L_arretes, g->m * sizeof(Arrete*));
    if (!g->L_arretes) {
        printf("Erreur : échec de la réallocation de memoire pour les arretes.\n");
        return;
    }
    g->L_arretes[g->m - 1] = a;
    ajouterVoisin(s1a, s2a);
}

void retirerArrete(Graphe* g, Arrete* a) {
    /*
     * Retirer une arête :
     * - Vérifier si elle existe dans le graphe
     * - Si c'est le cas, les deux sommets extrémités ne sont plus voisins  
     */
    if (!g || !a) {
        printf("Erreur : Le graphe ou l'arête n'existe pas !\n");
        return;
    }
    Sommet* aS1 = rechercheSommetAvecID(g, a->s1);
    Sommet* aS2 = rechercheSommetAvecID(g, a->s2);
    if (!aS1 || !aS2) {
        printf("Erreur : Sommets extrémités introuvables !\n");
        return;
    }
    // Retirer les voisins
    retirerVoisin(aS1, aS2);
    // Retrouver l'indice de l'arête
    int indiceArrete = rechercheArrete(g, a);
    if (indiceArrete == -1) {
        printf("Erreur : Arête introuvable dans le graphe !\n");
        return;
    }
    // Décaler les arêtes restantes
    for (int i = indiceArrete; i < g->m - 1; i++) {
        g->L_arretes[i] = g->L_arretes[i + 1];
    }
    g->m -= 1;
    // Réallouer la mémoire pour les arêtes
    g->L_arretes = (Arrete**)realloc(g->L_arretes, g->m * sizeof(Arrete*));
    // Libérer la mémoire de l'arête supprimée
    libererArrete(a);
}

void retirerSommet(Graphe* g, Sommet* s) {
    /*
     * Retirer un sommet :
     * - Vérifier s'il existe dans le graphe
     * - Si c'est le cas :
     *      | Tous ses voisins sont "libérés"
     *      | Toutes les arrêtes ayant s pour extrémité sont supprimées  
     */
    if (!g || !s) {
        printf("Erreur : Le graphe ou le sommet n'existe pas\n");
        return;
    }
    // Trouver l'indice du sommet dans le graphe
    int indiceSommet = rechercheSommet(g, s);
    if (indiceSommet == -1) {
        printf("Erreur : Sommet introuvable dans le graphe !\n");
        return;
    }
    //Récupère le sommet retiré puis son identifiant
    Sommet* sommetRetire = g->L_sommets[indiceSommet];
    int idSommetRetire = sommetRetire->id;
    // Supprimer toutes les arêtes liées au sommet
    int nbArrete = g->m-1;
    for (int j = nbArrete; j >= 0; j--) {
        if (g->L_arretes[j]->s1 == idSommetRetire || g->L_arretes[j]->s2 == idSommetRetire) {
            retirerArrete(g, g->L_arretes[j]);
        }
    }
    // Décaler les sommets pour supprimer celui ciblé
     /*
      * Erreur comise : Avoir supprimé le sommet en essayant ensuite de supprimer les arrêtes qui 
      * lui étaient associées.
      */
    for (int i = indiceSommet; i < g->n - 1; i++) {
        g->L_sommets[i] = g->L_sommets[i + 1];
    }
    g->n -= 1;
    // Réallouer la mémoire pour les sommets
    g->L_sommets = (Sommet**)realloc(g->L_sommets, g->n * sizeof(Sommet*));
    // Libérer la mémoire du sommet
    libererSommet(sommetRetire);
}


void afficherGraphe(Graphe* g) {
    if (!g || !g->L_sommets || g->n == 0) {
        printf("Erreur : graphe ou liste de sommets non initialisée.\n");
        return;
    }

    printf("Sommets du graphe : [\n");
    for (int i = 0; i < g->n; i++) {
        if (g->L_sommets[i]) {
            afficherSommet(g->L_sommets[i]);
        }
    }
    printf("]\n");

    printf("Arretes du graphe : [\n");
    for (int j = 0; j < g->m; j++) {
        if (g->L_arretes[j]) {
            afficherArrete(g->L_arretes[j]);
        }
    }
    printf("]\n");
}

Sommet** trierSommets(Graphe* g) {
    /*
     * Objectif de la fonction
     * - Récupérer le vecteur des sommets du graphe
     * - Ranger les sommets dans l'ordre croissant des cardinalités
     */
    
    // Allocation de mémoire pour la liste triée
    Sommet** listeSommetTriee = (Sommet**)malloc(g->n * sizeof(Sommet*));
    if (listeSommetTriee == NULL) {
        // Gestion de l'erreur d'allocation
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Copie des sommets dans la nouvelle liste
    for (int i = 0; i < g->n; i++) {
        listeSommetTriee[i] = g->L_sommets[i];
    }

    // Tri à bulles
    for (int i = 0; i < g->n - 1; i++) {
        for (int j = 0; j < g->n - i - 1; j++) {
            if (listeSommetTriee[j]->cardinalite > listeSommetTriee[j + 1]->cardinalite) {
                // Échange des sommets
                Sommet* temporaire = listeSommetTriee[j];
                listeSommetTriee[j] = listeSommetTriee[j + 1];
                listeSommetTriee[j + 1] = temporaire;
            }
        }
    }

    return listeSommetTriee;
}


void inverserLSommets(Sommet** listeSommet, int nbSommet) {
    int indiceDebut = 0;
    int indiceFin = nbSommet - 1;
    
    while (indiceDebut < indiceFin) {
        // Inversion des sommets
        Sommet* tempo = listeSommet[indiceDebut];
        listeSommet[indiceDebut] = listeSommet[indiceFin];
        listeSommet[indiceFin] = tempo;
        
        indiceDebut++;
        indiceFin--;
    }
}


void trierArretes(Graphe* g) {
    /*
     * Objectif de la fonction
     * - Récupérer le vecteur des arretes du graphe
     * - Ranger les arretes dans l'ordre croissant des poids
     * ON UTILISERA LA METHODE DU TRI PAR LE MAX (comme pour les sommets)
     *     - Recherche du max
     *     - Place à la fin du tableau
     */
    int maxIndex; 
    Arrete* temp;
    for (int i = g->m - 1; i > 0; i--) {
        // On suppose que le premier élément est le plus grand
        maxIndex = 0;
        
        // On trouve l'élément le plus grand dans le reste du tableau
        for (int j = 1; j <= i; j++) {
            if (g->L_arretes[j]->poids > g->L_arretes[maxIndex]->poids) {
                maxIndex = j;
            }
        }

        // On échange l'élément le plus grand trouvé avec l'élément en position i
        if (maxIndex != i) {
            temp = g->L_arretes[i];
            g->L_arretes[i] = g->L_arretes[maxIndex];
            g->L_arretes[maxIndex] = temp;
        }
    }
    afficherGraphe(g);
}

void algoWelshPowell(Graphe* g) {
    // Vérifier si le graphe est valide et si il a au moins un sommet
    if (g == NULL || g->n == 0) {
        return;  
    }
    Sommet** listeSommetTrie = trierSommets(g);
    inverserLSommets(listeSommetTrie, g->n); 
    int couleurMax = 0;
    for (int i = 0; i < g->n; i++) {
        Sommet* s = listeSommetTrie[i];
        if (s == NULL) continue;
        int couleur = 0;
        bool couleurValide;
        do {
            couleurValide = true;
            // Vérifier les couleurs des voisins
            for (int j = 0; j < s->cardinalite; j++) {
                if (s->voisins[j] != NULL && s->voisins[j]->color == couleur) {
                    couleurValide = false;
                    couleur++;
                    break;
                }
            }
        } while (!couleurValide);
        s->color = couleur;
        if (couleur > couleurMax) {
            couleurMax = couleur;
        }
    }
    //free(listeSommetTrie);
    printf("Nombre de couleurs utilisées pour coloré le graphe : %d\n", couleurMax + 1);
}


int algoDijkstra(Graphe* g, int origine, int destination){
    // Initialisation de la distance
    int distance = 0;
    int k = g->n;

    // Initialisation de la liste des sommets du graphe
    int* L_nonVisite = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        L_nonVisite[i] = i;
    }

    // Initialisation du sommet courant
    int idSommetCourant = origine;
    Sommet* sommetCourant = rechercheSommetAvecID(g, origine);
    g->L_sommets[origine]->pi = 0;
    g->L_sommets[origine]->parent = origine;

    while (L_nonVisite && idSommetCourant != destination) {
        // Extraire le sommet avec un pi le plus petit
        /*
         * Explication de la suite de l'algo
         * - On récupère l'indice du sommet (pas encore visité) ayant pi le plus petit
         * - On extrait le sommet[piMin] à la listeNonVisite
         * - On parcourt tous ces voisins
         *      - On récupère le poids de l'arrête (= distanceSJ) entre lui et son voisin
         *      - Si piS + distanceSJ < piJ alors 
         *          - on change piJ
         *          - Le parent de J devient le sommet courant
         * - On enlève le sommet déjà vu de ListeNonVisite
         */
        int idpiMin = -1;
        int valeurPiMin = (int)INFINITY;
        for (int i = 0; i < k; i++) {
            if (L_nonVisite[i] != -1) {
                Sommet* s = rechercheSommetAvecID(g, L_nonVisite[i]);
                if (s->pi < valeurPiMin) {
                    valeurPiMin = s->pi;
                    idpiMin = i; 
                }
            }
        }
        // Si aucun sommet non visité n'est trouvé, je dois donc sortir de la boucle
        if (idpiMin == -1) {
            break;
        }
        // Récupérer le sommet courant grâce à l'indice du sommet ayant le pi le plus petit
        idSommetCourant = L_nonVisite[idpiMin];
        sommetCourant = rechercheSommetAvecID(g, idSommetCourant);
        // On parcours tous les voisins
        for (int j = 0; j < sommetCourant->cardinalite; j++) {
            Sommet* voisin = sommetCourant->voisins[j];
            int idArrete = rechercheArrete(g, creerArrete(0, sommetCourant, voisin));
            int distanceCourantVoisinJ = g->L_arretes[idArrete]->poids;
            // On vérifie si la distance à chaque sommet est-elle à mettre à jour
            if (sommetCourant->pi + distanceCourantVoisinJ < voisin->pi) {
                voisin->pi = sommetCourant->pi + distanceCourantVoisinJ;
                voisin->parent = sommetCourant->id;
                g->L_arretes[idArrete]->color = 1; // =1 arrete coloré pour le chemin
            }
        }
        // On enlève le sommet courant de L_nonVisite
        L_nonVisite[idpiMin] = -1; // Marquer comme visité
    }
    if (g->L_sommets[destination]->pi == INT_MAX) {
        printf("Aucun chemin trouvé !\n");
        return -1;
    }
    // On retourne la distance entre les deux sommets
    return sommetCourant->pi;
}

