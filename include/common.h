#ifndef COMMON_H
#define COMMON_H

/*
 * Common header for STL-for-C
 * Universal version using include guards
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <errno.h>

/* Handy macros */
#define UNUSED(x) (void)(x)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif // COMMON_H
