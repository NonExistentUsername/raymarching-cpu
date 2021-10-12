#include <SDL2/SDL.h>

#ifndef GLOBAL_VARIABLES_H_INCLUDED
#define GLOBAL_VARIABLES_H_INCLUDED

constexpr int ray_march_iterations = 300;
constexpr double max_shape_distance = 1000.0;
constexpr double delta = 0.01;

constexpr int window_size_x = 1000;
constexpr int window_size_y = 600;
constexpr int pixel_size = 5;

constexpr int pixel_array_size_x = window_size_x / pixel_size + (window_size_x % pixel_size > 0);
constexpr int pixel_array_size_y = window_size_y / pixel_size + (window_size_y % pixel_size > 0);

constexpr int sdl_init_flags = SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE;
constexpr int sdl_createwindow_flags = SDL_WINDOW_SHOWN;
constexpr int sdl_createrenderer_flags = SDL_RENDERER_ACCELERATED;

#endif // GLOBAL_VARIABLES_H_INCLUDED
