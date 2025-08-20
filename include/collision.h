#ifndef COLLISION_H
#define COLLISION_H

#include "verlet.h"

#define GRID_CELL_SIZE 40
#define GRID_WIDTH (1280 / GRID_CELL_SIZE)
#define GRID_HEIGHT (720 / GRID_CELL_SIZE)

typedef struct {
    VerletObject *cells[GRID_WIDTH][GRID_HEIGHT][MAX_OBJECTS];
    int cellCounts[GRID_WIDTH][GRID_HEIGHT];
}Grid;

Grid grid;

void clearGrid();
void assignObjectsToGrid();
void checkCollisions();
void resolveCollision(VerletObject *a, VerletObject *b);

#endif