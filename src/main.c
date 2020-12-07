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
    StructureType stype = CELLMAP;
    init_data_structure(stype, 640, 480);

    SDL_SysMgr sdlmgr = init_sdl(640, 480);
    int x, y;
   
    set_cell(320 - 1, 240 - 1);
    set_cell(320, 240 - 1);
    set_cell(320 + 1, 240 - 1);
    set_cell(320 - 1, 240);
    set_cell(320, 240);
    set_cell(320 + 1, 240);
    set_cell(320 - 1, 240 + 1);
    set_cell(320, 240 + 1);
    set_cell(320 + 1, 240 + 1);

    while (sdlmgr.running) {
        prepare_scene(sdlmgr, (SDL_Point*) next_generation(stype), get_num_points(stype));
        present_scene(sdlmgr.renderer);
        
        input_handler(&sdlmgr, &x, &y);
        // TODO Implement user-set refresh rate (restricted by monitor refresh rate)
        SDL_Delay(600);
	}

    del_data_structure(stype);
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

