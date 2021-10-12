#include <iostream>
#include <math.h>
#include "default_classes.h"
#define PI 3.14159265359

COLOR::COLOR() {}
COLOR::COLOR(Uint8 R, Uint8 G, Uint8 B) {
    this->R = R;
    this->G = G;
    this->B = B;
}
COLOR::COLOR(Uint8 R, Uint8 G, Uint8 B, Uint8 A) {
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
}
void COLOR::set_color(Uint8 R, Uint8 G, Uint8 B) {
    this->R = R;
    this->G = G;
    this->B = B;
}
void COLOR::set_color(Uint8 R, Uint8 G, Uint8 B, Uint8 A) {



    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
}

POINT::POINT() {}
POINT::POINT(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void POINT::set_position(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

VEC3::VEC3() {}
VEC3::VEC3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void VEC3::set_direction(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void VEC3::normalize(void) {
    double len = sqrt(x*x + y*y + z*z);
    x /= len;
    y /= len;
    z /= len;
}
double VEC3::get_length(void) {
    return sqrt(x*x + y*y + z*z);
}

CAMERA::CAMERA(double x, double y, double z, double dx, double dy, double dz, double size_x, double size_y, double angle) {
    position.set_position(x, y, z);
    direction.set_direction(dx, dy, dz);
    this->size_x = size_x;
    this->size_y = size_y;
    horizontal_angle = angle * PI / 180.0;
    verctical_angle = (angle * size_y / size_x) * PI / 180.0;
}
VEC3 CAMERA::get_direction_for_pixel(int x, int y) {
    VEC3 ans = direction;
    VEC3 dir = direction;
    double angle = verctical_angle / (double)size_y * ((double)y - (double)size_y / 2.0);
    ans.x = dir.x * cos(angle) + dir.z * sin(angle);
    ans.z = -dir.x * sin(angle) + dir.z * cos(angle);
    dir = ans;
    angle = horizontal_angle / (double)size_x * ((double)x - (double)size_x / 2.0);
    ans.x = dir.x * cos(angle) - dir.y * sin(angle);
    ans.y = dir.x * sin(angle) + dir.y * cos(angle);
    ans.normalize();
    return ans;
}
