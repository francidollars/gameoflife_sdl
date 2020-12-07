/**
 * datastructure.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#include "datastructure.h"

/**
 * Initializes proper data structure
 * 
 * @param given_st - user declared structure type to use
 * @return initialized data structure
 */
DataStructure init_data_structure(StructureType given_st, unsigned int width, unsigned int height) {
    DataStructure data_structure;

    switch (given_st) {
        case CELLMAP :
            data_structure.stype = given_st;
            data_structure.data.cellmap = init_cellmap(width, height);
            break;
        default:
            data_structure.stype = NONE;
            break;
    }

    return data_structure;
}

int get_num_points(DataStructure ds) {
    int temp_num_points;

    switch (ds.stype) {
        case CELLMAP :
            temp_num_points = ds.data.cellmap->num_points;
            break;
        default :
            break;
    }

    return temp_num_points;
}

Point* next_generation(DataStructure ds) {
    Point* points;

    switch (ds.stype) {
        case CELLMAP :
            cellmap_next_generation(ds.data.cellmap);
            points = calloc(ds.data.cellmap->num_points, sizeof(Point));
            int point_cnt = 0;
            unsigned int x, y;
            Point temp_point;

            for (y = 0; y < ds.data.cellmap->height; y++) {
                for (x = 0; x < ds.data.cellmap->width; x++) {
                    if (cell_state(ds.data.cellmap, x, y)) {
                        temp_point.x = x;
                        temp_point.y = y;
                        *(points + point_cnt++) = temp_point; 
                    }
                }
            }
            break;
        default :
            break;
    }

    return points;
}

