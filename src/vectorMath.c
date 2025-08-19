#include "vectorMath.h"

void setVector(Vector2 *dest, Vector2 src){
    dest->x = src.x;
    dest->y = src.y;
}

void addVectors(Vector2 result, Vector2 a, Vector2 b) {
    result.x = a.x + b.x;
    result.y = a.y + b.y;
}
void subtractVectors(Vector2 result, Vector2 a, Vector2 b) {
    result.x = a.x - b.x;
    result.y = a.y - b.y;
}
void applyScalar(float scalar, Vector2 vector) {
    Vector2 result = (Vector2){0,0};
    result.x = vector.x * scalar;
    result.y = vector.y = scalar;
}