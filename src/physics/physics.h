#pragma once

#include <SDL2/SDL.h>

#include "../main/game.h"
#include "../rendering/graphics.h"

#define XSPEED 25.

#define LEFT_X 0
#define RIGHT_X (SCREEN_WIDTH / PIXELS_PER_UNIT)

#define LOWER_Y 0
#define UPPER_Y (SCREEN_HEIGHT / PIXELS_PER_UNIT)

#define JUMP 25.
#define GRAVITY 65.

void update(Game *game, Uint64 timeElapsed);