/*
 * sdl_funcs.h
 *
 *  Created on: Jan 1, 2020
 *      Author: Mickey
 */

#ifndef SDL_FUNCS_H_
#define SDL_FUNCS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_FontCache.h"

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event events;
    FC_Font* font;
    // int window_width; use SDL_GetWindowSurface(SDL_Window* window)->w
    // int window_height; use SDL_GetWindowSurface(SDL_Window* window)->h
    int ref_rate; // TODO: Already stored in SDL_DisplayMode
    bool running;
} SDL_SysMgr;

/**
 * Initialize SDL
 */
SDL_SysMgr init_sdl(int window_width, int window_height);

/**
 * Handling input from user
 */
int input_handler(SDL_SysMgr* sdl_mgr, int* x, int* y);

/**
 * Prepare window for display
 */
void prepare_scene(SDL_SysMgr sdl_mgr, SDL_Point* points, int num_points);

/**
 * Display window
 */
void present_scene(SDL_Renderer* renderer);

/**
 * Get string of time
 *
 * @param time -
 * @return Returns string of application run time
 */
char* get_time(int time);

#endif /* SDL_FUNCS_H_ */
