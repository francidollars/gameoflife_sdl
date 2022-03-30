/**
 * datastruct.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#include "datastruct.h"

static void ds_getpoints(struct DataStruct*, int*, int*);
// static void* ds_get_cpydata(struct DataStruct*);
// static void ds_nextgen(struct DataStruct*, void*, int*, int*);

struct DataStruct* ds_create(const struct datastruct_vtable_* _ds_vtable, ...) {
    struct DataStruct* ds = (struct DataStruct*) malloc(sizeof(struct DataStruct));
    ds->ds_vtable = _ds_vtable;

    assert(ds->ds_vtable);
    if (ds->ds_vtable->ds_ctor) {
        va_list a_list;

        va_start(a_list, _ds_vtable);
        ds->ds_instance = (_ds_vtable->ds_ctor)(&a_list);
        va_end(a_list);
    }

    return ds;
}

void ds_delete(struct DataStruct* ds) {
    if (ds && ds->ds_vtable->ds_dtor)
        (ds->ds_vtable->ds_dtor)(ds->ds_instance);

    free(ds);

}

int ds_get_numpoints(struct DataStruct* ds) {

    return (ds->ds_vtable->ds_get_numpoints)(ds->ds_instance);
}

SDL_Point* ds_get_sdlpoints(struct DataStruct* ds) {
    int num_points = (ds->ds_vtable->ds_get_numpoints)(ds->ds_instance);
    SDL_Point* point_arr = (SDL_Point*) calloc(num_points, sizeof(SDL_Point)); // TODO: Figure where this memory can be freed

    int x = 0, y = 0;
    for (int point_index = 0; point_index < num_points; point_index++) {
        ds_getpoints(ds, &x, &y);
        *(point_arr + point_index) = (SDL_Point) { .x = x , .y = y };
        x++;
    }

    return point_arr;
}

void ds_nextgen(struct DataStruct* ds) {
    (ds->ds_vtable->ds_nextgen)(ds->ds_instance);

}

static void ds_getpoints(struct DataStruct* ds, int* x_index, int* y_index) {
    (ds->ds_vtable->ds_getpoints)(ds->ds_instance, x_index, y_index);

}

/*
SDL_Point* ds_nextgen_getpoints(struct DataStruct* ds) {
    int num_points = (ds->ds_vtable->ds_get_numpoints)(ds->ds_instance);
    SDL_Point* point_arr = (SDL_Point*) calloc(num_points, sizeof(SDL_Point));

    void* ds_data = (ds->ds_vtable->ds_get_cpydata)(ds->ds_instance);

    int x = 0, y = 0;
    for (int point_index = 0; point_index < num_points; point_index++) {
        (ds->ds_vtable->ds_nextgen)(ds->ds_instance, ds_data, &x, &y);
        *(point_arr + point_index) = (SDL_Point) { .x = x , .y = y };
    }

    return point_arr;
}

static void* ds_get_cpydata(struct DataStruct* ds) {

    return (ds->ds_vtable->ds_get_cpydata)(ds->ds_instance);
}

static void ds_nextgen(struct DataStruct* ds, void* data, int* index_x, int* index_y) {
    if (ds->ds_vtable->ds_nextgen) {

        (ds->ds_vtable->ds_nextgen)(ds->ds_instance, data, index_x, index_y);
    }

}
*/
