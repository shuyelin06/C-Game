#include "graphics.h"

static SDL_Texture *birdTextureUp;
static SDL_Texture *birdTextureDown;

static SDL_Texture *pipeTexture;

// Render a Polygon using SDL2
static void renderPolygon(SDL_Renderer *renderer, const Polygon *polygon) {
    Vector* center = polygon->center;
    Vector* edges = polygon->edges;

    Vector vertexOne;
    Vector vertexTwo = { 
        (center->x + edges[0].x) * PIXELS_PER_UNIT, 
        SCREEN_HEIGHT - (center->y + edges[0].y) * PIXELS_PER_UNIT
    };

    for ( int i = 1; i < polygon->numEdges + 1; i++ ) {
        vertexOne = vertexTwo;

        vertexTwo.x = (center->x + edges[i].x) * PIXELS_PER_UNIT;
        vertexTwo.y = SCREEN_HEIGHT - (center->y + edges[i].y) * PIXELS_PER_UNIT;

        SDL_RenderDrawLine(renderer, 
            vertexOne.x, vertexOne.y, 
            vertexTwo.x, vertexTwo.y
        );
    }
}

// Debug (Draw Hitboxes)
void debug(SDL_Renderer *renderer, Game *game) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Render Bird Hitbox
    Bird *bird = game->_bird;

    if ( bird->state == WINGS_UP ) {
        renderPolygon(renderer, bird->hitboxUp);
    } else {
        renderPolygon(renderer, bird->hitboxDown);
    }   

    // Render Pipe Hitboxes
    Pipe *cur = game->_pipes->next;
    while(cur) {
        renderPolygon(renderer, cur->hitboxLower);
        renderPolygon(renderer, cur->hitboxUpper);

        // Increment Pointer
        cur = cur->next;
    }
}

/* Initialize Graphics Function and Helper Functions */
// Create a texture from a file
static SDL_Texture* createTexture(SDL_Renderer *renderer, const char *string) {
    SDL_Surface *surface = IMG_Load(string);
    if ( surface == NULL ) {
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if ( texture == NULL ) {
        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}
// Initialize Graphics for the Game
int initializeGraphics(SDL_Renderer *renderer) {
    birdTextureUp = createTexture(renderer, ".\\res\\birdUp.png");
    if ( birdTextureUp == NULL ) {
        return GRAPHICS_INIT_FAIL;
    }

    birdTextureDown = createTexture(renderer, ".\\res\\birdDown.png");
    if ( birdTextureDown == NULL ) {
        return GRAPHICS_INIT_FAIL;
    }

    pipeTexture = createTexture(renderer, ".\\res\\pipe.png");
    if ( pipeTexture == NULL ) {
        return GRAPHICS_INIT_FAIL;
    }

    return 1;
}

/* Destroy Graphics Function */
void destroyGraphics() {
    SDL_DestroyTexture(birdTextureUp);
    SDL_DestroyTexture(birdTextureDown);
    SDL_DestroyTexture(pipeTexture);
}

/* Render Function and Helper Functions */
static void drawBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Black Color
    SDL_RenderClear(renderer); // Black Screen
}

static void drawBird(SDL_Renderer *renderer, Bird *bird) {
    // Create a Rectangle for the Bird
    SDL_Rect rect = {
        (bird->position->x - bird->_width / 2) * PIXELS_PER_UNIT,
        SCREEN_HEIGHT - (bird->position->y + bird->_height / 2) * PIXELS_PER_UNIT,
        bird->_width * PIXELS_PER_UNIT,
        bird->_height * PIXELS_PER_UNIT
    };

    // Render the Bird Sprite
    if ( bird->state == WINGS_UP ) {
        SDL_RenderCopy(renderer, birdTextureUp, NULL, &rect);
    } else {
        SDL_RenderCopy(renderer, birdTextureDown, NULL, &rect);
    }    
}

static void drawPipes(SDL_Renderer *renderer, Pipe *firstPipe) {
    Pipe *cur = firstPipe;

    while(cur) {
        // Create a Rectangle for the Upper Pipe
        SDL_Rect upperRect = {
            (cur->center->x - cur->_pipeWidth / 2) * PIXELS_PER_UNIT,
            0,
            cur->_pipeWidth * PIXELS_PER_UNIT,
            SCREEN_HEIGHT - (cur->center->y + cur->_gapHeight / 2) * PIXELS_PER_UNIT
        };

        // Create a Rectangle for the Lower Pipe
        SDL_Rect lowerRect = {
            (cur->center->x - cur->_pipeWidth / 2) * PIXELS_PER_UNIT,
            SCREEN_HEIGHT - (cur->center->y - cur->_gapHeight / 2) * PIXELS_PER_UNIT,
            cur->_pipeWidth * PIXELS_PER_UNIT,
            (cur->center->y - cur->_gapHeight / 2) * PIXELS_PER_UNIT
        };

        // Render the Upper Pipe Texture Upside Down
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &upperRect, 0, NULL, SDL_FLIP_VERTICAL);
        // Render the Lower Pipe Texture Normally
        SDL_RenderCopy(renderer, pipeTexture, NULL, &lowerRect);

        // Increment Pointer
        cur = cur->next;
    }
}

void render(SDL_Renderer *renderer, Game *game) {
    // Draw Background
    drawBackground(renderer);

    // Draw Bird
    drawBird(renderer, game->_bird);
    
    // Draw Pipes
    drawPipes(renderer, game->_pipes->next);
}