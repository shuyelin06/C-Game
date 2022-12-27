#pragma once

#include "bird.h"
#include "pipe.h"

#include <geometry/polygon.h>
#include <settings.h>

#include <SDL2/SDL.h>


typedef struct _Game Game;

struct _Game {
    Bird *_bird;
    Pipe *_pipes;
    
    SDL_bool _gameOver;
    int score;
};

Game *newGame();

void freeGame(Game *game);