/**
 * main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mickey
 */

#include <stdio.h>
#include "sdl_funcs.h"
#include "ds_twodim_boolarr.h"
#include "datastruct.h"

int main() {
    struct DataStruct* ds = ds_create(DS_TDBA, 640, 480);
    SDL_SysMgr sdlmgr = init_sdl(640, 480);

//    int event_status;
//    int x, y;
//
//    while ((event_status = input_handler(&sdlmgr, &x, &y)) != 1) {
//        if (event_status == 2)
//            set_cell(x, y);
//
//        prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype, false), get_num_points(stype));
//        present_scene(sdlmgr.renderer);
//
//        SDL_Delay(10);
//    }

    while (input_handler(&sdlmgr, NULL, NULL) >= 0) {
        prepare_scene(sdlmgr, ds_get_sdlpoints(ds), ds_get_numpoints(ds));
        present_scene(sdlmgr.renderer);

        ds_nextgen(ds);

        SDL_Delay(100); // TODO Implement user-set refresh rate (restricted by monitor refresh rate)
    }

    ds_delete(ds);

    return 0;
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

/*
void get_points_rec(Node* node, SDL_Point* points, int* index) {
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
