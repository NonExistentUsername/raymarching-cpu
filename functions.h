#include <vector>
#include "global_variables.h"
#include "shapes.h"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void set_pixel_color_default_data();
void cout_debug_info(void);

void render_window(CAMERA* camera, COLOR pixel_color[][pixel_array_size_y], std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights);
void draw_window(SDL_Renderer* renderer, COLOR pixel_color[][pixel_array_size_y]);
double get_length_between_two_points(POINT point1, POINT point2);

void load_objects(std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights);

#endif // FUNCTIONS_H_INCLUDED
