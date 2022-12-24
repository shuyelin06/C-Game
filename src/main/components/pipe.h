#pragma once 

struct Pipe {
    double _x; // X-Coordinate of the Pipe

    double _pipeWidth; // Pipe Width
    
    double _gapY; // Center Y-Coordinate of the Pipe's Gap
    double _gapHeight; // Gap Height

    struct Pipe *next; // Next Pipe
};