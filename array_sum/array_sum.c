#include <float.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <array_sum.h>
#include <vector.h>

int arraySum(
    const size_t size,
    const dbl ptr[static size],
    dbl * const result
) {
    const size_t n = 1U << DBL_EXP_DIG;
    Vector *vectors = malloc((1U << DBL_EXP_DIG) * sizeof(Vector));
    if (vectors == NULL)
        return errno;
    for (size_t i = 0; i < n; ++i)
        vectorCreate(vectors + i);

    for (size_t i = 0; i < size; ++i) {
        const dbl value = ptr[i];
        vectorPushBack(vectors + fRawExp(value), value);
    }

    /* может зациклиться, подмать почему и исправить */
    for (size_t i = 0; i < n; ++i)
        while (vectorSize(vectors + i) >= 2)
            reduceBucket(vectors, i);

    for (size_t i = 0; i < n; ++i)
        vectorDestroy(vectors + i);

    *result = 0.0; // исправить

    return 0;
}

void reduceBucket(Vector * const vectors, const size_t i) {
    if (vectorSize(vectors + i) < 2)
        return;

    dbl x, y;
    vectorBack(vectors + i, &x);
    vectorPopBack(vectors + i);
    vectorBack(vectors + i, &y);
    vectorPopBack(vectors + i);

    dbl rest;
    vectorPushBack(vectors + i + 1, sum(x, y, &rest));
    vectorPushBack(vectors + i /* подумать (-52) рядом */, rest);
}

dbl sum(const dbl x, const dbl y, dbl rest[static 1]) {
    *rest = 0.0 /* СДЕЛАТЬ: хвост */;
    return x + y /* СДЕЛАТЬ: сумма */;
}

uint fRawExp(const dbl value) {
    union {
        uint64_t u64;
        dbl d;
    } exchange = { .d = value };
    return (exchange.u64 >> (DBL_MANT_DIG - 1)) & ((1U << DBL_EXP_DIG) - 1);
}
