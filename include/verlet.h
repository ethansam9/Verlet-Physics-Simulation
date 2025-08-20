#ifndef VERLET_H
#define VERLET_H
#include "vectorMath.h"
#include "SDL3/SDL.h"
#include "SDL3_gfx/SDL3_gfxPrimitives.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_OBJECTS 4096

typedef struct verletObject{
    SDL_Renderer *renderer;
    Vector2 currPosition;
    Vector2 prevPosition;
    Vector2 velocity;
    Vector2 acceleration;
    float radius;
    float mass;

}VerletObject;

void createVerletObject(Vector2 position, Vector2 velocity, float radius, float mass, SDL_Renderer *renderer);
void applyGravity();
void updatePositions(float dt);
void applyConstraints(float width, float height);
void drawVerlets();
#endif