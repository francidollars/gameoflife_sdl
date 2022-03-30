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
#include <SDL2/SDL_rect.h>

struct datastruct_vtable_ {
    void* (*ds_ctor)(va_list*);
    void (*ds_dtor)(void*);
    int (*ds_get_numpoints)(void*);
    void (*ds_getpoints)(void*, int*, int*);
    void (*ds_nextgen)(void*);
    // void* (*ds_get_cpydata)(void*);
    // void (*ds_nextgen)(void*, void*, int*, int*);
};

struct DataStruct {
    const struct datastruct_vtable_* ds_vtable;
    void* ds_instance;
    // TODO: SDL_Point**
};

struct DataStruct* ds_create(const struct datastruct_vtable_*, ...);

/**
 * Free memory utilized by data structure (called before exiting)
 */
void ds_delete(struct DataStruct*);

int ds_get_numpoints(struct DataStruct*);

SDL_Point* ds_get_sdlpoints(struct DataStruct*);

void ds_nextgen(struct DataStruct*);

/**
 * Function to convert next generation points to generic Point array
 *
SDL_Point* ds_nextgen_getpoints(struct DataStruct*);
*/

#endif /* DATASTRUCT_H_ */
