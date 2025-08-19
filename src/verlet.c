#include "verlet.h"

#define MAX_OBJECTS 4096
#define GRAVITY 9.81f

static VerletObject objects[MAX_OBJECTS];
static int numObjects = 0;

void createVerletObject(Vector2 position, float radius, float mass, SDL_Renderer *renderer) {
    if (numObjects >= MAX_OBJECTS) return;
    VerletObject *ball = &objects[numObjects];
    ball->renderer = renderer;
    ball->currPosition = position;
    ball->prevPosition = position;
    ball->radius = radius;
    ball->mass = 1;
    //ball->color = color;
    numObjects++;
}

void applyGravity() {
    for (int i = 0; i < numObjects; i++) {
        objects[i].acceleration.y += GRAVITY;
    }
}

void updatePositions(float dt) {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        Vector2 pos = obj->currPosition;
        Vector2 prev = obj->prevPosition;
        Vector2 new = (Vector2){0,0};
        applyGravity();

        applyScalar(2, pos);
        subtractVectors(new, pos, prev);
        applyScalar(dt * dt ,obj->acceleration);
        addVectors(new, pos, obj->acceleration);

        applyConstraints(1280, 720);
        
        obj->prevPosition = pos;
        obj->currPosition = new;
    }
}

void applyConstraints(float width, float height) {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        if (obj->currPosition.x + obj->radius >= width) {
            float disp = obj->currPosition.x - obj->prevPosition.x;
            obj->currPosition.x = width;
            obj->prevPosition.x = obj->currPosition.x + disp;
        }
        if (obj->currPosition.x - obj->radius <= 0) {
            float disp = obj->currPosition.x - obj->prevPosition.x;
            obj->currPosition.x = 0;
            obj->prevPosition.x = obj->currPosition.x + disp;
        }
        if (obj->currPosition.y + obj->radius >= height) {
            float disp = obj->currPosition.y - obj->prevPosition.y;
            obj->currPosition.y = height;
            obj->prevPosition.y = obj->currPosition.y + disp;
        }
        if (obj->currPosition.y - obj->radius <= 0) {
            float disp = obj->currPosition.x - obj->prevPosition.x;
            obj->currPosition.y = height;
            obj->prevPosition.y = obj->currPosition.y + disp;
        }
    }
}

void drawVerlets() {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        SDL_SetRenderDrawColor(obj->renderer, 0,0,33, SDL_ALPHA_OPAQUE);
        printf("(%0.2f, %0.2f)\n", obj->currPosition.x, obj->currPosition.y);
        printf("NumObjects: %d\n", numObjects);
        filledCircleRGBA(obj->renderer, obj->currPosition.x, obj->currPosition.y, obj->radius, 0, 0, 255, SDL_ALPHA_OPAQUE);
    }
}

