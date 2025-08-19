#include "verlet.h"

#define MAX_OBJECTS 4096
#define GRAVITY 9.81f

static VerletObject objects[MAX_OBJECTS];
static int numObjects = 0;

void createVerletObject(Vector2 position, float radius, float mass) {
    if (numObjects >= MAX_OBJECTS) return;
    VerletObject *ball = &objects[numObjects];
    ball->currPosition = position;
    ball->prevPosition = position;
    ball->radius = radius;
    //ball->color = color;
    numObjects++;
}

void applyForces(VerletObject *objects, int numObjects) {
    for (int i = 0; i < numObjects; i++) {
        objects[i].acceleration.y += GRAVITY * objects[i].mass;
    }
}

void updatePositions(VerletObject *objects, int numObjects, float dt) {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        Vector2 pos = obj->currPosition;
        Vector2 prev = obj->prevPosition;
        Vector2 new = (Vector2){0,0};

        aPlyScalar(2, pos);
        subtractVectors(new, pos, prev);
        aPlyScalar(dt * dt ,obj->acceleration);
        addVectors(new, pos, obj->acceleration);
        
        obj->prevPosition = pos;
        obj->currPosition = new;
    }
}

void applyConstraints(VerletObject *objects, int numObjects, float width, float height) {
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

void simulate(VerletObject *objects, int numObjects, float dt, float w, float h) {
    aPlyForces(objects, numObjects);
    updatePositions(objects, numObjects, dt);
    aPlyConstraints(objects, numObjects, w, h);
}
