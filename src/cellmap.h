/*
 * cellmap.h
 *
 *  Created on: Aug 17, 2019
 *      Author: Mickey
 */

#ifndef CELLMAP_H_
#define CELLMAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Cellmap {
	  bool** map;  
    int num_points;
	  unsigned int width;
	  unsigned int height;
  
} Cellmap;

/**
 * Initializes current and next cellmaps for the game to be played.
 */
Cellmap* init_cellmap(unsigned int width, unsigned int height);

/**
 * Frees memory where cellmap exists
 */
void del_cellmap(Cellmap* cellmap);

/**
 * Turns cell on at screen position (x, y).
 */
void set_cell(Cellmap* cellmap, unsigned int x, unsigned int y);

/**
 * Turns cell off at screen position (x, y).
 */
void clear_cell(Cellmap* cellmap, unsigned int x, unsigned int y);

/**
 * Returns cell state (true = on | false = off).
 */
bool cell_state(Cellmap* cellmap, unsigned int x, unsigned int y);

/**
 * Returns the number of neighbors a specified cell has.
 */
int count_neighbors(Cellmap* cellmap, unsigned int x, unsigned int y);

/**
 * 
 */
void cellmap_next_generation(Cellmap* cellmap);

#endif /* CELLMAP_H_ */

