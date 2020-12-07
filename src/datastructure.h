/**
 * datastructure.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#include "cellmap.h"
#include "twodim_tree.h"

typedef enum {
    NONE,
    CELLMAP,
    TWODIMTREE
} StructureType;

typedef struct {
    int x;
    int y;
} Point;

void init_data_structure(StructureType given_st, unsigned int width, unsigned int height);

int get_num_points(StructureType st);

Point* next_generation(StructureType st);

#endif /* DATASTRUCTURE_H_ */

