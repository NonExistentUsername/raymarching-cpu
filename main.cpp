#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

#include "global_variables.h"
#include "shapes.h"
#include "functions.h"

CAMERA camera(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, pixel_array_size_x, pixel_array_size_y, 60.0);

COLOR pixel_color[pixel_array_size_x][pixel_array_size_y];
std::vector<SHAPE*> shapes;
std::vector<SHAPE*> lights;

int main(int argc, char *argv[]) {
    if(SDL_Init(sdl_init_flags) != 0)
        return 1;

    SDL_Window* window = SDL_CreateWindow("im so sad.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          window_size_x, window_size_y, sdl_createwindow_flags);
    if(window == nullptr)
        return 2;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, sdl_createrenderer_flags);
    if(renderer == nullptr)
        return 3;

    load_objects(&shapes, &lights);

//    render_window(&camera, pixel_color, &shapes, &lights);

    SDL_Event event;
    bool rendering = true;
    double v = lights[0]->position.x;
    double u = lights[0]->position.y;
    while(rendering) {
        lights[0]->position.x = v + sin(clock()/1000.0)*1.2;
        lights[0]->position.y = u + cos(clock()/1000.0)*1.5;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                rendering = false;
        }
        render_window(&camera, pixel_color, &shapes, &lights);

        draw_window(renderer, pixel_color);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
