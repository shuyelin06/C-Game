#pragma once

#include "components/bird.h"
#include "components/pipe.h"

struct Game {
    struct Bird _bird;
    struct Pipe *_pipes;
};