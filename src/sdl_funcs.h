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
// #include <SDL2/SDL_ttf.h>

typedef struct SDL_SysMgr {
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event events;
    // int window_width; use SDL_GetWindowSurface(SDL_Window* window)->w
    // int window_height; use SDL_GetWindowSurface(SDL_Window* window)->h
    int ref_rate;
    bool running;
} SDL_SysMgr;

/**
 * Initialize SDL
 */
SDL_SysMgr init_sdl(int window_width, int window_height);

/**
 * Handling input from user
 */
void input_handler(SDL_SysMgr* sdl_mgr, int* x, int* y);

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

#endif /* CELLMAP_H_ */

