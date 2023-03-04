#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "types.h"
#include "vector.h"

static int newCapacity(size_t capacity);

int vectorBack(const Vector * const vector, dbl * const value) {
    if (vector->size == 0)
        return EINVAL;
    *value = vector->data[vector->size - 1];
    return 0;
}

size_t vectorCapacity(const Vector * const vector) {
    return vector->capacity;
}

int vectorCreate(Vector * vector) {
    vector->data = NULL;
    vector->capacity = vector->size = 0;
    return 0;
}

dbl *vectorData(const Vector * const vector) {
    return vector->data;
}

void vectorDestroy(Vector * vector) {
    free(vector->data);
}

int vectorPushBack(Vector * vector, const dbl value) {
    assert(vector->capacity >= vector->size);
    if (vector->capacity == vector->size) {
        const size_t capacity = newCapacity(vector->capacity);
        dbl * const data = realloc(vector->data, capacity * sizeof(dbl));
        if (data == NULL)
            return errno;
        vector->data = data;
        vector->capacity = capacity;
    }
    assert(vector->capacity > vector->size);

    vector->data[vector->size++] = value;
    return 0;
}


int vectorPopBack(Vector * vector) {
    if (vector->size == 0)
        return EINVAL;
    --vector->size;
    return 0;
}

int vectorResize(Vector * const vector, const size_t newSize, const dbl value) {
    if (newSize <= vector->size) {
        vector->size = newSize;
        return 0;
    }
    assert(newSize > vector->size);
    if (newSize <= vector->capacity) {
        while (vector->size < newSize)
            vector->data[vector->size++] = value;
        return 0;
    }
    assert(newSize > vector->capacity);
    dbl * const data = realloc(vector->data, newSize * sizeof(dbl));
    if (data == NULL)
        return errno;
    vector->data = data;
    vector->capacity = newSize;
    while (vector->size < newSize)
        vector->data[vector->size++] = value;
    return 0;
}

size_t vectorSize(const Vector * const vector) {
    return vector->size;
}

static int newCapacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}
