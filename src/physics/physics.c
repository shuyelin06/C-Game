#include "physics.h"

#include <stdio.h>

static void updateBird(Game *game, Uint64 timeElapsed);
static void updatePipes(Game *game, Uint64 timeElapsed);
static void checkForCollisions(Game *game);
static double randomNumber(double lower, double higher);
static SDL_bool overlap(Bird *bird, SDL_Rect rect);

// Note: Time elapsed is in milliseconds
void update(Game *game, Uint64 timeElapsed) {
    // Update the Bird
    updateBird(game, timeElapsed);

    // Update the Pipes
    updatePipes(game, timeElapsed);

    // Check for Collisions
    checkForCollisions(game);
}

static void updateBird(Game *game, Uint64 timeElapsed) {
    // Get the Bird
    Bird *bird = game->_bird;

    // Update Bird Height
    bird->_yVel -= (GRAVITY * timeElapsed / 1000);
    bird->_y += (bird->_yVel * timeElapsed / 1000);

    // Make sure bird does not go off screen
    if( bird->_y < LOWER_Y || bird->_y > UPPER_Y) {
        printf("Game Over! Total Score: %d \n", game->score);
        game->_gameOver = SDL_TRUE;
    } 
}

static double randomNumber(double lower, double higher) {
    return ((higher - lower) * (rand() % 11 + 1.) / 10) + lower;
}
static void updatePipes(Game *game, Uint64 timeElapsed) {
    struct Pipe *firstPipe = game->_pipes;

    struct Pipe *prevPipe = firstPipe;
    struct Pipe *curPipe = firstPipe->next;

    // Iterate through all pipes, adjust their x-position
    while(curPipe) { // While current pipe is not null
        // Move Pipe X-Position
        curPipe->_x -= (XSPEED * timeElapsed / 1000);
        
        // If pipe is off screen, remove it
        if ( curPipe->_x + curPipe->_pipeWidth / 2 < 0 ) {
            game->score += 1;

            prevPipe->next = curPipe->next;
            free(curPipe);
            curPipe = prevPipe->next;
        } else {
            // Increment Pointer
            prevPipe = curPipe;
            curPipe = curPipe->next;
        }

    }

    // Check if the last pipe is being rendered - if it is, generate new pipes
    if (prevPipe->_x == -1) {
        struct Pipe* newPipe = malloc(sizeof(struct Pipe));

        // Randomly Generate New Pipe
        newPipe->next = NULL;

        newPipe->_x = RIGHT_X + 10;
        newPipe->_gapY = randomNumber(0.25 * UPPER_Y, 0.75 * UPPER_Y);   
        
        newPipe->_gapHeight = randomNumber(20, 25);
        newPipe->_pipeWidth = randomNumber(8, 12);

        prevPipe->next = newPipe;

    } else if (prevPipe->_x - prevPipe->_pipeWidth / 2 < RIGHT_X) {
        struct Pipe* newPipe = malloc(sizeof(struct Pipe));

        // Randomly Generate New Pipe
        newPipe->next = NULL;

        newPipe->_x = (prevPipe->_x + prevPipe->_pipeWidth / 2) + randomNumber(25, 35);
        newPipe->_gapY = (prevPipe->_gapY + randomNumber(-10, 10));  
        
        newPipe->_gapHeight = randomNumber(20, 25);
        newPipe->_pipeWidth = randomNumber(8, 12);

        prevPipe->next = newPipe;

    }
    
}

static void checkForCollisions(Game *game) {
    Bird *bird = game->_bird;
    struct Pipe *pipes = game->_pipes;

    struct Pipe *prevPipe = pipes;
    struct Pipe *curPipe = pipes->next;

    SDL_bool collision = SDL_FALSE;
    while (curPipe) {
        SDL_Rect top;
        top.h = (UPPER_Y - (curPipe->_gapY + curPipe->_gapHeight / 2));
        top.w = curPipe->_pipeWidth;
          
        top.x = curPipe->_x;
        top.y = curPipe->_gapY + curPipe->_gapHeight / 2 + top.h / 2;

        SDL_Rect bot;
        bot.x = curPipe->_x;
        bot.y = (curPipe->_gapY - curPipe->_gapHeight / 2) / 2;

        bot.h = (curPipe->_gapY - curPipe->_gapHeight / 2);
        bot.w = curPipe->_pipeWidth;

        if ( overlap(bird, top) == SDL_TRUE || overlap(bird, bot) == SDL_TRUE ) {
            collision = SDL_TRUE;
            break;
        }

        prevPipe = curPipe;
        curPipe = curPipe->next;
    }

    if ( collision == SDL_TRUE ) {
        printf("Game Over! Total Score: %d \n", game->score);
        game->_gameOver = SDL_TRUE;
    }
}
static SDL_bool overlap(Bird *bird, SDL_Rect rect) {
    if ( bird->_x + bird->_width / 2 <= rect.x - rect.w / 2 || rect.x + rect.w / 2 <= bird->_x - bird->_width / 2 ) {
        return SDL_FALSE;
    }
    if ( bird->_y + bird->_height / 2 <= rect.y - rect.h / 2 || rect.y + rect.h / 2 <= bird->_y - bird->_height / 2  ) {
        return SDL_FALSE;
    }
    return SDL_TRUE;
}