#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

cellule_t* chercher_cellule(const liste_noeud_t* liste, coord_t noeud) {
    cellule_t* trouve = NULL; 
    if (liste != NULL) {
        cellule_t* courante = (*liste).tete;
        while (courante != NULL && trouve == NULL) {
            if (memes_coord((*courante).noeud, noeud)) {
                trouve = courante; 
            } else {
                courante = (*courante).suivant; 
            }
        }
    }
    return trouve;
}


liste_noeud_t* creer_liste() {
    liste_noeud_t* liste = malloc(sizeof(liste_noeud_t)); // on donne de la place en mémoire
    if (liste != NULL) {
        (*liste).tete = NULL;
    }
    return liste;
}


void detruire_liste(liste_noeud_t** liste_ptr) {
    if (liste_ptr == NULL || *liste_ptr == NULL) return;
    cellule_t* courante = (**liste_ptr).tete;
    while (courante != NULL) {
        cellule_t* a_supprimer = courante;
        courante = (*courante).suivant;
        free(a_supprimer);
    }
    free(*liste_ptr);
    *liste_ptr = NULL;
}

bool est_vide_liste(const liste_noeud_t* liste) {
    bool resultat = false;
    if (liste == NULL || (*liste).tete == NULL) {
        resultat = true;
    }
    return resultat;
}

bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    return chercher_cellule(liste, noeud) != NULL;
}

bool contient_arrete_liste(const liste_noeud_t* liste, coord_t source, coord_t destination) {
    cellule_t* cell_dest = chercher_cellule(liste, destination);
    if (cell_dest != NULL) {
        return memes_coord(cell_dest->precedent, source);
    }
    return false;
}

float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    float resultat = COUT_INFINI; // initialisation 
    cellule_t* cellule = chercher_cellule(liste, noeud);
    if (cellule != NULL) {
        resultat = (*cellule).cout;
    }
    return resultat ;
}


coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    coord_t resultat = INVALIDE;
    cellule_t* cellule = chercher_cellule(liste, noeud);
    if (cellule != NULL) {
        resultat = (*cellule).precedent;
    }
    return resultat;
}

coord_t min_noeud_liste(const liste_noeud_t* liste) {
    coord_t resultat = INVALIDE;
    if (liste != NULL && (*liste).tete != NULL) {
        cellule_t* courante = (*liste).tete;
        cellule_t* cellule_min = (*liste).tete;
        while (courante != NULL) {
            if ((*courante).cout < (*cellule_min).cout) {
                cellule_min = courante; 
            }
            courante = (*courante).suivant;
        }
        resultat = (*cellule_min).noeud;
    }
    return resultat; 
}

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, coord_t precedent, float cout) {
    if (liste != NULL) { // est-ce que le noeud existe 
        cellule_t* cellule = chercher_cellule(liste, noeud);
        if (cellule != NULL) { // le point existe déjà donc on modif juste ce qu'on veut 
            (*cellule).cout = cout;
            (*cellule).precedent = precedent;
        } 
        else { // le point est nouveau : on le rajoute 
            cellule_t* nouvelle = malloc(sizeof(*nouvelle));
            if (nouvelle != NULL) {
                (*nouvelle).noeud = noeud;
                (*nouvelle).cout = cout;
                (*nouvelle).precedent = precedent;
                (*nouvelle).suivant = (*liste).tete;
                (*liste).tete = nouvelle;
            }
        }
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud) {
    if (liste != NULL && (*liste).tete != NULL) {
        cellule_t* courante = (*liste).tete;
        cellule_t* precedente = NULL;
        cellule_t* a_supprimer = NULL;
        while (courante != NULL && a_supprimer == NULL) {
            if (memes_coord((*courante).noeud, noeud)) {
                a_supprimer = courante; // ig on a trouvé ici
            } else {
                precedente = courante; 
                courante = (*courante).suivant;
            }
        }
        if (a_supprimer != NULL) {
            if (precedente == NULL) {
                (*liste).tete = (*a_supprimer).suivant;
            } else {
                (*precedente).suivant = (*a_supprimer).suivant;
            }
            free(a_supprimer); 
        }
    }
}




