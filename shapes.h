#include "default_classes.h"

#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

class SHAPE{
public:
    COLOR color;
    POINT position;
    virtual double get_length(POINT point) = 0;
    VEC3 get_normal(POINT point) {
        double dist = get_length(point);
        double delta = 0.01;
        VEC3 normal;
        point.x -= delta;
        normal.x = dist - get_length(point);
        point.x += delta;

        point.y -= delta;
        normal.y = dist - get_length(point);
        point.y += delta;

        point.z -= delta;
        normal.z = dist - get_length(point);
        normal.normalize();
        return normal;
    }
};

class SPHERE : public SHAPE{
public:
    double size = 1.0;
    SPHERE();
    SPHERE(double x, double y, double z, double size, Uint8 R, Uint8 G, Uint8 B);
    SPHERE(double x, double y, double z, double size, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
    double get_length(POINT point);
};

struct RAY_INFO{
    POINT position;
    VEC3 direction;
    COLOR color;
    SHAPE* shape;
};

#endif // SHAPES_H_INCLUDED
