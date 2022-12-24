#pragma once

#include "components/bird.h"
#include "components/pipe.h"

typedef struct {
    Bird *_bird;
    struct Pipe *_pipes;
} Game;