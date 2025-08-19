#ifndef VECTOR_MATH
#define VECTOR_MATH
#include <math.h>

typedef struct {
    float x;
    float y;
}Vector2;

void setVector(Vector2 *dest, Vector2 src);
void addVectors(Vector2 result, Vector2 a, Vector2 b);
void subtractVectors(Vector2 result, Vector2 a, Vector2 b);
void applyScalar(float scalar, Vector2 vector);

#endif