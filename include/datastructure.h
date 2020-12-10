/**
 * datastructure.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#include "cellmap.h"
//#include "twodim_tree.h" TODO Implement twodimtree functions

typedef enum {
    NONE,
    CELLMAP,
    TWODIMTREE
} StructureType;

typedef struct {
    int x;
    int y;
} Point;

/**
 * Initializes chosen data structure
 */
void init_data_structure(StructureType given_st, unsigned int width, unsigned int height);

/**
 * Free memory utilized by data structure (called before exiting)
 */
void del_data_structure(StructureType st);

/**
 * Gets number of points in existing data_structure
 */
int get_num_points(StructureType st);

/**
 * Function to convert next generation points to generic Point array
 */ 
Point* next_generation(StructureType st, bool calc);

#endif /* DATASTRUCTURE_H_ */

