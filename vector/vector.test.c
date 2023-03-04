#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "types.h"
#include "vector.h"

static void vectorBackPopBackTest(void);
static void vectorCreateDestroyTest(void);
static void vectorPushBackTest(void);
static void vectorResizeTest(void);

int main(void) {
    vectorBackPopBackTest();
    vectorCreateDestroyTest();
    vectorPushBackTest();
    vectorResizeTest();
    return 0;
}

static void vectorBackPopBackTest(void) {
    Vector vector;
    vectorCreate(&vector);

    vectorResize(&vector, 10, 0.0);
    for (size_t i = 0; i < vector.size; ++i)
        vector.data[i] = -(dbl) i - 1.0;
    const dbl *data = vector.data;
    const size_t capacity = vector.capacity;
    while (vector.size != 0) {
        dbl value;
        assert(vectorBack(&vector, &value) == 0);
        assert(value == -(dbl) vector.size);

        const size_t oldSize = vector.size;
        assert(vectorPopBack(&vector) == 0);
        assert(vector.data == data && vector.capacity == capacity &&
            vector.size == oldSize - 1);
    }

    vectorDestroy(&vector);
}

static void vectorCreateDestroyTest(void) {
    Vector vector;
    assert(vectorCreate(&vector) == 0);
    assert(vector.data == NULL && vector.capacity == 0 && vector.size == 0);
    vectorDestroy(&vector);
}

static void vectorPushBackTest(void) {
    Vector vector;
    assert(vectorCreate(&vector) == 0);

    assert(vectorPushBack(&vector, 0.0) == 0);
    assert(vector.data != NULL && vector.capacity == 1 && vector.size == 1);
    for (size_t i = 0; i < 1; ++i)
        assert(vector.data[i] == (dbl) i);

    assert(vectorPushBack(&vector, 1.0) == 0);
    assert(vector.data != NULL && vector.capacity == 2 && vector.size == 2);
    for (size_t i = 0; i < 2; ++i)
        assert(vector.data[i] == (dbl) i);

    assert(vectorPushBack(&vector, 2.0) == 0);
    assert(vector.data != NULL && vector.capacity == 4 && vector.size == 3);
    for (size_t i = 0; i < 3; ++i)
        assert(vector.data[i] == (dbl) i);

    assert(vectorPushBack(&vector, 3.0) == 0);
    assert(vector.data != NULL && vector.capacity == 4 && vector.size == 4);
    for (size_t i = 0; i < 4; ++i)
        assert(vector.data[i] == (dbl) i);

    assert(vectorPushBack(&vector, 4.0) == 0);
    assert(vector.data != NULL && vector.capacity == 8 && vector.size == 5);
    for (size_t i = 0; i < 5; ++i)
        assert(vector.data[i] == (dbl) i);

    vectorDestroy(&vector);
}

static void vectorResizeTest(void) {
    Vector vector;
    vectorCreate(&vector);

    assert(vectorResize(&vector, 5, 1.0) == 0);
    assert(vector.data != NULL && vector.capacity == 5 && vector.size == 5);
    for (size_t i = 0; i < vector.capacity; ++i)
        assert(vector.data[i] == 1.0);

    assert(vectorResize(&vector, 10, 1.5) == 0);
    assert(vector.data != NULL && vector.capacity == 10 && vector.size == 10);
    for (size_t i = 0; i < vector.capacity; ++i)
        if (i < 5)
            assert(vector.data[i] == 1.0);
        else
            assert(vector.data[i] == 1.5);

    assert(vectorResize(&vector, 3, 0.0) == 0);
    assert(vector.data != NULL && vector.capacity == 10 && vector.size == 3);
    for (size_t i = 0; i < vector.capacity; ++i)
        if (i < 5)
            assert(vector.data[i] == 1.0);
        else
            assert(vector.data[i] == 1.5);

    assert(vectorResize(&vector, 15, 3.0) == 0);
    assert(vector.data != NULL && vector.capacity == 15 && vector.size == 15);
    for (size_t i = 0; i < vector.capacity; ++i)
        if (i < 3)
            assert(vector.data[i] == 1.0);
        else
            assert(vector.data[i] == 3.0);

    vectorDestroy(&vector);
}
