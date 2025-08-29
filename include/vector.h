#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

#define DEFINE_VEC(T) \
typedef struct { \
 T *data; \
size_t cap; \
size_t len; \
 } vec_##T; \
\
static inline void vec_##T##_init(vec_##T *v) { \
 v->len = 0; \
 v->cap = 0; \
 v->data = NULL; \
 } \
\
static inline void vec_##T##_push(vec_##T *v, T val) { \
if (v->len >= v->cap) { \
size_t new_cap = (v->cap == 0) ? 4 : v->cap * 2; \
 T *new_data = realloc(v->data, new_cap * sizeof(T)); \
if (!new_data) { \
printf("Memory allocation failed\n"); \
return; \
 } \
 v->data = new_data; \
 v->cap = new_cap; \
 } \
 v->data[v->len++] = val; \
 } \
\
static inline T vec_##T##_get(vec_##T *v, size_t i) { \
if (i >= v->len) { \
printf("Invalid index %zu\n", i); \
 T tmp = {0}; return tmp; \
 } \
return v->data[i]; \
 } \
\
static inline void vec_##T##_set(vec_##T *v, size_t i, T item) { \
if (i >= v->len) { \
printf("Index out of bounds\n"); \
return; \
 } \
 v->data[i] = item; \
 } \
\
static inline void vec_##T##_insert(vec_##T *v, size_t i, T item) { \
if (i > v->len) { \
printf("Index out of bounds\n"); \
return; \
 } \
if (v->len >= v->cap) { \
size_t new_cap = (v->cap == 0) ? 4 : v->cap * 2; \
 T *new_data = realloc(v->data, new_cap * sizeof(T)); \
if (!new_data) { \
printf("Memory allocation failed\n"); \
return; \
 } \
 v->data = new_data; \
 v->cap = new_cap; \
 } \
for (size_t j = v->len; j > i; j--) { \
 v->data[j] = v->data[j - 1]; \
 } \
 v->data[i] = item; \
 v->len++; \
 } \
\
static inline void vec_##T##_remove(vec_##T *v, size_t i) { \
if (i >= v->len) { \
printf("Index out of bounds\n"); \
return; \
 } \
for (size_t j = i; j < v->len - 1; j++) { \
 v->data[j] = v->data[j + 1]; \
 } \
 v->len--; \
if (v->len > 0 && v->len <= v->cap / 4) { \
size_t new_cap = v->cap / 2; \
if (new_cap < 4) new_cap = 4; \
 T *new_data = realloc(v->data, new_cap * sizeof(T)); \
if (new_data) { \
 v->data = new_data; \
 v->cap = new_cap; \
 } \
 } \
 } \
\
static inline void vec_##T##_free(vec_##T *v) { \
free(v->data); \
 v->data = NULL; \
 v->len = 0; \
 v->cap = 0; \
 }
#endif