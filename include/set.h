#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Helper macro to create unique names
#define CONCAT(a, b) a##_##b
#define MAKE_NAME(prefix, type) CONCAT(prefix, type)

// For primitive types that support <, >, == operators
#define DEFINE_SET(T, TYPE_NAME, FORMAT) \
typedef struct MAKE_NAME(SetNode, TYPE_NAME) { \
    T data; \
    struct MAKE_NAME(SetNode, TYPE_NAME)* left; \
    struct MAKE_NAME(SetNode, TYPE_NAME)* right; \
} MAKE_NAME(SetNode, TYPE_NAME); \
\
typedef struct { \
    MAKE_NAME(SetNode, TYPE_NAME)* root; \
    size_t size; \
} MAKE_NAME(Set, TYPE_NAME); \
\
static inline MAKE_NAME(SetNode, TYPE_NAME)* MAKE_NAME(create_node, TYPE_NAME)(T val) { \
    MAKE_NAME(SetNode, TYPE_NAME)* n = (MAKE_NAME(SetNode, TYPE_NAME)*)malloc(sizeof(MAKE_NAME(SetNode, TYPE_NAME))); \
    n->data = val; \
    n->left = n->right = NULL; \
    return n; \
} \
\
static inline MAKE_NAME(SetNode, TYPE_NAME)* MAKE_NAME(insert_node, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root, T data) { \
    if (!root) return MAKE_NAME(create_node, TYPE_NAME)(data); \
    if (data < root->data) root->left = MAKE_NAME(insert_node, TYPE_NAME)(root->left, data); \
    else if (data > root->data) root->right = MAKE_NAME(insert_node, TYPE_NAME)(root->right, data); \
    return root; \
} \
\
static inline bool MAKE_NAME(node_contains, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root, T data) { \
    if (!root) return false; \
    if (root->data == data) return true; \
    return (data < root->data) ? MAKE_NAME(node_contains, TYPE_NAME)(root->left, data) : MAKE_NAME(node_contains, TYPE_NAME)(root->right, data); \
} \
\
static inline void MAKE_NAME(print_inorder, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root) { \
    if (!root) return; \
    MAKE_NAME(print_inorder, TYPE_NAME)(root->left); \
    printf(FORMAT " ", root->data); \
    MAKE_NAME(print_inorder, TYPE_NAME)(root->right); \
} \
\
static inline void MAKE_NAME(set_init, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s) { \
    s->root = NULL; \
    s->size = 0; \
} \
\
static inline void MAKE_NAME(set_add, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s, T data) { \
    if (!MAKE_NAME(node_contains, TYPE_NAME)(s->root, data)) { \
        s->root = MAKE_NAME(insert_node, TYPE_NAME)(s->root, data); \
        s->size++; \
    } \
} \
\
static inline bool MAKE_NAME(set_contains, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s, T data) { \
    return MAKE_NAME(node_contains, TYPE_NAME)(s->root, data); \
} \
\
static inline void MAKE_NAME(set_display, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s) { \
    printf("{ "); \
    MAKE_NAME(print_inorder, TYPE_NAME)(s->root); \
    printf("}\n"); \
} \
\
static inline void MAKE_NAME(node_to_array, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root, T* arr, size_t* idx) { \
    if (!root) return; \
    MAKE_NAME(node_to_array, TYPE_NAME)(root->left, arr, idx); \
    arr[(*idx)++] = root->data; \
    MAKE_NAME(node_to_array, TYPE_NAME)(root->right, arr, idx); \
} \
\
static inline MAKE_NAME(Set, TYPE_NAME) MAKE_NAME(set_union, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    MAKE_NAME(Set, TYPE_NAME) result; \
    MAKE_NAME(set_init, TYPE_NAME)(&result); \
    size_t i = 0; \
    T* arrA = (T*)malloc(sizeof(T) * A->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arrA, &i); \
    for (size_t j = 0; j < i; j++) MAKE_NAME(set_add, TYPE_NAME)(&result, arrA[j]); \
    free(arrA); \
    i = 0; \
    T* arrB = (T*)malloc(sizeof(T) * B->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(B->root, arrB, &i); \
    for (size_t j = 0; j < i; j++) MAKE_NAME(set_add, TYPE_NAME)(&result, arrB[j]); \
    free(arrB); \
    return result; \
} \
\
static inline MAKE_NAME(Set, TYPE_NAME) MAKE_NAME(set_intersection, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    MAKE_NAME(Set, TYPE_NAME) result; \
    MAKE_NAME(set_init, TYPE_NAME)(&result); \
    size_t i = 0; \
    T* arrA = (T*)malloc(sizeof(T) * A->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arrA, &i); \
    for (size_t j = 0; j < i; j++) \
        if (MAKE_NAME(set_contains, TYPE_NAME)(B, arrA[j])) MAKE_NAME(set_add, TYPE_NAME)(&result, arrA[j]); \
    free(arrA); \
    return result; \
} \
\
static inline MAKE_NAME(Set, TYPE_NAME) MAKE_NAME(set_difference, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    MAKE_NAME(Set, TYPE_NAME) result; \
    MAKE_NAME(set_init, TYPE_NAME)(&result); \
    size_t i = 0; \
    T* arrA = (T*)malloc(sizeof(T) * A->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arrA, &i); \
    for (size_t j = 0; j < i; j++) \
        if (!MAKE_NAME(set_contains, TYPE_NAME)(B, arrA[j])) MAKE_NAME(set_add, TYPE_NAME)(&result, arrA[j]); \
    free(arrA); \
    return result; \
} \
\
static inline bool MAKE_NAME(set_is_subset, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    size_t i = 0; \
    T* arrA = (T*)malloc(sizeof(T) * A->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arrA, &i); \
    for (size_t j = 0; j < i; j++) \
        if (!MAKE_NAME(set_contains, TYPE_NAME)(B, arrA[j])) { free(arrA); return false; } \
    free(arrA); \
    return true; \
} \
\
static inline bool MAKE_NAME(set_is_equal, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    return (A->size == B->size) && MAKE_NAME(set_is_subset, TYPE_NAME)(A, B); \
} \
\
static inline void MAKE_NAME(set_power_set, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A) { \
    size_t i = 0; \
    T* arr = (T*)malloc(sizeof(T) * A->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arr, &i); \
    size_t total_subsets = 1ULL << i; \
    for (size_t mask = 0; mask < total_subsets; mask++) { \
        printf("{ "); \
        for (size_t j = 0; j < i; j++) \
            if (mask & (1ULL << j)) printf(FORMAT " ", arr[j]); \
        printf("}\n"); \
    } \
    free(arr); \
} \
\
static inline void MAKE_NAME(set_cartesian_product, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* A, MAKE_NAME(Set, TYPE_NAME)* B) { \
    size_t i = 0, j = 0; \
    T* arrA = (T*)malloc(sizeof(T) * A->size); \
    T* arrB = (T*)malloc(sizeof(T) * B->size); \
    MAKE_NAME(node_to_array, TYPE_NAME)(A->root, arrA, &i); \
    MAKE_NAME(node_to_array, TYPE_NAME)(B->root, arrB, &j); \
    printf("{ "); \
    for (size_t x = 0; x < i; x++) { \
        for (size_t y = 0; y < j; y++) { \
            printf("(" FORMAT "," FORMAT ") ", arrA[x], arrB[y]); \
        } \
    } \
    printf("}\n"); \
    free(arrA); free(arrB); \
}

// For complex types like structs that need custom comparison and printing
#define DEFINE_SET_CUSTOM(T, TYPE_NAME, CMP_FUNC, EQ_FUNC, PRINT_FUNC) \
typedef struct MAKE_NAME(SetNode, TYPE_NAME) { \
    T data; \
    struct MAKE_NAME(SetNode, TYPE_NAME)* left; \
    struct MAKE_NAME(SetNode, TYPE_NAME)* right; \
} MAKE_NAME(SetNode, TYPE_NAME); \
\
typedef struct { \
    MAKE_NAME(SetNode, TYPE_NAME)* root; \
    size_t size; \
} MAKE_NAME(Set, TYPE_NAME); \
\
static inline MAKE_NAME(SetNode, TYPE_NAME)* MAKE_NAME(create_node, TYPE_NAME)(T val) { \
    MAKE_NAME(SetNode, TYPE_NAME)* n = (MAKE_NAME(SetNode, TYPE_NAME)*)malloc(sizeof(MAKE_NAME(SetNode, TYPE_NAME))); \
    n->data = val; \
    n->left = n->right = NULL; \
    return n; \
} \
\
static inline MAKE_NAME(SetNode, TYPE_NAME)* MAKE_NAME(insert_node, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root, T data) { \
    if (!root) return MAKE_NAME(create_node, TYPE_NAME)(data); \
    if (CMP_FUNC(data, root->data) < 0) root->left = MAKE_NAME(insert_node, TYPE_NAME)(root->left, data); \
    else if (!EQ_FUNC(data, root->data)) root->right = MAKE_NAME(insert_node, TYPE_NAME)(root->right, data); \
    return root; \
} \
\
static inline bool MAKE_NAME(node_contains, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root, T data) { \
    if (!root) return false; \
    if (EQ_FUNC(root->data, data)) return true; \
    return (CMP_FUNC(data, root->data) < 0) ? MAKE_NAME(node_contains, TYPE_NAME)(root->left, data) : MAKE_NAME(node_contains, TYPE_NAME)(root->right, data); \
} \
\
static inline void MAKE_NAME(print_inorder, TYPE_NAME)(MAKE_NAME(SetNode, TYPE_NAME)* root) { \
    if (!root) return; \
    MAKE_NAME(print_inorder, TYPE_NAME)(root->left); \
    PRINT_FUNC(root->data); \
    printf(" "); \
    MAKE_NAME(print_inorder, TYPE_NAME)(root->right); \
} \
\
static inline void MAKE_NAME(set_init, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s) { \
    s->root = NULL; \
    s->size = 0; \
} \
\
static inline void MAKE_NAME(set_add, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s, T data) { \
    if (!MAKE_NAME(node_contains, TYPE_NAME)(s->root, data)) { \
        s->root = MAKE_NAME(insert_node, TYPE_NAME)(s->root, data); \
        s->size++; \
    } \
} \
\
static inline bool MAKE_NAME(set_contains, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s, T data) { \
    return MAKE_NAME(node_contains, TYPE_NAME)(s->root, data); \
} \
\
static inline void MAKE_NAME(set_display, TYPE_NAME)(MAKE_NAME(Set, TYPE_NAME)* s) { \
    printf("{ "); \
    MAKE_NAME(print_inorder, TYPE_NAME)(s->root); \
    printf("}\n"); \
}

#endif