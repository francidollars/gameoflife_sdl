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
void init_cellmap(unsigned int width, unsigned int height);

/**
 * Frees memory where cellmap exists
 */
void del_cellmap(void);

/**
 * Turns cell on at screen position (x, y).
 */
void set_cell(unsigned int x, unsigned int y);

/**
 * Turns cell off at screen position (x, y).
 */
void clear_cell(unsigned int x, unsigned int y);

int cellmap_get_num_points(void);

bool** cellmap_get_map(void);

unsigned int cellmap_get_width(void);
  
unsigned int cellmap_get_height(void);

/**
 * Returns cell state (true = on | false = off).
 */
bool cell_state(bool** map, unsigned int x, unsigned int y);

/**
 * Returns the number of neighbors a specified cell has.
 */
int count_neighbors(bool** map, unsigned int x, unsigned int y);

/**
 * 
 */
void cellmap_next_generation(void);

#endif /* CELLMAP_H_ */

