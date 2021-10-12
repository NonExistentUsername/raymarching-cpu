#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "functions.h"
#include "global_variables.h"
#include "shapes.h"

void draw_pixel(int x, int y, SDL_Renderer* renderer, COLOR pixel_color[][pixel_array_size_y]) {
    SDL_SetRenderDrawColor(renderer, Uint8((double)pixel_color[x][y].R*pixel_color[x][y].brightness),
                                     Uint8((double)pixel_color[x][y].G*pixel_color[x][y].brightness),
                                     Uint8((double)pixel_color[x][y].B*pixel_color[x][y].brightness), pixel_color[x][y].A);
    if(pixel_size == 1)
        SDL_RenderDrawPoint(renderer, x, y);
    else {
        SDL_Rect rect = {pixel_size*x, pixel_size*y, pixel_size*(x+1), pixel_size*(y+1)};
        SDL_RenderFillRect(renderer, &rect);
    }
}
void draw_window(SDL_Renderer* renderer, COLOR pixel_color[][pixel_array_size_y]) {
    for(int x = 0; x < pixel_array_size_x; ++x)
        for(int y = 0; y < pixel_array_size_y; ++y)
            draw_pixel(x, y, renderer, pixel_color);
    SDL_RenderPresent(renderer);
}
double get_length_between_two_points(POINT point1, POINT point2) {
    return sqrt((point1.x-point2.x)*(point1.x-point2.x) + (point1.y-point2.y)*(point1.y-point2.y) + (point1.z-point2.z)*(point1.z-point2.z));
}
double get_cos_between_two_vec(VEC3 vec1, VEC3 vec2) {
    vec2.x *= -1;
    vec2.y *= -1;
    vec2.z *= -1;
    double A = (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
    double B = vec1.get_length() * vec2.get_length();
    if(A / B > 0)
        return A / B;
    else
        return 0;
}

void load_objects(std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights) {
//    shapes.push_back(new SHAPE());
    shapes->push_back(new SPHERE(8.0, 0.0, 0.0, 1.5, 255, 255, 128));
    shapes->push_back(new SPHERE(6.0, 1.0, -0.5, 1.0, 128, 255, 255));
    shapes->push_back(new SPHERE(7.0, -2.0, -1.6, 0.4, 128, 128, 255));
    shapes->push_back(new SPHERE(7.5, -1.0, -1.6, 0.4, 255, 128, 128));

    shapes->push_back(new SPHERE(0.0, 0.0, -1002.0, 1000.0, 255, 255, 255));

    lights->push_back(new SPHERE(1.0, 0.0, 10.0, 1.0, 255, 255, 255));
//    lights
}

RAY_INFO ray_march(VEC3 direction, POINT position, std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights, bool light);

RAY_INFO get_light(POINT point, std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights) {
    RAY_INFO ray;
    ray.shape = nullptr;
    ray.color.set_color(0, 0, 0);
    ray.color.brightness = 0;
    for(auto light : *lights) {
        VEC3 direction;
        direction.x = point.x - light->position.x;
        direction.y = point.y - light->position.y;
        direction.z = point.z - light->position.z;
        direction.normalize();
        RAY_INFO Q = ray_march(direction, light->position, shapes, lights, true);
        Q.color.brightness = 1;
        if(Q.shape != nullptr)
            return Q;
    }
    return ray;
}

void update_color(RAY_INFO* ray, RAY_INFO upd_ray) {
//    std::cout << "gg\n";
    if(ray->shape != upd_ray.shape) {
        ray->color.brightness = 0;
        return;
    }
    if(upd_ray.color.brightness == 0) {
        ray->color.brightness = 0;
        return;
    }
//    ray->color.brightness = get_cos_between_two_vec(ray->shape->get_normal(ray->position), upd_ray.direction);
    ray->color.brightness = get_cos_between_two_vec(ray->shape->get_normal(ray->position), upd_ray.direction);
}

RAY_INFO ray_march(VEC3 direction, POINT position, std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights, bool light) {
    RAY_INFO ray;
    ray.color.set_color(0, 0, 0);
    ray.direction = direction;
    double len;
    for(int i = 0; i < ray_march_iterations; ++i) {
        len = max_shape_distance;
        for(auto shape : *shapes)
            if(shape->get_length(position) < len) {
                len = shape->get_length(position);
                ray.shape = shape;
            }
        position.x += len * direction.x;
        position.y += len * direction.y;
        position.z += len * direction.z;
        ray.position = position;
        if(len >= max_shape_distance)
            return ray;
        if(len < delta) {
            ray.color = ray.shape->color;
            if(!light)
                update_color(&ray, get_light(position, shapes, lights));
//            ray.color.brightness = 0.5;
            return ray;
        }

    }
    return ray;
}


void render_window(CAMERA* camera, COLOR pixel_color[][pixel_array_size_y], std::vector<SHAPE*>* shapes, std::vector<SHAPE*>* lights) {
    POINT position = camera->position;
    for(int x = 0; x < pixel_array_size_x; ++x)
        for(int y = 0; y < pixel_array_size_y; ++y) {
            VEC3 direction = camera->get_direction_for_pixel(x, y);
            pixel_color[x][y] = ray_march(direction, position, shapes, lights, false).color;
        }
}

void cout_debug_info(void) {
    std::cout << pixel_size << " " << pixel_array_size_x << " " << pixel_array_size_y << '\n';
}

void set_pixel_color_default_data(COLOR* pixel_color[pixel_array_size_x][pixel_array_size_y]) {
    for(int x = 0; x < pixel_array_size_x; ++x)
        for(int y = 0; y < pixel_array_size_y; ++y)
            pixel_color[x][y]->set_color(x + y, x, y);
}

