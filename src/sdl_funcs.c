/*
 * sdl_funcs.c 
 *
 *  Created on: Jan 1, 2020
 *      Author: Mickey
 */

#include "sdl_funcs.h"

// TODO proper error logging
SDL_SysMgr init_sdl(int window_width, int window_height) {
    SDL_SysMgr sdl_mgr;
    sdl_mgr.window = NULL;
    sdl_mgr.renderer = NULL;
    
    // Check for initialization failure
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL initialization failed:\n\t%s\n", SDL_GetError());

		return sdl_mgr;
	}

    /* TODO Clock Implementation
	if (TTF_Init() < 0) {
		printf("TTF initialization failed:\n\t%s\n", TTF_GetError());

		return sdl_mgr;
	}
    */

    // Initialize SDL_Window
	sdl_mgr.window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    
    SDL_SetWindowResizable(sdl_mgr.window, false);    
    
    // Check SDL_window for errors
	if (!sdl_mgr.window || (SDL_GetWindowSurface(sdl_mgr.window)->w != window_width)
      || (SDL_GetWindowSurface(sdl_mgr.window)->h != window_height)) {
		SDL_Log("Failed to create %d x %d window:\n\t%s\n", window_width,
		window_height, SDL_GetError());

		return sdl_mgr;
	}

    // Initialize SDL_Renderer
	sdl_mgr.renderer = SDL_CreateRenderer(sdl_mgr.window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdl_mgr.renderer, window_width, window_height);

    // Check SDL_Renderer for errors
	if (!sdl_mgr.renderer) {
		SDL_Log("Failed to create renderer:\n\t%s\n", SDL_GetError());

		return sdl_mgr;
	}

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") != SDL_TRUE) {
        SDL_Log("Failed to set hinting\n\t%s\n", SDL_GetError());
        
        return sdl_mgr;
    }
 
    SDL_DisplayMode display_mode;
 
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
        if (SDL_GetCurrentDisplayMode(i, &display_mode) != 0) {
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d:\n\t%s\n", i, SDL_GetError());
        } else {
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, display_mode.w, display_mode.h, display_mode.refresh_rate);
        }

    sdl_mgr.running = true;

    return sdl_mgr;
}

void input_handler(SDL_SysMgr* sdl_mgr, int* x, int* y) {
    while (SDL_PollEvent(&(sdl_mgr->events))) {
        switch (sdl_mgr->events.type) {
            case SDL_QUIT:
                sdl_mgr->running = false;
                break;
            case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    *x = sdl_mgr->events.motion.x;
                    *y = sdl_mgr->events.motion.y;
                }
        }
    }
    
}

void prepare_scene(SDL_SysMgr sdl_mgr, SDL_Point* points, int num_points) {
    // Set background to black
    SDL_SetRenderDrawColor(sdl_mgr.renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdl_mgr.renderer);
    
    // Set pixel color to red
    SDL_SetRenderDrawColor(sdl_mgr.renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoints(sdl_mgr.renderer, points, num_points);
    
    /* TODO Clock Implementation
    char* time_str = get_time(SDL_GetTicks());
    
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/gnu-free/FreeSans.ttf", 11);
    
    if (!font) {
        printf("TTF_Font call failed:\n\t%s\n", TTF_GetError());
        sdl_mgr.running = false;
        
        return;
    }
    
    int w = 0;
    int h = 0;
    SDL_Color white = { 255, 255, 255, 255 };
    
    if (TTF_SizeText(font, time_str, &w, &h)) {
        printf("TTF_SizeText call failed:\n\t%s\n", TTF_GetError());
        sdl_mgr.running = false;
        
        return;
    }
    
    SDL_Surface* message_surface = TTF_RenderText_Solid(font, time_str, white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(sdl_mgr.renderer, message_surface);
    SDL_FreeSurface(message_surface);
    TTF_CloseFont(font);
    
    SDL_Rect message_rect;
    message_rect.x = (sdl_mgr.window_width - w) / 2;
    message_rect.y = 0;
    message_rect.w = w;
    message_rect.h = h;
    
    SDL_RenderCopy(sdl_mgr.renderer, message, NULL, &message_rect);
    */
}

void present_scene(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
    
}

char* get_time(int time) {
    static char run_clock[9] = "";
    
    snprintf(run_clock, sizeof(run_clock), "%02d:%02d:%02d", (time / 3600000) % 60,
			(time / 60000) % 60, (time / 1000) % 60);
    
    return run_clock;
}

