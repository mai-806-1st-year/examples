#include <assert.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "array_sum.h"

static void fRawExpTest(void);

int main(void) {
    fRawExpTest();
    return 0;
}

static void fRawExpTest(void) {
    assert(fRawExp(0.0) == 0);
    assert(fRawExp(DBL_TRUE_MIN) == 0);
    assert(fRawExp(DBL_TRUE_MIN * 2.0) == 0);
    assert(fRawExp(DBL_TRUE_MIN * 4.0) == 0);
    assert(fRawExp(DBL_MIN)            == 1);
    assert(fRawExp(DBL_MIN * 2.0)      == 2);
    assert(fRawExp(DBL_MIN * 4.0)      == 3);
    assert(fRawExp(DBL_MIN * 8.0)      == 4);
    assert(fRawExp(0.5)                == (1U << (DBL_EXP_DIG - 1)) - 2);
    assert(fRawExp(0.75)               == (1U << (DBL_EXP_DIG - 1)) - 2);
    assert(fRawExp(1.0)                == (1U << (DBL_EXP_DIG - 1)) - 1);
    assert(fRawExp(1.5)                == (1U << (DBL_EXP_DIG - 1)) - 1);
    assert(fRawExp(2.0)                == 1U << (DBL_EXP_DIG - 1));
    assert(fRawExp(3.0)                == 1U << (DBL_EXP_DIG - 1));
    assert(fRawExp(4.0)                == (1U << (DBL_EXP_DIG - 1)) + 1);
    assert(fRawExp(6.0)                == (1U << (DBL_EXP_DIG - 1)) + 1);
    assert(fRawExp(8.0)                == (1U << (DBL_EXP_DIG - 1)) + 2);
    assert(fRawExp(12.0)               == (1U << (DBL_EXP_DIG - 1)) + 2);
    assert(fRawExp(DBL_MAX)            == (1U << (DBL_EXP_DIG)) - 2);
    assert(fRawExp(HUGE_VAL)           == (1U << (DBL_EXP_DIG)) - 1);
}
