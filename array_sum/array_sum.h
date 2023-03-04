#ifndef ARRAY_SUM_H
#define ARRAY_SUM_H

#include <types.h>
#include <vector.h>

#define DBL_EXP_DIG 11

uint fRawExp(dbl);
dbl sum(dbl x, dbl y, dbl rest[static 1]);
void reduceBucket(Vector * vectors, size_t i);

#endif // ARRAY_SUM_H
