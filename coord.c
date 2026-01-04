#include "coord.h"
#include <math.h>
#include <stdlib.h> 


coord_t creer_coord(int abscisse, int ordonnee) {
    coord_t nouvelle_coord;
    nouvelle_coord.abscisse = abscisse;
    nouvelle_coord.ordonnee = ordonnee;
    return nouvelle_coord;
}

int get_x(coord_t point){
    return point.abscisse;
}

int get_y(coord_t point){
    return point.ordonnee;
}

void set_x(coord_t* point, int valeur){ 
    (*point).abscisse = valeur;
}

void set_y(coord_t* point, int valeur){ 
    (*point).ordonnee = valeur;
}

bool memes_coord(coord_t p1, coord_t p2){
    return (p1.abscisse == p2.abscisse) && (p1.ordonnee == p2.ordonnee);
}

coord_t translation(coord_t point, int dx, int dy){
    return creer_coord(point.abscisse + dx, point.ordonnee + dy);
}


float distance_euclidienne(coord_t p1, coord_t p2){
    float dx = (float)(p1.abscisse - p2.abscisse);
    float dy = (float)(p1.ordonnee - p2.ordonnee);
    return sqrt( pow(dx, 2) + pow(dy, 2) );
}
