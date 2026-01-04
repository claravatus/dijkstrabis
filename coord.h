#ifndef COORD_H
#define COORD_H

#include <stdbool.h> 
#include <math.h>    
#include <stdio.h>   

typedef struct {
    int abscisse;
    int ordonnee;
} coord_t;

coord_t creer_coord(int abscisse, int ordonnee);

int get_x(coord_t point);

int get_y(coord_t point);

void set_x(coord_t* point, int valeur); 

void set_y(coord_t* point, int valeur); 

bool memes_coord(coord_t p1, coord_t p2);

coord_t translation(coord_t point, int dx, int dy);

float distance_euclidienne(coord_t p1, coord_t p2);

#endif // COORD_H