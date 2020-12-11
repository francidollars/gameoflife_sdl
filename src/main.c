/**
 * main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mickey
 */

#include <stdlib.h>
#include <stdio.h>
#include "sdl_funcs.h"
#include "datastructure.h"

int main (int argc, char* args[]) {
   /* if (argc < 4 && atoi(args[3]) != 0) {

        return EXIT_FAILURE;
    } */

    StructureType stype = CELLMAP; // (StructureType) strtol(args[3], NULL, 10);
    // unsigned int init_width = 640; // (unsigned int) strtol(args[1], NULL, 10);
    // unsigned int init_height = 480; // (unsigned int) strtol(args[2], NULL, 10);

    init_data_structure(stype, 640, 480);

    SDL_SysMgr sdlmgr = init_sdl(640, 480);
    int event_status;
    int x, y;
   
    while ((event_status = input_handler(&sdlmgr, &x, &y)) != 1) {
        if (event_status == 2)
            set_cell(x, y);

        prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype, false), get_num_points(stype));
        present_scene(sdlmgr.renderer);

        SDL_Delay(10);
    }

    while (input_handler(&sdlmgr, NULL, NULL) > 0) {
        prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype, true), get_num_points(stype));
        present_scene(sdlmgr.renderer);
        
        // TODO Implement user-set refresh rate (restricted by monitor refresh rate)
        SDL_Delay(100);
	}

    del_data_structure(stype);
    FC_FreeFont(sdlmgr.font);
    SDL_Quit();

    return 0;
}

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

