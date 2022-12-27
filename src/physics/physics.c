#include "physics.h"

static void updateBird(Game *game, Uint64 timeElapsed) {
    // Get the Bird
    Bird *bird = game->_bird;
    
    // Update Bird Height
    bird->_yVel -= (GRAVITY * timeElapsed / 1000);
    bird->position->y += (bird->_yVel * timeElapsed / 1000);

    // Make sure bird does not go off screen
    if( bird->position->y < LOWER_Y || bird->position->y > UPPER_Y) {
        printf("Game Over (Press Space to Restart)! Total Score: %d \n", game->score);
        game->_gameOver = SDL_TRUE;
    } 

    // Update Bird Wing State
    if ( bird->_yVel > 0 ) {
        bird->state = WINGS_DOWN;
    } else {
        bird->state = WINGS_UP;
    }
}

static double randomNumber(double lower, double higher) {
    return ((higher - lower) * (rand() % 11 + 1.) / 10) + lower;
}
static void generateLowerPipe(const Pipe *pipe, Polygon *lower) {
    lower->center = pipe->center;
    lower->numEdges = 7;
    lower->edges = malloc(sizeof(Vector) * (7 + 1));

    // Dimensions         
    double botX = -pipe->_pipeWidth / 2;
    double botY = -pipe->_gapHeight / 2;
    double botW = pipe->_pipeWidth;
    double botH = pipe->center->y - pipe->_gapHeight / 2;

    lower->edges[0].x = botX + (0.235) * botW;
    lower->edges[0].y = botY - (0.998) * botH;

    lower->edges[1].x = botX + (0.038) * botW;
    lower->edges[1].y = botY - (0.524) * botH;

    lower->edges[2].x = botX + (0.132) * botW;
    lower->edges[2].y = botY - (0.308) * botH;

    lower->edges[3].x = botX + (0.675) * botW;
    lower->edges[3].y = botY - (0.023) * botH;

    lower->edges[4].x = botX + (0.875) * botW;
    lower->edges[4].y = botY - (0.098) * botH;
    
    lower->edges[5].x = botX + (0.946) * botW;
    lower->edges[5].y = botY - (0.548) * botH;

    lower->edges[6].x = botX + (0.906) * botW;
    lower->edges[6].y = botY - (0.991) * botH;

    lower->edges[7].x = botX + (0.235) * botW;
    lower->edges[7].y = botY - (0.998) * botH;
}
static void generateUpperPipe(const Pipe *pipe, Polygon *upper) {
    upper->center = pipe->center;
    upper->numEdges = 7;
    upper->edges = malloc(sizeof(Vector) * (7 + 1));
    
    // Dimensions of the Upper Hitbox
    double topX = -pipe->_pipeWidth / 2;
    double topY = pipe->_gapHeight / 2;
    double topW = pipe->_pipeWidth;
    double topH = UPPER_Y - (pipe->center->y + pipe->_gapHeight / 2);

    upper->edges[0].x = topX + (0.235) * topW;
    upper->edges[0].y = topY + (0.998) * topH;

    upper->edges[1].x = topX + (0.038) * topW;
    upper->edges[1].y = topY + (0.524) * topH;

    upper->edges[2].x = topX + (0.132) * topW;
    upper->edges[2].y = topY + (0.308) * topH;

    upper->edges[3].x = topX + (0.675) * topW;
    upper->edges[3].y = topY + (0.023) * topH;

    upper->edges[4].x = topX + (0.875) * topW;
    upper->edges[4].y = topY + (0.098) * topH;
    
    upper->edges[5].x = topX + (0.946) * topW;
    upper->edges[5].y = topY + (0.548) * topH;

    upper->edges[6].x = topX + (0.906) * topW;
    upper->edges[6].y = topY + (0.991) * topH;

    upper->edges[7].x = topX + (0.235) * topW;
    upper->edges[7].y = topY + (0.998) * topH;
}
static void updatePipes(Game *game, Uint64 timeElapsed) {
    Pipe *firstPipe = game->_pipes;

    Pipe *prevPipe = firstPipe;
    Pipe *curPipe = firstPipe->next;

    // Iterate through all pipes, adjust their x-position
    while(curPipe) { // While current pipe is not null
        // Move Pipe X-Position
        curPipe->center->x -= (XSPEED * timeElapsed / 1000);
        
        // If pipe is off screen, remove it
        if ( curPipe->center->x + curPipe->_pipeWidth / 2 < 0 ) {
            // Increase Game Score
            game->score += 1;

            // Removing from List
            prevPipe->next = curPipe->next;
            
            // Freeing Pipe's Memory
            free(curPipe->hitboxLower->edges);
            free(curPipe->hitboxLower);

            free(curPipe->hitboxUpper->edges);
            free(curPipe->hitboxUpper);
        
            free(curPipe->center);
            free(curPipe);
            
            // Incrementing Pointer 
            curPipe = prevPipe->next;
        } else {
            // Increment Pointer
            prevPipe = curPipe;
            curPipe = curPipe->next;
        }

    }

    // Check if the last pipe is being rendered - if it is, generate new pipes
    SDL_bool generateNewPipe = SDL_FALSE;
    if (prevPipe->center->x == -1) {
        // Allocate memory for new pipe
        Pipe* newPipe = malloc(sizeof(Pipe));
        
        newPipe->_gapHeight = randomNumber(20, 25);
        newPipe->_pipeWidth = randomNumber(8, 12);
        newPipe->next = NULL;

        // Pipe position
        Vector *position = malloc(sizeof(Vector));
        newPipe->center = position;

        position->x = RIGHT_X + 10;
        position->y = randomNumber(0.25 * UPPER_Y, 0.75 * UPPER_Y);   

        // Hitboxes - Lower Hitbox
        Polygon *lower = malloc(sizeof(Polygon));
        newPipe->hitboxLower = lower;

        generateLowerPipe(newPipe, lower);

        // Hitboxes - Upper Hitbox
        Polygon *upper = malloc(sizeof(Polygon));
        newPipe->hitboxUpper = upper;

        generateUpperPipe(newPipe, upper);

        // Append to List
        prevPipe->next = newPipe;

    } else if (prevPipe->center->x - prevPipe->_pipeWidth / 2 < RIGHT_X) {
        // Allocate memory for new pipe
        Pipe* newPipe = malloc(sizeof(Pipe));
        
        newPipe->_gapHeight = randomNumber(20, 25);
        newPipe->_pipeWidth = randomNumber(8, 12);
        newPipe->next = NULL;

        // Pipe position
        Vector *position = malloc(sizeof(Vector));
        newPipe->center = position;

        position->x = (prevPipe->center->x + prevPipe->_pipeWidth / 2) + randomNumber(25, 35);
        if ( prevPipe->center->y + 15 > UPPER_Y ) {
            position->y = (prevPipe->center->y + randomNumber(-5, -15));  
        } else if ( prevPipe->center->y - 15 < LOWER_Y ) {
            position->y = (prevPipe->center->y + randomNumber(5, 15));  
        } else {
            position->y = (prevPipe->center->y + randomNumber(-10, 10));  
        }

        // Hitboxes - Lower Hitbox
        Polygon *lower = malloc(sizeof(Polygon));
        newPipe->hitboxLower = lower;

        generateLowerPipe(newPipe, lower);

        // Hitboxes - Upper Hitbox
        Polygon *upper = malloc(sizeof(Polygon));
        newPipe->hitboxUpper = upper;

        generateUpperPipe(newPipe, upper);

        // Append to List
        prevPipe->next = newPipe;
    }
    
}

static void checkForCollisions(Game *game) {
    // Bird Hitbox
    Polygon *birdHitbox;
    if ( game->_bird->state == WINGS_DOWN ) {
        birdHitbox = game->_bird->hitboxDown;
    } else {
        birdHitbox = game->_bird->hitboxUp;
    }

    // Pipes
    Pipe *curPipe = game->_pipes->next;

    while (curPipe) {
        Polygon *topPipe = curPipe->hitboxUpper;
        Polygon *botPipe = curPipe->hitboxLower;

        if ( polygonIntersection(birdHitbox, topPipe) 
                || polygonIntersection(birdHitbox, botPipe) ) {
            printf("Game Over (Press Space to Restart)! Total Score: %d \n", game->score);
            game->_gameOver = SDL_TRUE;
            return;
        }

        curPipe = curPipe->next;
    }
    
}

// Note: Time elapsed is in milliseconds
void update(Game *game, Uint64 timeElapsed) {
    // Update the Bird
    updateBird(game, timeElapsed);

    // Update the Pipes
    updatePipes(game, timeElapsed);

    // Check for Collisions
    checkForCollisions(game);
}