#include "physics.h"

#include <stdio.h>

static void updateBird(Bird *bird, Uint64 timeElapsed);
static void updatePipes(struct Pipe *firstPipe, Uint64 timeElapsed);
static double randomNumber(double lower, double higher);

// Note: Time elapsed is in milliseconds
void update(Game *game, Uint64 timeElapsed) {
    // Update the Bird
    updateBird(game->_bird, timeElapsed);

    // Update the Pipes
    updatePipes(game->_pipes, timeElapsed);
}

static void updateBird(Bird *bird, Uint64 timeElapsed) {
    // Update Bird Height
    bird->_yVel -= (GRAVITY * timeElapsed / 1000);
    bird->_y += (bird->_yVel * timeElapsed / 1000);

    // Make sure bird does not go off screen
    if( bird->_y < LOWER_Y ) {
        bird->_y = LOWER_Y;
        bird->_yVel = 0;
    } else if ( bird->_y > UPPER_Y ) {
        bird->_y = UPPER_Y;
        bird->_yVel = 0;
    } 
}

static double randomNumber(double lower, double higher) {
    return ((higher - lower) * (rand() % 11 + 1.) / 10) + lower;
}
static void updatePipes(struct Pipe *firstPipe, Uint64 timeElapsed) {
    struct Pipe *prevPipe = firstPipe;
    struct Pipe *curPipe = firstPipe->next;

    // Iterate through all pipes, adjust their x-position
    while(curPipe) { // While current pipe is not null
        // Move Pipe X-Position
        curPipe->_x -= (XSPEED * timeElapsed / 1000);
        
        // If pipe is off screen, remove it
        if ( curPipe->_x + curPipe->_pipeWidth / 2 < 0 ) {
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
        
        newPipe->_gapHeight = randomNumber(10, 30);
        newPipe->_pipeWidth = randomNumber(4, 8);

        prevPipe->next = newPipe;

    } else if (prevPipe->_x - prevPipe->_pipeWidth / 2 < RIGHT_X) {
        struct Pipe* newPipe = malloc(sizeof(struct Pipe));

        // Randomly Generate New Pipe
        newPipe->next = NULL;

        newPipe->_x = (prevPipe->_x + prevPipe->_pipeWidth / 2) + randomNumber(10, 20);
        newPipe->_gapY = (prevPipe->_gapY + randomNumber(-5, 5));  
        
        newPipe->_gapHeight = randomNumber(10, 30);
        newPipe->_pipeWidth = randomNumber(4, 8);

        prevPipe->next = newPipe;

    }
    
}