/**
 * datastruct.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#include "DataStruct/datastruct.h"

struct DataStruct* ds_create(const struct datastruct_vtable_* _ds_vtable, ...) {
    struct DataStruct* ds = malloc(sizeof(struct DataStruct));
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

struct DataStruct* ds_get_cpydata(struct DataStruct* ds) {
    struct DataStruct* p = malloc(sizeof(struct DataStruct));

    if (ds->ds_vtable->ds_get_cpydata) {
        p->ds_vtable = ds->ds_vtable;
        p->ds_instance = (ds->ds_vtable->ds_get_cpydata)(ds->ds_instance);
    }

    return p;
}

void* ds_get_element(struct DataStruct* ds, ...) {
    void* p;

    if (ds->ds_vtable->ds_get_element) {
        va_list a_list;

        va_start(a_list, ds);
        p = (ds->ds_vtable->ds_get_element)(ds->ds_instance, &a_list);
        va_end(a_list);
    }

    return p;
}

void ds_add_element(struct DataStruct* ds, ...) {
    if (ds->ds_vtable->ds_add_element) {
        va_list a_list;

        va_start(a_list, ds);
        (ds->ds_vtable->ds_add_element)(ds->ds_instance, &a_list);
        va_end(a_list);
    }

}

void ds_rem_element(struct DataStruct* ds, ...) {
    if (ds->ds_vtable->ds_rem_element) {
        va_list a_list;

        va_start(a_list, ds);
        (ds->ds_vtable->ds_rem_element)(ds->ds_instance, &a_list);
        va_end(a_list);
    }

}
