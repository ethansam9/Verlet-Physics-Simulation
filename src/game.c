#include "game.h"

bool GameInitSDL(Game *g) {
    if (!SDL_Init(SDL_FLAGS)) {
        SDL_Log("Error initializing SDL3: %s\n", SDL_GetError());
        return false;
    }

    g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (g->window == NULL) {
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        return false;
    }

    g->renderer = SDL_CreateRenderer(g->window, NULL);
    if (g->renderer == NULL) {
        SDL_Log("Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    createVerletObject((Vector2){640, 700}, 5, 1, g->renderer);
    
    return true;
}

bool GameNew(Game **game) {
    *game = calloc(1, sizeof(Game));
    if (*game == NULL) {
        fprintf(stderr, "Error Calloc of New Game\n");
    }
    Game *g = *game;

    if (!GameInitSDL(g)) {
        return false;
    }
    g->isRunning = true;
    return true;
}

void GameFree(Game **game) {
    if (*game) {
        Game *g = *game;

        if (g->renderer) {
            SDL_DestroyRenderer(g->renderer);
            g->renderer = NULL;
        }
        if (g->window) {
            SDL_DestroyWindow(g->window);
            g->window = NULL;
        }
        free(g);
        g = NULL;
        *game = NULL;

        SDL_Quit();
        printf("All clean\n");
    }
}

void GameEvents(Game *g) {
    while (SDL_PollEvent(&g->event)) {
            switch (g->event.type)
            {
            case SDL_EVENT_QUIT:
                g->isRunning = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch(g->event.key.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        g->isRunning = false;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
            }
        }
}

void GameUpdate(Game *g) {
    updatePositions(g->deltaTime);
}

void GameDraw(Game *g){    
    SDL_SetRenderDrawColor(g->renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(g->renderer);
    filledCircleRGBA(g->renderer, 640, 360, 50, 0, 255, 0, SDL_ALPHA_OPAQUE);
    drawVerlets();
    SDL_RenderPresent(g->renderer);
}

void GameRun(Game *g) {
    while (g->isRunning) {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        g->deltaTime = (float)(currentTime - g->lastTime) / g->frequency;
        g->lastTime = currentTime; 
        GameEvents(g);
        GameUpdate(g);
        GameDraw(g);
        SDL_Delay(16);
    }
}