#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"
#include "vector.h"

#define DEFINE_QUEUE(T)\
        typedef struct{\
            vec_##T data;\
        } queue_##T;\
        \
        static inline void queue_##T##_init(queue_##T *q){\
            vec_##T##_init(&q->data);\
        }\
        \
    static inline void queue_##T##_enqueue(queue_##T *q,T item){\
        vec_##T##_push(&q->data,item);\
    }\
    \
    /* Dequeue: remove element from the front */ \
    static inline T queue_##T##_dequeue(queue_##T *q) { \
        if (q->data.len == 0) { \
            fprintf(stderr, "Queue underflow\n"); \
            T tmp = {0}; \
            return tmp; \
        } \
        T val = vec_##T##_get(&q->data, 0); \
        vec_##T##_remove(&q->data, 0); \
        return val; \
    } \
    \
    /* Front element */ \
    static inline T queue_##T##_front(queue_##T *q) { \
        if (q->data.len == 0) { \
            fprintf(stderr, "Queue is empty\n"); \
            T tmp = {0}; \
            return tmp; \
        } \
        return vec_##T##_get(&q->data, 0); \
    } \
    \
    /* Rear element */ \
    static inline T queue_##T##_rear(queue_##T *q) { \
        if (q->data.len == 0) { \
            fprintf(stderr, "Queue is empty\n"); \
            T tmp = {0}; \
            return tmp; \
        } \
        return vec_##T##_get(&q->data, q->data.len - 1); \
    } \
    \
    static inline size_t queue_##T##_size(queue_##T *q) { \
        return q->data.len; \
    } \
    \
    static inline int queue_##T##_empty(queue_##T *q) { \
        return q->data.len == 0; \
    } \
    \
    static inline void queue_##T##_free(queue_##T *q) { \
        vec_##T##_free(&q->data); \
    }

#endif