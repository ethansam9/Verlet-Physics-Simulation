#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_gfx/SDL3_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_TITLE "Open Window"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool isRunning;
    /*VerletObject *obj;
    Uint64 frequency;
    Uint64 lastTime;
    float deltaTime;*/
}Game;

bool GameInitSDL(Game *g);
bool GameNew(Game **game);
void GameFree(Game **game);
void GameEvents(Game *g);
void GameDraw(Game *g);
void GameRun(Game *g);

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

void GameDraw(Game *g){    

    SDL_SetRenderDrawColor(g->renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(g->renderer);
    filledCircleRGBA(g->renderer, 640, 360, 100, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(g->renderer);
}

void GameRun(Game *g) {
    while (g->isRunning) {
        /*Uint64 currentTime = SDL_GetPerformanceCounter();
        g->deltaTime = (float)(currentTime - g->lastTime) / g->frequency;
        g->lastTime = currentTime; */
        GameEvents(g);
        GameDraw(g);
        SDL_Delay(16);
    }
}

int main(void) {
    bool exitStatus = EXIT_FAILURE;

    Game *game = NULL;

    if (GameNew(&game)) {
        GameRun(game);
        exitStatus = EXIT_SUCCESS;
    }

    GameFree(&game);
    return exitStatus;
}
