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
void init_data_structure(StructureType given_st, unsigned int width, unsigned int height) {

    switch (given_st) {
        case CELLMAP:
            init_cellmap(width, height);
            break;
        default:
            break;
    }

}

int get_num_points(StructureType st) {
    int temp_num_points;

    switch (st) {
        case CELLMAP:
            temp_num_points = cellmap_get_num_points();
            break;
        default:
            temp_num_points = -1;
    }

    return temp_num_points;
}

Point* next_generation(StructureType st) {
    Point* points;

    switch (st) {
        case CELLMAP : { // TODO rid of block with temp var declarations
            bool** cellmap_map = cellmap_get_map();
            unsigned int cellmap_height = cellmap_get_height();
            unsigned int cellmap_width = cellmap_get_width();
            int num_points = cellmap_get_num_points();

            points = calloc(num_points, sizeof(Point));
            int point_cnt = 0;
            Point temp_point = { -1 , -1 };

            for (unsigned int y = 0; y < cellmap_height; y++) {
                for (unsigned int x = 0; x < cellmap_width; x++) {
                    if (cell_state(cellmap_map, x, y)) {
                        temp_point.x = x;
                        temp_point.y = y;
                        *(points + point_cnt++) = temp_point; 
                    }
                }
            }

            cellmap_next_generation();
        } break;
        default :
            break;
    }

    return points;
}

