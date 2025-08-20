#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_gfx/SDL3_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "verlet.h"


#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_TITLE "Open Window"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool isRunning;
    Uint64 frequency;
    Uint64 lastTime;
    float deltaTime;
    //VerletObject *balls[];
}Game;

bool GameInitSDL(Game *g);
bool GameNew(Game **game);
void GameFree(Game **game);
void GameEvents(Game *g);
void GameUpdate(Game *g);
void GameDraw(Game *g);
void GameRun(Game *g);

#endif