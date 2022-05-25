/**
 * main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mickey
 */

#include <stdio.h>
#include <stdlib.h>
#include "sdl_funcs.h"
#include "DataStruct/datastruct.h"
#include "ds_headers.h"

// SDL_Point* ds_nextgen(struct DataStruct*, int*, int, int);
void ds_nextgen(SDL_SysMgr, struct DataStruct*, int, int);
int count_neighbors(struct DataStruct*, int, int);

// TODO: Figure how to check if structure is available, through DS_Map or preprocessor stuff
// TODO: Figure how to pass user input as parameters for ds_create()
// TODO: Figure how to dynamically create header file for libraries wanted to be included
// TODO: Figure how to build and link libraries correctly

int main(int argc, char* args[]) {
    int num_cols = 640;
    int num_rows = 480;

    SDL_SysMgr sdlmgr = init_sdl(640, 480);
    struct DataStruct* ds = ds_create(DS_TDBA, num_cols, num_rows);
    int num_points = 10;

    while (input_handler(&sdlmgr, NULL, NULL) >= 0) {
        // prepare_scene(sdlmgr, ds_nextgen(ds, &num_points, num_cols, num_rows), num_points);
        prepare_scene(sdlmgr);
        ds_nextgen(sdlmgr, ds, num_cols, num_rows);
        present_scene(sdlmgr);

        // TODO Implement user-set refresh rate (restricted by monitor refresh rate)
        SDL_Delay(100);
    }

    ds_delete(ds);
    FC_FreeFont(sdlmgr.font);   // TODO: Combine these functions into
    SDL_Quit();                 //      one function in sdl_funcs.h

    return 0;
}

void ds_nextgen(SDL_SysMgr sdl_mgr, struct DataStruct* ds, int _num_cols, int _num_rows) {
    struct DataStruct* temp_ds = ds_get_cpydata(ds);

    int neighbor_count;
    int point_cnt = 0;
    for (int cols_index = 0; cols_index < (int) _num_cols; cols_index++) {
        for (int rows_index = 0; rows_index < (int) _num_rows; rows_index++) {
            neighbor_count = count_neighbors(temp_ds, cols_index, rows_index);

            if (ds_get_element(temp_ds, cols_index, rows_index)) {
                if ((neighbor_count != 2) && (neighbor_count != 3)) {
                    ds_rem_element(ds, cols_index, rows_index);
                }

                draw_point_scene(sdl_mgr, cols_index, rows_index);

            } else {
                if (neighbor_count == 3) {
                    ds_add_element(ds, cols_index, rows_index);
                }

            }
        }
    }

    ds_delete(temp_ds);

}

/* void ds_nextgen(struct DataStruct* ds, int* _num_points, int _num_cols, int _num_rows) {
    struct DataStruct* temp_ds = ds_get_cpydata(ds);
    SDL_Point* point_arr = calloc(*(_num_points), sizeof(SDL_Point));

    int neighbor_count;
    int point_cnt = 0;
    for (int cols_index = 0; cols_index < (int) _num_cols; cols_index++) {
        for (int rows_index = 0; rows_index < (int) _num_rows; rows_index++) {
            neighbor_count = count_neighbors(temp_ds, cols_index, rows_index);

            if (ds_get_element(temp_ds, cols_index, rows_index)) {
                if ((neighbor_count != 2) && (neighbor_count != 3)) {
                    ds_rem_element(ds, cols_index, rows_index);
                    (*_num_points)--;
                }

                *(point_arr + point_cnt++) = (SDL_Point) { .x = cols_index , .y = rows_index };

            } else {
                if (neighbor_count == 3) {
                    ds_add_element(ds, cols_index, rows_index);
                    (*_num_points)++;
                }

            }
        }
    }

    ds_delete(temp_ds);

    return point_arr;
} */

int count_neighbors(struct DataStruct* ds, int _col_index, int _row_index) {
	int neighbor_count = 0;

    // TODO: Add wrapping checks here
    for (int rows_index = -1; rows_index <= 1; rows_index++)
        for (int cols_index = -1; cols_index <= 1; cols_index++)
            if ((rows_index || cols_index) && ds_get_element(ds, (_col_index + cols_index), (_row_index + rows_index)))
                neighbor_count++;

	return neighbor_count;
}

// int main (int argc, char* args[]) {
//
//     DataStruct* ds = init_ds(twodim_boolarr_init(640, 480), TwoDim_BoolArr_as_DataStruct);
//
//     SDL_SysMgr sdlmgr = init_sdl(640, 480);
//     int event_status;
//     int x, y;
//
//     while ((event_status = input_handler(&sdlmgr, &x, &y)) != 1) {
//         if (event_status == 2)
//             set_cell(x, y);
//
//         prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype, false), get_num_points(stype));
//         present_scene(sdlmgr.renderer);
//
//         SDL_Delay(10);
//     }
//
//     while (input_handler(&sdlmgr, NULL, NULL) > 0) {
//         prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype, true), get_num_points(stype));
//         present_scene(sdlmgr.renderer);
//
//         // TODO Implement user-set refresh rate (restricted by monitor refresh rate)
//         SDL_Delay(100);
// 	}
//
//     ds_del(ds);
//     FC_FreeFont(sdlmgr.font);
//     SDL_Quit();
//
//     return 0;
// }

/* void get_points_rec(Node* node, SDL_Point* points, int* index) {
    if (node == NULL)
        return;

    points[*index].x = node->point[0];
    points[*index].y = node->point[1];
    ++*index;

    if (node->right != NULL)
        get_points_rec(node->right, points, index);
    if (node->left != NULL)
        get_points_rec(node->left, points, index);
}

// Wrapper function for get_points_rec
int get_points(Node* node, SDL_Point* points) {
    int index = 0;

    get_points_rec(node, points, &index);

    return index;
}
*/
