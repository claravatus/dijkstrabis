#include "coord.h"
#include <math.h>
#include <stdlib.h> 


coord_t creer_coord(int x, int y) {
    coord_t nouvelle_coord;
    nouvelle_coord.x = x;
    nouvelle_coord.y = y;
    return nouvelle_coord;
}

int get_x(coord_t point){
    return point.x;
}

int get_y(coord_t point){
    return point.y;
}

void set_x(coord_t* point, int valeur){ 
    (*point).x = valeur;
}

void set_y(coord_t* point, int valeur){ 
    (*point).y = valeur;
}

bool memes_coord(coord_t p1, coord_t p2){
    return (p1.x == p2.x) && (p1.y == p2.y);
}

coord_t translation(coord_t point, int dx, int dy){
    return creer_coord(point.x + dx, point.y + dy);
}


float distance_euclidienne(coord_t p1, coord_t p2){
    float dx = (float)(p1.x - p2.x);
    float dy = (float)(p1.y - p2.y);
    return sqrt( pow(dx, 2) + pow(dy, 2) );
}
