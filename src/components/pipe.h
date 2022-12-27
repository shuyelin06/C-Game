#pragma once 

#include <geometry/polygon.h>

typedef struct _Pipe Pipe;

struct _Pipe {
    Vector *center;         // Pipe Coordinates (x, gap y)

    double _pipeWidth;      // Pipe Width
    double _gapHeight;      // Gap Height

    Polygon *hitboxLower;   // Hitbox for the Lower Pipe
    Polygon *hitboxUpper;   // Hitbox for the Upper Pipe
    
    Pipe *next;      // Next Pipe
};