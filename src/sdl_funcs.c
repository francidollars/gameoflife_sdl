/*
 * sdl_funcs.c
 *
 *  Created on: Jan 1, 2020
 *      Author: Mickey
 */

#include "sdl_funcs.h"

// TODO: proper error logging
// TODO: One return sdl_mgr statement
SDL_SysMgr init_sdl(int window_width, int window_height) {
    SDL_SysMgr sdl_mgr;
    sdl_mgr.window = NULL;
    sdl_mgr.renderer = NULL;

    // Check for initialization failure
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // TODO: Change to SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS
		SDL_Log("SDL initialization failed:\n\t%s\n", SDL_GetError());

		return sdl_mgr;
	}

    // Initialize SDL_Window
	sdl_mgr.window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

    SDL_SetWindowResizable(sdl_mgr.window, SDL_FALSE); //TODO: Pass flags in SDL_CreateWindow, this might not be necessary

    // Check SDL_window for errors
	if (!sdl_mgr.window) {
		SDL_Log("Failed to create %d x %d window:\n\t%s\n", window_width, window_height, SDL_GetError());

		return sdl_mgr;
	}

    // Initialize SDL_Renderer
	sdl_mgr.renderer = SDL_CreateRenderer(sdl_mgr.window, -1, 0);
	SDL_RenderSetLogicalSize(sdl_mgr.renderer, window_width, window_height);

    // Check SDL_Renderer for errors
	if (!sdl_mgr.renderer) {
		SDL_Log("Failed to create renderer:\n\t%s\n", SDL_GetError());

		return sdl_mgr;
	}

    // if ((SDL_GetWindowSurface(sdl_mgr.window)->w != window_width) || (SDL_GetWindowSurface(sdl_mgr.window)->h != window_height)) { }

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") != SDL_TRUE) {
        SDL_Log("Failed to set hinting:\n\t%s\n", SDL_GetError());

        return sdl_mgr;
    }

    SDL_DisplayMode display_mode;

    for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
        if (SDL_GetCurrentDisplayMode(i, &display_mode) != 0) {
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d:\n\t%s\n", i, SDL_GetError());
        } else {
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, display_mode.w, display_mode.h,
              display_mode.refresh_rate);
        }
    }

	if (TTF_Init() < 0) {
		printf("TTF initialization failed:\n\t%s\n", TTF_GetError());

		return sdl_mgr;
	}

    // TODO Dynamically select font
    sdl_mgr.font = FC_CreateFont();
    FC_LoadFont(sdl_mgr.font, sdl_mgr.renderer, "/usr/share/fonts/liberation/LiberationMono-Regular.ttf",
      11, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    if (!sdl_mgr.font) {
        printf("TTF_Font call failed:\n\t%s\n", TTF_GetError());
        sdl_mgr.running = false;

        return sdl_mgr;
    }

    sdl_mgr.running = true;

    return sdl_mgr;
}

// TODO: Return SDL enum
int input_handler(SDL_SysMgr* sdl_mgr, int* x, int* y) {
    int event_int = 0;

    while (SDL_PollEvent(&(sdl_mgr->events))) {
        switch (sdl_mgr->events.type) {
            case SDL_QUIT:
                event_int = -1;
                break;
            case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    *x = sdl_mgr->events.motion.x;
                    *y = sdl_mgr->events.motion.y;
                    event_int = 2;
                }
                break;
            case SDL_KEYDOWN:
                switch (sdl_mgr->events.key.keysym.sym) {
                    case SDLK_SPACE:
                        event_int = 1;
                        break;
                    default:
                        break;
                }
        }
    }

    return event_int;
}

/* void prepare_scene(SDL_SysMgr sdl_mgr, SDL_Point* points, int num_points) {
    // Set background to black
    if (SDL_SetRenderDrawColor(sdl_mgr.renderer, 0, 0, 0, 0))
        SDL_Log("Failed to set SDL_Renderer draw color (on clear):\n\t%s\n", SDL_GetError());
    if (SDL_RenderClear(sdl_mgr.renderer))
        SDL_Log("Failed to SDL_RenderClear:\n\t%s\n", SDL_GetError());

    // Set pixel color to red
    if (SDL_SetRenderDrawColor(sdl_mgr.renderer, 255, 0, 0, 255))
        SDL_Log("Failed to set SDL_Renderer draw color (on points):\n\t%s\n", SDL_GetError());
    if (SDL_RenderDrawPoints(sdl_mgr.renderer, points, num_points))
        SDL_Log("Failed to SDL_RenderDrawPoints:\n\t%s\n", SDL_GetError());

    // char* time_str = get_time(SDL_GetTicks());

    // FC_Draw(sdl_mgr.font, sdl_mgr.renderer, ((SDL_GetWindowSurface(sdl_mgr.window)->w - FC_GetWidth(sdl_mgr.font, "%s", time_str)) / 2), 0, "%s", time_str);

} */

void prepare_scene(SDL_SysMgr sdl_mgr) {
    // Set background to black
    if (SDL_SetRenderDrawColor(sdl_mgr.renderer, 0, 0, 0, 0))
        SDL_Log("Failed to set SDL_Renderer draw color (on clear):\n\t%s\n", SDL_GetError());
    if (SDL_RenderClear(sdl_mgr.renderer))
        SDL_Log("Failed to SDL_RenderClear:\n\t%s\n", SDL_GetError());

    // char* time_str = get_time(SDL_GetTicks());

    // FC_Draw(sdl_mgr.font, sdl_mgr.renderer, ((SDL_GetWindowSurface(sdl_mgr.window)->w - FC_GetWidth(sdl_mgr.font, "%s", time_str)) / 2), 0, "%s", time_str);

}

void draw_point_scene(SDL_SysMgr sdl_mgr, int x, int y) {
    if (SDL_SetRenderDrawColor(sdl_mgr.renderer, 255, 0, 0, 255))
        SDL_Log("Failed to set SDL_Renderer draw color (on points):\n\t%s\n", SDL_GetError());
    if (SDL_RenderDrawPoint(sdl_mgr.renderer, x, y))
        SDL_Log("Failed SDL_RenderDrawPoint:\n\t%s\n", SDL_GetError());

}

void present_scene(SDL_SysMgr sdl_mgr) {
    SDL_RenderPresent(sdl_mgr.renderer);

}

char* get_time(int time) {
    static char run_clock[9] = "";

    snprintf(run_clock, sizeof(run_clock), "%02d:%02d:%02d", (time / 3600000) % 60,
	  (time / 60000) % 60, (time / 1000) % 60);

    return run_clock;
}
