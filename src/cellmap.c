/*
 * cellmap.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Mickey
 */

#include "cellmap.h"

bool** cpy_map(Cellmap* cellmap);

Cellmap* init_cellmap(unsigned int width, unsigned int height) {
    // Allocate memory for cellmap
	Cellmap* cellmap = malloc(sizeof(Cellmap*));
    
    // Set width and height variables
	cellmap->width = width;
	cellmap->height = height;
    
    // Allocate map (bool**) according to given dimensions (width, height)
	cellmap->map = calloc(height, sizeof(bool*));
	for (unsigned int h_index = 0; h_index < cellmap->height; h_index++)
		*(cellmap->map + h_index) = calloc(cellmap->width, sizeof(bool));

    cellmap->num_points = 0;
    
    return cellmap;
}

void del_cellmap(Cellmap* cellmap) {
    for (int deallo_cnt = 0; deallo_cnt < (int) cellmap->height; deallo_cnt++)
        free(*(cellmap->map + deallo_cnt)); 
    
    // Deallocate the memory in cellmap
    free(cellmap);

}

void set_cell(Cellmap* cellmap, unsigned int x, unsigned int y) {
	if (cellmap->width <= x) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to SET_CELL out of bounds|x-range: %u >= %u\n", x, cellmap->width);
        
        return;
	} else if (cellmap->height <= y) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to SET_CELL out of bounds|y-range: %u >= %u\n", y, cellmap->height);
        
        return;
	}
    
    cellmap->num_points++;
	*(*(cellmap->map + y) + x) = true;
    
}

void clear_cell(Cellmap* cellmap, unsigned int x, unsigned int y) {
    if (cellmap->num_points < 1) {
        
        return;
    } else if (cellmap->width <= x) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to CLEAR_CELL out of bounds|x-range: %u >= %u\n", x, cellmap->width);
        
        return;
	} else if (cellmap->height <= y) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to CLEAR_CELL out of bounds|y-range: %u >= %u\n", y, cellmap->height);
        
        return;
	}

    cellmap->num_points--;
	*(*(cellmap->map + y) + x) = false;

}

bool cell_state(Cellmap* cellmap, unsigned int x, unsigned int y) {
	if (cellmap->width <= x) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to CELL_STATE out of bounds|x-range: %u >= %u\n", x, cellmap->width);
        
		return false;
    } else if (cellmap->height <= y) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to CELL_STATE out of bounds|y-range: %u >= %u\n", y, cellmap->height);
        
        return false;
	}

	return *(*(cellmap->map + y) + x);
}

bool** cpy_map(Cellmap* cellmap) {
	bool** old_map = calloc(cellmap->height, sizeof(bool*));
	for (unsigned int h_index = 0; h_index < cellmap->height; h_index++)
		memcpy(*(old_map + h_index), *(cellmap->map + h_index), (unsigned long) cellmap->width * sizeof(bool));
    
    return old_map;
}

// TODO Implement wrapping
int count_neighbors(Cellmap* cellmap, unsigned int x, unsigned int y) {
    if (cellmap->num_points <= 1) {
        
        return 0;
    } else if (cellmap->width <= x) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to COUNT_NEIGHBORS out of bounds|x-range: %u >= %u\n", x, cellmap->width);
        
        return -1;
	} else if (cellmap->height <= y) {
		// Print statement for Debugging (will get rid of in time)
		printf("WARNING:Call to COUNT_NEIGHBORS out of bounds|y-range: %u >= %u\n", y, cellmap->height);
        
        return -1;
	}

	int neighbor_count = cell_state(cellmap, x - 1, y - 1) + cell_state(cellmap, x, y - 1)
      + cell_state(cellmap, x + 1, y - 1) + cell_state(cellmap, x - 1, y) + cell_state(cellmap, x + 1, y)
      + cell_state(cellmap, x - 1, y + 1) + cell_state(cellmap, x, y + 1) + cell_state(cellmap, x + 1, y + 1);

	return neighbor_count;
}

// TODO Implement wrapping
void cellmap_next_generation(Cellmap* cellmap) {
    int neighbor_count;
    unsigned int x, y;
    
    Cellmap* temp_cellmap;
    temp_cellmap->map
    
    for (y = 0; y < cellmap->height; y++) {
        for (x = 0; x < cellmap->width; x++) {
            neighbor_count = count_neighbors(old_map, x, y);
            
            if (cell_state(cellmap, x, y)) {
                if ((neighbor_count != 2) && (neighbor_count != 3))
                    clear_cell(cellmap, x, y);
                
            } else {
                if (neighbor_count == 3)
                    set_cell(cellmap, x, y);
                    
            }
        }
    }

}

