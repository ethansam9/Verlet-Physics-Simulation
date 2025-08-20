#include "game.h"
#include <stdbool.h>

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
    g->frequency = SDL_GetPerformanceFrequency();
    g->lastTime = SDL_GetPerformanceCounter();
    g->deltaTime = 0;

    // Initialize Verlet objects
    Vector2 startPos = {640, 50};
    createVerletObject(startPos, (Vector2){0,0}, 5 , 1, g->renderer);
    
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

static bool isMousePressed = false;
static Uint32 mousePressStartTime = 0;
static int mouseX = 0, mouseY = 0;

void GameEvents(Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
            case SDL_EVENT_QUIT:
                g->isRunning = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (g->event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    g->isRunning = false;
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN: // Mouse button pressed
                if (g->event.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = true;
                    mouseX = g->event.button.x;
                    mouseY = g->event.button.y;
                    mousePressStartTime = SDL_GetTicks(); // Record the time when the button is pressed
                }
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP: // Mouse button released
                if (g->event.button.button == SDL_BUTTON_LEFT && isMousePressed) {
                    isMousePressed = false;
                    Uint32 mousePressDuration = SDL_GetTicks() - mousePressStartTime; // Calculate press duration

                    // Scale radius and mass based on press duration
                    float radius = 10 + (mousePressDuration / 100.0f); // Base radius + scaled by duration
                    float mass = 1 + (mousePressDuration / 1000.0f);   // Base mass + scaled by duration

                    // Clamp radius and mass to reasonable values
                    if (radius > 100) radius = 100;
                    if (mass > 10) mass = 10;

                    int newMouseX = g->event.button.x;
                    int newMouseY = g->event.button.y;

                    printf("Mouse released at (%d, %d) after %d ms\n", newMouseX, newMouseY, mousePressDuration);

                    // Create the ball at the mouse position
                    Vector2 clickPosition = {mouseX, mouseY};
                    createVerletObject(clickPosition, (Vector2){mouseX - newMouseX, mouseY - newMouseY}, radius, mass, g->renderer);

                    printf("Created ball at (%d, %d) with radius %.2f and mass %.2f\n", mouseX, mouseY, radius, mass);
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