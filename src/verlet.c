#include "verlet.h"
#define GRAVITY 20.0f

static VerletObject objects[MAX_OBJECTS];
static int numObjects = 0;

void createVerletObject(Vector2 position, Vector2 velocity, float radius, float mass, SDL_Renderer *renderer) {
    if (numObjects >= MAX_OBJECTS) return;
    VerletObject *ball = &objects[numObjects];
    ball->renderer = renderer;
    ball->currPosition = position;
    ball->velocity = velocity; // Assign the velocity parameter to ball->velocity
    if (ball->velocity.x != 0 || ball->velocity.y != 0) {
        ball->prevPosition = (Vector2){
            position.x - ball->velocity.x * 0.1f,
            position.y - ball->velocity.y * 0.1f
        };
        printf("Velocity set: (%f, %f)\n", ball->velocity.x, ball->velocity.y);
    } else {
        ball->prevPosition = position;
    }
    ball->radius = radius;
    ball->mass = 1;
    ball->acceleration = (Vector2){0, 0};
    //ball->color = color;
    numObjects++;
}

void applyGravity() {
    for (int i = 0; i < numObjects; i++) {
        objects[i].acceleration.y = GRAVITY;
    }
}

void updatePositions(float dt) {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        Vector2 pos = obj->currPosition;
        Vector2 prev = obj->prevPosition;
        Vector2 new = (Vector2){0,0};
        applyGravity();

        new.x = pos.x + (pos.x - prev.x) + obj->acceleration.x * dt * dt;
        new.y = pos.y + (pos.y - prev.y) + obj->acceleration.y * dt * dt;
        
        obj->prevPosition = pos;
        obj->currPosition = new;
    }

    applyConstraints(1280, 720);
}

void applyConstraints(float width, float height) {
    float damping = 0.9f; // Damping factor for energy loss during collision

    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];

        // Right boundary
        if (obj->currPosition.x + obj->radius >= width) {
            printf("Right boundary hit\n");
            float disp = obj->currPosition.x - obj->prevPosition.x;
            obj->currPosition.x = width - obj->radius; // Clamp to boundary
            obj->prevPosition.x = obj->currPosition.x + disp * damping; // Reverse and dampen velocity
        }

        // Left boundary
        if (obj->currPosition.x - obj->radius <= 0) {
            printf("Left boundary hit\n");
            float disp = obj->currPosition.x - obj->prevPosition.x;
            obj->currPosition.x = obj->radius; // Clamp to boundary
            obj->prevPosition.x = obj->currPosition.x + disp * damping; // Reverse and dampen velocity
        }

        // Bottom boundary
        if (obj->currPosition.y + obj->radius >= height) {
            printf("Bottom boundary hit\n");
            float disp = obj->currPosition.y - obj->prevPosition.y;
            obj->currPosition.y = height - obj->radius; // Clamp to boundary
            obj->prevPosition.y = obj->currPosition.y + disp * damping; // Reverse and dampen velocity
        }

        // Top boundary
        if (obj->currPosition.y - obj->radius <= 0) {
            printf("Top boundary hit\n");
            float disp = obj->currPosition.y - obj->prevPosition.y;
            obj->currPosition.y = obj->radius; // Clamp to boundary
            obj->prevPosition.y = obj->currPosition.y + disp * damping; // Reverse and dampen velocity
        }
    }
}

void drawVerlets() {
    for (int i = 0; i < numObjects; i++) {
        VerletObject *obj = &objects[i];
        SDL_SetRenderDrawColor(obj->renderer, 0,0,33, SDL_ALPHA_OPAQUE);
        filledCircleRGBA(obj->renderer, 
            (int)obj->currPosition.x, 
            (int)obj->currPosition.y, 
            (int)obj->radius, 
            0, 200, 100, SDL_ALPHA_OPAQUE);
    }
}

