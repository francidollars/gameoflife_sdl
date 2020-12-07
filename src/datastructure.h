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
    StructureType stype;
    union {
        Cellmap* cellmap;
    } data;
} DataStructure;

typedef struct {
    int x;
    int y;
} Point;

DataStructure init_data_structure(StructureType given_st, unsigned int width, unsigned int height);

int get_num_points(DataStructure ds);

Point* next_generation(DataStructure ds);

#endif /* DATASTRUCTURE_H_ */

