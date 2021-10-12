#include <SDL2/SDL.h>

#ifndef DEFAULT_CLASSES_H_INCLUDED
#define DEFAULT_CLASSES_H_INCLUDED

class COLOR{
public:
    Uint8 R=0, G=0, B=0, A=255;
    double brightness = 1;
    COLOR();
    COLOR(Uint8 R, Uint8 G, Uint8 B);
    COLOR(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
    void set_color(Uint8 R, Uint8 G, Uint8 B);
    void set_color(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
};

class POINT{
public:
    double x=0, y=0, z=0;
    POINT();
    POINT(double x, double y, double z);
    void set_position(double x, double y, double z);
};

class VEC3{
public:
    double x=0, y=0, z=0;
    VEC3();
    VEC3(double x, double y, double z);
    void set_direction(double x, double y, double z);
    void normalize(void);
    double get_length(void);
};

class CAMERA{
public:
    POINT position;
    VEC3 direction;
    double horizontal_angle, verctical_angle;
    int size_x = 0, size_y = 0;
    CAMERA(double x, double y, double z, double dx, double dy, double dz, double size_x, double size_y, double angle);
    VEC3 get_direction_for_pixel(int x, int y);
};

#endif // DEFAULT_CLASSES_H_INCLUDED
