#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

// pour calculer la position d'un point dans le tableau créé (grille)
static size_t coord_lin(grille_t grille, coord_t position) {
    int x = get_x(position); 
    int y = get_y(position); 
    assert(dans_les_bornes(grille, position)); // au cas où ?
    return (size_t)(y * (*grille).largeur + x);
}

grille_t creer_grille(int largeur, int profondeur) {
    grille_t grille = (grille_t)malloc(sizeof(struct grille_t));
    (*grille).largeur = largeur;
    (*grille).profondeur = profondeur;
    size_t taille = (size_t)largeur * profondeur;
    (*grille).hauteurs = (float*)calloc(taille, sizeof(float));
    return grille;
}

void detruire_grille(grille_t grille) {
    if (grille != NULL) { // donc pas vide
        free((*grille).hauteurs);
        free(grille);
    }
}

int get_largeur(grille_t grille) {
    return (*grille).largeur;
}

int get_profondeur(grille_t grille) {
    return (*grille).profondeur;
}

bool dans_les_bornes(grille_t grille, coord_t position) {
    int x = get_x(position);
    int y = get_y(position);
    bool x_ok = (x >= 0) && (x < (*grille).largeur);
    bool y_ok = (y >= 0) && (y < (*grille).profondeur);
    return x_ok && y_ok;
}

coord_t inferieur_gauche(grille_t grille) {
    (void)grille; // grille ne sert à rien ici donc on explicite qu'on l'utilise pas ???
    return creer_coord(0, 0); 
}

coord_t superieur_droit(grille_t grille) {
    return creer_coord((*grille).largeur - 1, (*grille).profondeur - 1);
}

void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    size_t index = coord_lin(grille, position);
    (*grille).hauteurs[index] = hauteur;
}

float get_hauteur(grille_t grille, coord_t position) {
    size_t index = coord_lin(grille, position);
    return (*grille).hauteurs[index];
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0}; // on cherche les directions pour chercher
    float h_centre = get_hauteur(grille, position);
    size_t nb = 0;
    coord_t temp[4]; 
    for (int i = 0; i < 4; i++) {
        coord_t v_pos = creer_coord(get_x(position) + dx[i], get_y(position) + dy[i]);
        if (dans_les_bornes(grille, v_pos)) {
            float h_voisin = get_hauteur(grille, v_pos);
            float diff = h_centre - h_voisin;
            if (diff < 0) {
                diff = -diff; // pour avoir la valeur absolue
             } 
            if (diff <= seuil) {
                temp[nb] = v_pos;
                nb++;
            }
        }
    }
    *voisins = malloc(nb * sizeof(coord_t)); // on donne de la mémoire
    if (*voisins != NULL) { 
        for (size_t i = 0; i < nb; i++) {
            (*voisins)[i] = temp[i]; // on stocke
        }
    }
    return nb;
}


