/**
 * datastruct.h
 *
 *  Created on: Dec 6, 2020
 *      Author: Mickey
 */

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

struct datastruct_vtable_ {
    void* (*ds_ctor)(va_list*);
    void (*ds_dtor)(void*);
    struct DataStruct* (*ds_get_cpydata)(void*);
    void* (*ds_get_element)(void*, va_list*);
    void (*ds_add_element)(void*, va_list*);
    void (*ds_rem_element)(void*, va_list*);
};

struct DataStruct {
    const struct datastruct_vtable_* ds_vtable;
    void* ds_instance;
};

extern int ds_int;

struct DataStruct* ds_create(const struct datastruct_vtable_*, ...);

/**
 * Free memory utilized by data structure (called before exiting)
 */
void ds_delete(struct DataStruct*);

struct DataStruct* ds_get_cpydata(struct DataStruct*);

void* ds_get_element(struct DataStruct*, ...);

void ds_add_element(struct DataStruct*, ...);

void ds_rem_element(struct DataStruct*, ...);

#endif /* DATASTRUCT_H_ */
