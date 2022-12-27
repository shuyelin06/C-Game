#pragma once 

#include <geometry/polygon.h>

#define WINGS_DOWN 0
#define WINGS_UP 1

typedef struct _Bird Bird;

struct _Bird {
    Vector* position;    // Position 

    Polygon *hitboxUp;    // Bird Hitbox (Wings Up)
    Polygon *hitboxDown;    // Bird Hitbox (Wings Down)
    
    int state;
    
    double _width;      // Width
    double _height;     // Height

    double _yVel;       // Y-Velocity
};