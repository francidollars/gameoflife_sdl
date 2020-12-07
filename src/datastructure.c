/*
 * datastructure.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#include "datastructure.h"

/**
 * Initializes chosen data structure
 * 
 * @param given_st - user declared structure type to use
 * @return initialized data structure
 */
void init_data_structure(StructureType given_st, unsigned int width, unsigned int height) {
    // TODO Implement error checking
    switch (given_st) {
        case CELLMAP:
            init_cellmap(width, height);
            break;
        default:
            break;
    }

}

/**
 * Free memory utilized by data structure (called before exiting)
 * 
 * @param st - user declared structure type to use 
 */
void del_data_structure(StructureType st) {
    switch (st) {
        case CELLMAP:
            del_cellmap();
            break;
        default:
            // TODO Implement default (uninitialized case)
            break;
   }

}

/**
 * Gets number of points in existing data_structure
 * 
 * @param st - user declared structure type to use
 * @return integer representing number of points
 */
int get_num_points(StructureType st) {
    int temp_num_points;

    switch (st) {
        case CELLMAP:
            temp_num_points = cellmap_get_num_points();
            break;
        default:
            // TODO Implement default (uninitialized case)
            temp_num_points = -1;
    }

    return temp_num_points;
}

/**
 * Function to convert next generation points to generic Point array
 * 
 * @param st - user declared structure type to use
 * @return generic Point array that can be converted to SDL_Point array for drawing
 */
Point* next_generation(StructureType st, bool calc) {
    Point* points;

    switch (st) {
        case CELLMAP : { // TODO rid of block with temp var declarations
            bool** cellmap_map = cellmap_get_map();
            unsigned int cellmap_height = cellmap_get_height();
            unsigned int cellmap_width = cellmap_get_width();
            int num_points = cellmap_get_num_points();

            points = calloc(num_points, sizeof(Point));
            int point_cnt = 0;  // TODO break when point_cnt equals number of points
            Point temp_point;

            for (unsigned int y = 0; y < cellmap_height; y++) {
                for (unsigned int x = 0; x < cellmap_width; x++) {
                    if (cell_state(cellmap_map, x, y)) {
                        temp_point.x = x;
                        temp_point.y = y;
                        *(points + point_cnt++) = temp_point;

                        if (point_cnt == num_points) {
                            y = cellmap_height;
                            break;
                        }

                    }
                }
            }

            if (calc)
                cellmap_next_generation();

        } break;
        default:
            // TODO Implement default (uninitialized case)
            break;
    }

    return points;
}

