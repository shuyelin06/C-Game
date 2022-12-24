#pragma once

#include "components/bird.h"
#include "components/pipe.h"

#include <SDL2/SDL.h>

typedef struct {
    Bird *_bird;
    struct Pipe *_pipes;
    
    SDL_bool _gameOver;
    int score;
} Game;