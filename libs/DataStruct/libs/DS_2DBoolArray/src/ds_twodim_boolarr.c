/**
 * ds_twodim_boolarr.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Mickey
 */

#include <stdlib.h>
#include <stdbool.h>
#include "DS_2DBoolArray/ds_twodim_boolarr.h"

struct DS_TwoDim_BoolArr {
	bool** arr;
	unsigned int num_cols, num_rows;
};

static void twodim_boolarr_init(struct DS_TwoDim_BoolArr*, bool**, unsigned int, unsigned int);

static struct DS_TwoDim_BoolArr* twodim_boolarr_ctor(va_list* app) {
    struct DS_TwoDim_BoolArr* ds_tdba = malloc(sizeof(struct DS_TwoDim_BoolArr));

    // TODO: va_list error checking (or maybe in datastruct.c)
    unsigned int init_num_cols = (unsigned int) va_arg(*app, int);
    unsigned int init_num_rows = (unsigned int) va_arg(*app, int);


    bool** cell_arr = calloc(init_num_rows, sizeof(bool*)); //TODO: Formalize 'cell_arr' term
    for (int row_index = 0; row_index < (int) init_num_rows; row_index++)
    	*(cell_arr + row_index) = calloc(init_num_cols, sizeof(bool));

    // TODO: TESTING
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 4) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 4) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 3) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 3) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 2) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 2) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) - 1) = true;
    *(*(cell_arr + init_num_rows / 2) + (init_num_cols / 2) + 1) = true;
    *(*(cell_arr + init_num_rows / 2) + init_num_cols / 2) = true;
    *(*(cell_arr + 0) + 0) = true;

    twodim_boolarr_init(ds_tdba, cell_arr, init_num_rows, init_num_cols);

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

static struct DS_TwoDim_BoolArr* twodim_boolarr_get_cpydatastruct(struct DS_TwoDim_BoolArr* ds_tdba) {
    struct DS_TwoDim_BoolArr* temp_ds = malloc(sizeof(struct DS_TwoDim_BoolArr));

	bool** old_arr = calloc(ds_tdba->num_rows, sizeof(bool*));
	for (int row_index = 0; row_index < (int) ds_tdba->num_rows; row_index++) {
        *(old_arr + row_index) = calloc(ds_tdba->num_cols, sizeof(bool));

        for (int col_index = 0; col_index < (int) ds_tdba->num_cols; col_index++)
		    *(*(old_arr + row_index) + col_index) = *(*(ds_tdba->arr + row_index) + col_index);

    }

    twodim_boolarr_init(temp_ds, old_arr, ds_tdba->num_rows, ds_tdba->num_cols);

    return temp_ds;
}

static bool twodim_boolarr_get_cell_state(struct DS_TwoDim_BoolArr* ds_tdba, va_list* app) {
    // TODO: REMOVE should be handled somewhere else
    int w = (int) ds_tdba->num_cols;
    int h = (int) ds_tdba->num_rows;
    int temp_x = ((va_arg(*app, int) + w) % w);
    int temp_y = ((va_arg(*app, int) + h) % h);

    return *(*(ds_tdba->arr + temp_y) + temp_x); // Does wrapping
}

static void twodim_boolarr_add_cell_state(struct DS_TwoDim_BoolArr* ds_tdba, va_list* app) {
    int w = (int) ds_tdba->num_cols;
    int h = (int) ds_tdba->num_rows;
    int temp_x = ((va_arg(*app, int) + w) % w);
    int temp_y = ((va_arg(*app, int) + h) % h);

    *(*(ds_tdba->arr + temp_y) + temp_x) = true; // Does wrapping

}

static void twodim_boolarr_rem_cell_state(struct DS_TwoDim_BoolArr* ds_tdba, va_list* app) {
    int w = (int) ds_tdba->num_cols;
    int h = (int) ds_tdba->num_rows;
    int temp_x = ((va_arg(*app, int) + w) % w);
    int temp_y = ((va_arg(*app, int) + h) % h);

    *(*(ds_tdba->arr + temp_y) + temp_x) = false; // Does wrapping

}

/* static const struct datastruct_vtable_ _ds_tdba = {
    twodim_boolarr_ctor,
    twodim_boolarr_dtor,
    twodim_boolarr_get_cpydatastruct,
    twodim_boolarr_get_cell_state,
    twodim_boolarr_add_cell_state,
    twodim_boolarr_rem_cell_state
};

const struct datastruct_vtable_* DS_TDBA = &_ds_tdba; */

const struct datastruct_vtable_* DS_TDBA = &(struct datastruct_vtable_) {
    .ds_ctor = (struct DS_TwoDim_BoolArr* (*)(va_list*)) twodim_boolarr_ctor,
    .ds_dtor = (void (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_dtor,
    .ds_get_cpydata = (struct DS_TwoDim_BoolArr* (*)(struct DS_TwoDim_BoolArr*)) twodim_boolarr_get_cpydatastruct,
    .ds_get_element = (void*) (bool (*)(struct DS_TwoDim_BoolArr*, va_list*)) twodim_boolarr_get_cell_state,
    .ds_add_element = (void (*)(struct DS_TwoDim_BoolArr*, va_list*)) twodim_boolarr_add_cell_state,
    .ds_rem_element = (void (*)(struct DS_TwoDim_BoolArr*, va_list*)) twodim_boolarr_rem_cell_state
};

static void twodim_boolarr_init(struct DS_TwoDim_BoolArr* ds, bool** _arr, unsigned int _num_rows, unsigned int _num_cols) {
    ds->arr = _arr;
    ds->num_rows = _num_rows;
    ds->num_cols = _num_cols;

}

/* static void twodim_boolarr_nextgen(struct DS_TwoDim_BoolArr* ds_tdba) {
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

} */

/* static int count_neighbors(struct DS_TwoDim_BoolArr* ds_tdba, int x, int y) {
    // TODO: Error checking (out of bounds stuff)

	int neighbor_count = 0;

    for (int rows_index = -1; rows_index <= 1; rows_index++)
        for (int cols_index = -1; cols_index <= 1; cols_index++)
            if ((rows_index || cols_index) && get_cell_state(ds_tdba, (x + cols_index), (y + rows_index)))
                neighbor_count++;

	return neighbor_count;
} */
