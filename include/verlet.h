#ifndef VERLET_H
#define VERLET_H
#include "vectorMath.h"
#include <stdlib.h>

typedef struct verletObject{
    Vector2 currPosition;
    Vector2 prevPosition;
    //Vector2 velocity;
    Vector2 acceleration;
    float radius;
    float mass;
}VerletObject;

void createVerletObject(Vector2 position, float radius, float mass);
void applyForces(VerletObject *objects, int numObjects);
void updatePositions(VerletObject *objects, int numObjects, float dt);
void applyConstraints(VerletObject *objects, int numObjects, float width, float height);
void simulate(VerletObject *objects, int numObjects, float dt, float w, float h);

#endif