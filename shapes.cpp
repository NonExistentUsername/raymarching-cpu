#include "default_classes.h"
#include "shapes.h"
#include "functions.h"

SPHERE::SPHERE() {}
SPHERE::SPHERE(double x, double y, double z, double size, Uint8 R, Uint8 G, Uint8 B) {
    position.set_position(x, y, z);
    color.set_color(R, G, B);
    this->size = size;
}
SPHERE::SPHERE(double x, double y, double z, double size, Uint8 R, Uint8 G, Uint8 B, Uint8 A) {
    position.set_position(x, y, z);
    color.set_color(R, G, B, A);
    this->size = size;
}
double SPHERE::get_length(POINT point) {
    return get_length_between_two_points(point, position) - size;
}

