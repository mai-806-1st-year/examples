#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "types.h"
#include "vector.h"

int main(void) {
    size_t n;
    scanf("%zu", &n);

    Vector vector;
    vectorCreate(&vector);
    if (vectorResize(&vector, n, 0.0) != 0) {
        perror("vectorResize");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < vectorSize(&vector); ++i)
        scanf("%lf", vectorData(&vector) + i);

    printf("capacity = %zu, size = %zu\n",
        vectorCapacity(&vector), vectorSize(&vector));
    for (size_t i = 0; i < vectorSize(&vector); ++i)
        printf("%lf ", vectorData(&vector)[i]);
    printf("\n");

    dbl value = 1.0;
    while (value != 0.0) {
        scanf("%lf", &value);
        vectorPushBack(&vector, value);
        printf("capacity = %zu, size = %zu\n",
            vectorCapacity(&vector), vectorSize(&vector));
        for (size_t i = 0; i < vectorSize(&vector); ++i)
            printf("%lf ", vectorData(&vector)[i]);
        printf("\n");
    }

    vectorDestroy(&vector);

    return 0;
}
