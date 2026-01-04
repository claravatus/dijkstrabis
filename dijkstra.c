#include "dijkstra.h"
//#include "animation.h"
#include "grille.h"
#include <stdlib.h>

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
    float dist = distance_euclidienne(courant, suivant);
    float h_courant = get_hauteur(grille, courant);
    float h_suivant = get_hauteur(grille, suivant);
    float denivele = h_suivant - h_courant;
    if (denivele < 0) {
        denivele = 0;
    }   
    return dist + denivele;
}



/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */

// algo C (je voyais pas trop l'intérêt de le mettre dans le .h d'où le static)
static void construire_chemin_vers(coord_t n, coord_t source, liste_noeud_t* visites, liste_noeud_t* chemin) {
    if (!memes_coord(n, source)) {
        // (C-1) Soit n_p = prec(n)
        coord_t n_p = precedent_noeud_liste(visites, n);
        // (C-3.1) Appel récursif vers le précédent
        construire_chemin_vers(n_p, source, visites, chemin);
        // (C-3.2) Ajouter au chemin le noeud n_p
        float cout_np = cout_noeud_liste(visites, n_p);
        coord_t prec_np = precedent_noeud_liste(visites, n_p);
        inserer_noeud_liste(chemin, n_p, prec_np, cout_np);
    }
    // ig si la condition n'est pas remplie ça ne fait plus rien et algo fini 
} 

// algo D 
float dijkstra(grille_t grille, coord_t source, coord_t destination, float seuil, liste_noeud_t** chemin) {
    liste_noeud_t* a_visiter = creer_liste();
    liste_noeud_t* visites = creer_liste();
    float resultat_cout = COUT_INFINI;
    bool trouve = false;
    // (D-1) Ajouter le noeud de départ à cout 0
    inserer_noeud_liste(a_visiter, source, source, 0.0);
    // (D-2) Tant qu'il existe noeud, faire :
    while (!est_vide_liste(a_visiter) && !trouve) {
        // (D-2.1) Noeud courant n_c de coût minimal
        coord_t n_c = min_noeud_liste(a_visiter);
        float cout_nc = cout_noeud_liste(a_visiter, n_c);
        coord_t prec_nc = precedent_noeud_liste(a_visiter, n_c);
        // (D-2.2) Ajouter n_c dans Visités
        inserer_noeud_liste(visites, n_c, prec_nc, cout_nc);
        // (D-2.3) Supprimer n_c de AVisiter
        supprimer_noeud_liste(a_visiter, n_c);
        if (memes_coord(n_c, destination)) {
            resultat_cout = cout_nc;
            trouve = true; 
        } else {
            // (D-2.4) Exploration des voisins (que si on trouve le chemin du coup)
            coord_t* voisins = NULL;
            size_t nb_voisins = get_voisins(grille, n_c, seuil, &voisins);
            if (nb_voisins > 0 && voisins != NULL) { // On ne traite que s'il y a des voisins
                for (size_t i = 0; i < nb_voisins; i++) {
                    coord_t n_v = voisins[i];
                    if (!contient_noeud_liste(visites, n_v)) {
                        float delta_prime = cout_nc + cout(grille, n_c, n_v); 
                        float delta = cout_noeud_liste(a_visiter, n_v);
                        if (delta_prime < delta) {
                            inserer_noeud_liste(a_visiter, n_v, n_c, delta_prime);
                        }
                    }
                }
                free(voisins); 
                voisins = NULL;
            }
        }
    }
    if (chemin != NULL) {
        if (resultat_cout != COUT_INFINI) {
            *chemin = creer_liste();
            construire_chemin_vers(destination, source, visites, *chemin);
            inserer_noeud_liste(*chemin, destination, precedent_noeud_liste(visites, destination), resultat_cout);
        } else {
            *chemin = NULL;
        }
    }

    detruire_liste(&a_visiter);
    detruire_liste(&visites);
    return resultat_cout;
}

