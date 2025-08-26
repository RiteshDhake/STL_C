#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFINE_LIST(T, Name) \
struct Name##Node { \
    T data; \
    struct Name##Node *next; \
    struct Name##Node *prev; \
}; \
typedef struct Name##Node Name##Node; \
\
struct Name { \
    Name##Node *head; \
    Name##Node *tail; \
    size_t size; \
}; \
typedef struct Name Name; \
\
static inline void Name##_init(Name *l) { \
    l->head = l->tail = NULL; \
    l->size = 0; \
} \
\
static inline size_t Name##_size(const Name *l) { return l->size; } \
static inline bool Name##_empty(const Name *l) { return l->size == 0; } \
\
static inline void Name##_push_back(Name *l, T val) { \
    Name##Node *node = malloc(sizeof(Name##Node)); \
    if (!node) { perror("malloc"); exit(1);} \
    node->data = val; \
    node->next = NULL; \
    node->prev = l->tail; \
    if (l->tail) l->tail->next = node; \
    else l->head = node; \
    l->tail = node; \
    l->size++; \
} \
\
static inline void Name##_push_front(Name *l, T val) { \
    Name##Node *node = malloc(sizeof(Name##Node)); \
    if (!node) { perror("malloc"); exit(1);} \
    node->data = val; \
    node->prev = NULL; \
    node->next = l->head; \
    if (l->head) l->head->prev = node; \
    else l->tail = node; \
    l->head = node; \
    l->size++; \
} \
\
static inline T Name##_pop_back(Name *l) { \
    if (!l->tail) { fprintf(stderr, "pop_back on empty list\\n"); exit(1);} \
    Name##Node *tmp = l->tail; \
    T val = tmp->data; \
    l->tail = tmp->prev; \
    if (l->tail) l->tail->next = NULL; \
    else l->head = NULL; \
    free(tmp); \
    l->size--; \
    return val; \
} \
\
static inline T Name##_pop_front(Name *l) { \
    if (!l->head) { fprintf(stderr, "pop_front on empty list\\n"); exit(1);} \
    Name##Node *tmp = l->head; \
    T val = tmp->data; \
    l->head = tmp->next; \
    if (l->head) l->head->prev = NULL; \
    else l->tail = NULL; \
    free(tmp); \
    l->size--; \
    return val; \
} \
\
static inline void Name##_clear(Name *l) { \
    Name##Node *cur = l->head; \
    while (cur) { \
        Name##Node *next = cur->next; \
        free(cur); \
        cur = next; \
    } \
    l->head = l->tail = NULL; \
    l->size = 0; \
}

#endif // LIST_H
