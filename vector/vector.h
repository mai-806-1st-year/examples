#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    dbl *data;
    size_t capacity, size;
} Vector;

int vectorBack(const Vector *vector, dbl *value);

size_t vectorCapacity(const Vector *vector);

void vectorCreate(Vector *vector);

dbl *vectorData(const Vector *vector);

int vectorPopBack(Vector *vector);

int vectorPushBack(Vector *vector, dbl value);

int vectorResize(Vector *vector, size_t newSize, dbl value);

size_t vectorSize(const Vector *vector);

void vectorDestroy(Vector *vector);

#endif // VECTOR_H
