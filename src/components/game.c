#include "game.h"

static void generateBirdHitboxUp(const Bird *bird, Polygon *hitbox) {
    hitbox->numEdges = 8;
    hitbox->edges = malloc(sizeof(Vector) * (8 + 1));

    // Dimensions of the Upper Hitbox
    double x = -bird->_width / 2;
    double y = bird->_height / 2;
    double w = bird->_width;
    double h = bird->_height;

    hitbox->edges[0].x = x + (0.017) * w;
    hitbox->edges[0].y = y - (0.2) * h;
    
    hitbox->edges[1].x = x + (0.4) * w;
    hitbox->edges[1].y = y - (0.882) * h;

    hitbox->edges[2].x = x + (0.71) * w;
    hitbox->edges[2].y = y - (0.982) * h;

    hitbox->edges[3].x = x + (0.845) * w;
    hitbox->edges[3].y = y - (0.886) * h;

    hitbox->edges[4].x = x + (0.974) * w;
    hitbox->edges[4].y = y - (0.467) * h;

    hitbox->edges[5].x = x + (0.893) * w;
    hitbox->edges[5].y = y - (0.228) * h;

    hitbox->edges[6].x = x + (0.729) * w;
    hitbox->edges[6].y = y - (0.123) * h;

    hitbox->edges[7].x = x + (0.195) * w;
    hitbox->edges[7].y = y - (0.024) * h;

    hitbox->edges[8].x = x + (0.017) * w;
    hitbox->edges[8].y = y - (0.2) * h;
}
static void generateBirdHitboxDown(const Bird *bird, Polygon *hitbox) {
    hitbox->numEdges = 7;
    hitbox->edges = malloc(sizeof(Vector) * (7 + 1));

    // Dimensions of the Upper Hitbox
    double x = -bird->_width / 2;
    double y = bird->_height / 2;
    double w = bird->_width;
    double h = bird->_height;

    hitbox->edges[0].x = x + (0.03) * w;
    hitbox->edges[0].y = y - (0.513) * h;
    
    hitbox->edges[1].x = x + (0.034) * w;
    hitbox->edges[1].y = y - (0.709) * h;

    hitbox->edges[2].x = x + (0.692) * w;
    hitbox->edges[2].y = y - (0.982) * h;

    hitbox->edges[3].x = x + (0.817) * w;
    hitbox->edges[3].y = y - (0.919) * h;

    hitbox->edges[4].x = x + (0.974) * w;
    hitbox->edges[4].y = y - (0.395) * h;

    hitbox->edges[5].x = x + (0.866) * w;
    hitbox->edges[5].y = y - (0.092) * h;

    hitbox->edges[6].x = x + (0.686) * w;
    hitbox->edges[6].y = y - (0.016) * h;

    hitbox->edges[7].x = x + (0.03) * w;
    hitbox->edges[7].y = y - (0.513) * h;
}
Game *newGame() {
    // Bird Position
    Vector *birdPosition = malloc(sizeof(Vector));
    birdPosition->x = 20;
    birdPosition->y = UPPER_Y / 2;
    // Bird Hitbox
    Polygon *birdHitboxUp = malloc(sizeof(Polygon));
    birdHitboxUp->center = birdPosition;
    Polygon *birdHitboxDown = malloc(sizeof(Polygon));
    birdHitboxDown->center = birdPosition;
    // Create Bird
    Bird *bird = malloc(sizeof(Bird));
    bird->_yVel = 0;
    bird->_width = 6;
    bird->_height = 6;
    bird->position = birdPosition;
    bird->hitboxUp = birdHitboxUp;
    bird->hitboxDown = birdHitboxDown;
    // Initialize Bird Hitbox
    generateBirdHitboxUp(bird, birdHitboxUp);
    generateBirdHitboxDown(bird, birdHitboxDown);

    // Dummy Pipe
    Vector *pipePosition = malloc(sizeof(Vector));
    pipePosition->x = -1;

    Pipe *dummyHead = malloc(sizeof(Pipe));
    dummyHead->center = pipePosition;
    dummyHead->hitboxLower = NULL;
    dummyHead->hitboxUpper = NULL;

    dummyHead->_pipeWidth = 0;
    dummyHead->_gapHeight = 0;

    dummyHead->next = NULL;

    // Create Game
    Game *game = malloc(sizeof(Game));
    game->_gameOver = SDL_FALSE;
    game->score = 0;
    game->_bird = bird;
    game->_pipes = dummyHead;

    return game;
}

void freeGame(Game *game) {
    // Free Bird
    free(game->_bird->hitboxUp->edges);
    free(game->_bird->hitboxUp);
    free(game->_bird->hitboxDown->edges);
    free(game->_bird->hitboxDown);

    free(game->_bird->position);
    free(game->_bird);

    // Free All Pipes
    Pipe *cur = game->_pipes;
    while ( cur ) {
        Pipe *next = cur->next;

        if ( cur->hitboxLower ) {
            free(cur->hitboxLower->edges);
        }
        free(cur->hitboxLower);
        
        if ( cur->hitboxUpper ) {
            free(cur->hitboxUpper->edges);
        }
        free(cur->hitboxUpper);
        
        free(cur->center);
        free(cur);

        cur = next;
    }
    
    // Free Game
    free(game);
}