#ifndef STACK_H
#define STACK_H

#include "common.h"
#include "vector.h"

#define DEFINE_STACK(T) \
    typedef struct { \
        vec_##T data; \
    } stack_##T; \
    \
    static inline void stack_##T##_init(stack_##T *s) { \
        vec_##T##_init(&s->data); \
    } \
    \
    static inline void stack_##T##_push(stack_##T *s, T value) { \
        vec_##T##_push(&s->data, value); \
    } \
    \
    static inline T stack_##T##_pop(stack_##T *s) { \
        if (s->data.len == 0) { \
            printf("Stack underflow\n"); \
            T tmp = {0}; \
            return tmp; \
        } \
        T value = s->data.data[s->data.len - 1]; \
        s->data.len--; \
        \
        /* Shrink if necessary */ \
        if (s->data.len > 0 && s->data.len <= s->data.cap / 4) { \
            size_t new_cap = s->data.cap / 2; \
            if (new_cap < 4) new_cap = 4; \
            T *new_data = realloc(s->data.data, new_cap * sizeof(T)); \
            if (new_data) { \
                s->data.data = new_data; \
                s->data.cap = new_cap; \
            } \
        } \
        \
        return value; \
    } \
    \
    static inline T stack_##T##_peek(stack_##T *s) { \
        if (s->data.len == 0) { \
            printf("Stack is empty\n"); \
            T tmp = {0}; \
            return tmp; \
        } \
        return s->data.data[s->data.len - 1]; \
    } \
    \
    static inline T stack_##T##_top(stack_##T *s) { \
        return stack_##T##_peek(s); \
    } \
    \
    static inline int stack_##T##_empty(stack_##T *s) { \
        return s->data.len == 0; \
    } \
    \
    static inline size_t stack_##T##_size(stack_##T *s) { \
        return s->data.len; \
    } \
    \
    static inline void stack_##T##_free(stack_##T *s) { \
        vec_##T##_free(&s->data); \
    }

#endif