/**
 * ds_twodim_boolarr.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Mickey
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ds_twodim_boolarr.h"

static void twodim_boolarr_init(struct DS_TwoDim_BoolArr*, bool**, int, unsigned int, unsigned int);
static bool get_cell_state(struct DS_TwoDim_BoolArr*, int, int);
static void set_cell_state(struct DS_TwoDim_BoolArr*, unsigned int, unsigned int, bool);
static int count_neighbors(struct DS_TwoDim_BoolArr*, int, int);

static struct DS_TwoDim_BoolArr* twodim_boolarr_ctor(va_list* app) {
    struct DS_TwoDim_BoolArr* ds_tdba = (struct DS_TwoDim_BoolArr*) malloc(sizeof(struct DS_TwoDim_BoolArr));

    // TODO: va_list error checking (or maybe in datastruct.c)
    unsigned int init_num_cols = (unsigned int) va_arg(*app, int);
    unsigned int init_num_rows = (unsigned int) va_arg(*app, int);
    int init_num_points; // TODO: Testing

    bool** cell_arr = calloc(init_num_rows, sizeof(bool**)); //TODO: Formalize 'cell_arr' term
	for (int row_index = 0; row_index < (int) init_num_rows; row_index++)
		*(cell_arr + row_index) = calloc(init_num_cols, sizeof(bool*));

    // TODO: TESTING
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 4) = true;
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 4) = true;
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 3) = true;
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 3) = true;
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 2) = true;
    // *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 2) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 1) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 1) = true;
    *(*(cell_arr + init_num_rows / 2) + init_num_cols / 2) = true;
    init_num_points = 3;

    twodim_boolarr_init(ds_tdba, cell_arr, init_num_points /* Should be 0 */, init_num_rows, init_num_cols);

    return ds_tdba;
}

static void twodim_boolarr_dtor(struct DS_TwoDim_BoolArr* ds_tdba) {
    // Deallocate bool arr
    for (int row_index = 0; row_index < (int) ds_tdba->num_rows; row_index++)
        free(*(ds_tdba->arr + row_index));

    free(ds_tdba->arr);
    // Deallocate datastruct
    free(ds_tdba);

}

static int twodim_boolarr_get_numpoints(struct DS_TwoDim_BoolArr* ds_tdba) {

    return ds_tdba->num_points;
}

static void twodim_boolarr_getpoints(struct DS_TwoDim_BoolArr* ds_tdba, int* x_index, int* y_index) {
    // TODO: Clean up these loops
    for (; *y_index < ds_tdba->num_rows; (*y_index)++) {
        for (*(x_index) = (*x_index % ds_tdba->num_cols); *x_index < ds_tdba->num_cols; (*x_index)++) {
            if (get_cell_state(ds_tdba, *x_index, *y_index)) {

                return;
            }
        }
    }
}

static struct DS_TwoDim_BoolArr* twodim_boolarr_get_cpydatastruct(struct DS_TwoDim_BoolArr* ds_tdba) {
    struct DS_TwoDim_BoolArr* temp_ds = (struct DS_TwoDim_BoolArr*) malloc(sizeof(struct DS_TwoDim_BoolArr));

	bool** old_arr = calloc(ds_tdba->num_rows, sizeof(bool**));
	for (int row_index = 0; row_index < (int) ds_tdba->num_rows; row_index++) {
        *(old_arr + row_index) = calloc(ds_tdba->num_cols, sizeof(bool*));

        for (int col_index = 0; col_index < (int) ds_tdba->num_cols; col_index++)
		    *(*(old_arr + row_index) + col_index) = get_cell_state(ds_tdba, col_index, row_index);

    }

    twodim_boolarr_init(temp_ds, old_arr, ds_tdba->num_points, ds_tdba->num_rows, ds_tdba->num_cols);

    return temp_ds;
}

static void twodim_boolarr_nextgen(struct DS_TwoDim_BoolArr* ds_tdba) {
    struct DS_TwoDim_BoolArr* temp_ds = (struct DS_TwoDim_BoolArr*) malloc(sizeof(struct DS_TwoDim_BoolArr));
    twodim_boolarr_init(temp_ds, twodim_boolarr_get_cpydata(ds_tdba), ds_tdba->num_points, ds_tdba->num_rows, ds_tdba->num_cols);

    int x = 0, y = 0;
    int modi_x, modi_y;
    int neighbor_count;
    for (int index = 0; index < temp_ds->num_points; index++) {
        twodim_boolarr_getpoints(temp_ds, &x, &y);
        for (int row_index_modifier = -1; row_index_modifier <= 1; row_index_modifier++) {
            for (int col_index_modifier = -1; col_index_modifier <= 1; col_index_modifier++) {
                modi_x = x + col_index_modifier;
                modi_y = y + row_index_modifier;
                neighbor_count = count_neighbors(temp_ds, modi_x, modi_y);

                if (get_cell_state(temp_ds, modi_x, modi_y)) {
                    if ((neighbor_count != 2) && (neighbor_count != 3))
                        set_cell_state(ds_tdba, modi_x, modi_y, false);

                } else {
                    if (neighbor_count == 3)
                        set_cell_state(ds_tdba, modi_x, modi_y, true);

                }
            }
        }
    }

}

/* static void twodim_boolarr_nextgen(struct DS_TwoDim_BoolArr* ds_tdba) {
    struct DS_TwoDim_BoolArr* temp_ds = (struct DS_TwoDim_BoolArr*) malloc(sizeof(struct DS_TwoDim_BoolArr));
    // TODO: Could be possible to only get check live points / we need to check neighbors of live points
    twodim_boolarr_init(temp_ds, twodim_boolarr_get_cpydata(ds_tdba), ds_tdba->num_points, ds_tdba->num_rows, ds_tdba->num_cols);

    int neighbor_count;
    for (int index_y = 0; index_y < (int) temp_ds->num_rows; index_y++) {
        for (int index_x = 0; index_x < (int) temp_ds->num_cols; index_x++) {
            neighbor_count = count_neighbors(temp_ds, index_x, index_y);

            if (get_cell_state(temp_ds, index_x, index_y)) {
                if ((neighbor_count != 2) && (neighbor_count != 3))
                    set_cell_state(ds_tdba, index_x, index_y, false);

            } else {
                if (neighbor_count == 3)
                    set_cell_state(ds_tdba, index_x, index_y, true);

            }
        }
    }

    twodim_boolarr_dtor(temp_ds);

} */

const struct datastruct_vtable_* DS_TDBA = &(struct datastruct_vtable_) {
    .ds_ctor = (void*) (struct DS_TwoDim_BoolArr* (*)(va_list*)) twodim_boolarr_ctor,
    .ds_dtor = (void (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_dtor,
    .ds_get_numpoints = (int (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_get_numpoints,
    .ds_getpoints = (void (*)(struct DS_TwoDim_BoolArr*, int*, int*)) twodim_boolarr_getpoints,
    .ds_get_cpydatastruct = (void*) (struct DS_TwoDim_BoolArr* (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_get_cpydatastruct
    // .ds_nextgen = (void (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_nextgen
};

static void twodim_boolarr_init(struct DS_TwoDim_BoolArr* ds, bool** _arr, int _num_points, unsigned int _num_rows, unsigned int _num_cols) {
    ds->arr = _arr;
    ds->num_points = _num_points;
    ds->num_rows = _num_rows;
    ds->num_cols = _num_cols;

}

static bool get_cell_state(struct DS_TwoDim_BoolArr* ds_tdba, int cell_index_x, int cell_index_y) {
    // TODO: Error checking (out of bounds stuff)

    int w = (int) ds_tdba->num_cols;
    int h = (int) ds_tdba->num_rows;
    int temp_x = ((cell_index_x + w) % w);
    int temp_y = ((cell_index_y + h) % h);

    return *(*(ds_tdba->arr + temp_y) + temp_x); // Does wrapping
}

static void set_cell_state(struct DS_TwoDim_BoolArr* ds, unsigned int cell_index_x, unsigned int cell_index_y, bool state) {
    // TODO: Error checking (out of bounds stuff)

	if (*(*(ds->arr + cell_index_y) + cell_index_x) = state) {
        ds->num_points++;
    } else {
        ds->num_points--;
    }

}

static int count_neighbors(struct DS_TwoDim_BoolArr* ds_tdba, int x, int y) {
    // TODO: Error checking (out of bounds stuff)

	int neighbor_count = 0;

    for (int rows_index = -1; rows_index <= 1; rows_index++)
        for (int cols_index = -1; cols_index <= 1; cols_index++)
            if ((rows_index || cols_index) && get_cell_state(ds_tdba, (x + cols_index), (y + rows_index)))
                neighbor_count++;

	return neighbor_count;
}
