#include "collision.h"

void clearGrid() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            grid.cellCounts[x][y] = 0;
        }
    }
}
void assignObjectsToGrid() {
    // Implementation of assigning objects to the grid
}
void checkCollisions() {
    // Implementation of checking collisions
}
void resolveCollision(VerletObject *a, VerletObject *b) {
    // Implementation of resolving collision between two objects
}
