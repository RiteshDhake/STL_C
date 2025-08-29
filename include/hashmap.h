#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define HASHMAP_INITIAL_CAPACITY 16
#define HASHMAP_LOAD_FACTOR 0.75

// Helper macro to create unique names
#define CONCAT(a, b) a##_##b
#define MAKE_NAME(prefix, type) CONCAT(prefix, type)

// Default hash functions for common types
static inline size_t hash_int(int key) {
    return (size_t)key;
}

static inline size_t hash_string(const char* key) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

static inline size_t hash_double(double key) {
    union { double d; uint64_t i; } u;
    u.d = key;
    return (size_t)u.i;
}

static inline size_t hash_float(float key) {
    union { float f; uint32_t i; } u;
    u.f = key;
    return (size_t)u.i;
}

static inline size_t hash_long(long key) {
    return (size_t)key;
}

static inline size_t hash_char(char key) {
    return (size_t)key;
}

// Helper macros for common equality checks
#define INT_EQUAL(a, b) ((a) == (b))
#define STRING_EQUAL(a, b) (strcmp((a), (b)) == 0)
#define DOUBLE_EQUAL(a, b) ((a) == (b))
#define FLOAT_EQUAL(a, b) ((a) == (b))
#define LONG_EQUAL(a, b) ((a) == (b))
#define CHAR_EQUAL(a, b) ((a) == (b))

// Convenient macros for common primitive type combinations
// For int keys
#define HASHMAP_INT_STRING DEFINE_HASHMAP(int, char*, int_string, "%d", "%s", hash_int, INT_EQUAL)
#define HASHMAP_INT_DOUBLE DEFINE_HASHMAP(int, double, int_double, "%d", "%.2f", hash_int, INT_EQUAL)
#define HASHMAP_INT_FLOAT DEFINE_HASHMAP(int, float, int_float, "%d", "%.2f", hash_int, INT_EQUAL)
#define HASHMAP_INT_LONG DEFINE_HASHMAP(int, long, int_long, "%d", "%ld", hash_int, INT_EQUAL)
#define HASHMAP_INT_CHAR DEFINE_HASHMAP(int, char, int_char, "%d", "%c", hash_int, INT_EQUAL)
#define HASHMAP_INT_INT DEFINE_HASHMAP(int, int, int_int, "%d", "%d", hash_int, INT_EQUAL)

// For string keys  
#define HASHMAP_STRING_INT DEFINE_HASHMAP(char*, int, string_int, "%s", "%d", hash_string, STRING_EQUAL)
#define HASHMAP_STRING_DOUBLE DEFINE_HASHMAP(char*, double, string_double, "%s", "%.2f", hash_string, STRING_EQUAL)
#define HASHMAP_STRING_FLOAT DEFINE_HASHMAP(char*, float, string_float, "%s", "%.2f", hash_string, STRING_EQUAL)
#define HASHMAP_STRING_LONG DEFINE_HASHMAP(char*, long, string_long, "%s", "%ld", hash_string, STRING_EQUAL)
#define HASHMAP_STRING_CHAR DEFINE_HASHMAP(char*, char, string_char, "%s", "%c", hash_string, STRING_EQUAL)
#define HASHMAP_STRING_STRING DEFINE_HASHMAP(char*, char*, string_string, "%s", "%s", hash_string, STRING_EQUAL)

// For double keys
#define HASHMAP_DOUBLE_INT DEFINE_HASHMAP(double, int, double_int, "%.2f", "%d", hash_double, DOUBLE_EQUAL)
#define HASHMAP_DOUBLE_DOUBLE DEFINE_HASHMAP(double, double, double_double, "%.2f", "%.2f", hash_double, DOUBLE_EQUAL)
#define HASHMAP_DOUBLE_FLOAT DEFINE_HASHMAP(double, float, double_float, "%.2f", "%.2f", hash_double, DOUBLE_EQUAL)
#define HASHMAP_DOUBLE_LONG DEFINE_HASHMAP(double, long, double_long, "%.2f", "%ld", hash_double, DOUBLE_EQUAL)
#define HASHMAP_DOUBLE_CHAR DEFINE_HASHMAP(double, char, double_char, "%.2f", "%c", hash_double, DOUBLE_EQUAL)
#define HASHMAP_DOUBLE_STRING DEFINE_HASHMAP(double, char*, double_string, "%.2f", "%s", hash_double, DOUBLE_EQUAL)

// For float keys
#define HASHMAP_FLOAT_INT DEFINE_HASHMAP(float, int, float_int, "%.2f", "%d", hash_float, FLOAT_EQUAL)
#define HASHMAP_FLOAT_DOUBLE DEFINE_HASHMAP(float, double, float_double, "%.2f", "%.2f", hash_float, FLOAT_EQUAL)
#define HASHMAP_FLOAT_FLOAT DEFINE_HASHMAP(float, float, float_float, "%.2f", "%.2f", hash_float, FLOAT_EQUAL)
#define HASHMAP_FLOAT_LONG DEFINE_HASHMAP(float, long, float_long, "%.2f", "%ld", hash_float, FLOAT_EQUAL)
#define HASHMAP_FLOAT_CHAR DEFINE_HASHMAP(float, char, float_char, "%.2f", "%c", hash_float, FLOAT_EQUAL)
#define HASHMAP_FLOAT_STRING DEFINE_HASHMAP(float, char*, float_string, "%.2f", "%s", hash_float, FLOAT_EQUAL)

// For long keys
#define HASHMAP_LONG_INT DEFINE_HASHMAP(long, int, long_int, "%ld", "%d", hash_long, LONG_EQUAL)
#define HASHMAP_LONG_DOUBLE DEFINE_HASHMAP(long, double, long_double, "%ld", "%.2f", hash_long, LONG_EQUAL)
#define HASHMAP_LONG_FLOAT DEFINE_HASHMAP(long, float, long_float, "%ld", "%.2f", hash_long, LONG_EQUAL)
#define HASHMAP_LONG_LONG DEFINE_HASHMAP(long, long, long_long, "%ld", "%ld", hash_long, LONG_EQUAL)
#define HASHMAP_LONG_CHAR DEFINE_HASHMAP(long, char, long_char, "%ld", "%c", hash_long, LONG_EQUAL)
#define HASHMAP_LONG_STRING DEFINE_HASHMAP(long, char*, long_string, "%ld", "%s", hash_long, LONG_EQUAL)

// For char keys
#define HASHMAP_CHAR_INT DEFINE_HASHMAP(char, int, char_int, "%c", "%d", hash_char, CHAR_EQUAL)
#define HASHMAP_CHAR_DOUBLE DEFINE_HASHMAP(char, double, char_double, "%c", "%.2f", hash_char, CHAR_EQUAL)
#define HASHMAP_CHAR_FLOAT DEFINE_HASHMAP(char, float, char_float, "%c", "%.2f", hash_char, CHAR_EQUAL)
#define HASHMAP_CHAR_LONG DEFINE_HASHMAP(char, long, char_long, "%c", "%ld", hash_char, CHAR_EQUAL)
#define HASHMAP_CHAR_CHAR DEFINE_HASHMAP(char, char, char_char, "%c", "%c", hash_char, CHAR_EQUAL)
#define HASHMAP_CHAR_STRING DEFINE_HASHMAP(char, char*, char_string, "%c", "%s", hash_char, CHAR_EQUAL)

// For primitive types with built-in hash functions
#define DEFINE_HASHMAP(K, V, TYPE_NAME, K_FORMAT, V_FORMAT, HASH_FUNC, K_EQUAL) \
typedef struct MAKE_NAME(HashNode, TYPE_NAME) { \
    K key; \
    V value; \
    struct MAKE_NAME(HashNode, TYPE_NAME)* next; \
} MAKE_NAME(HashNode, TYPE_NAME); \
\
typedef struct { \
    MAKE_NAME(HashNode, TYPE_NAME)** buckets; \
    size_t capacity; \
    size_t size; \
} MAKE_NAME(HashMap, TYPE_NAME); \
\
static inline MAKE_NAME(HashNode, TYPE_NAME)* MAKE_NAME(create_hash_node, TYPE_NAME)(K key, V value) { \
    MAKE_NAME(HashNode, TYPE_NAME)* node = (MAKE_NAME(HashNode, TYPE_NAME)*)malloc(sizeof(MAKE_NAME(HashNode, TYPE_NAME))); \
    node->key = key; \
    node->value = value; \
    node->next = NULL; \
    return node; \
} \
\
static inline void MAKE_NAME(hashmap_init, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    map->buckets = (MAKE_NAME(HashNode, TYPE_NAME)**)calloc(HASHMAP_INITIAL_CAPACITY, sizeof(MAKE_NAME(HashNode, TYPE_NAME)*)); \
    map->capacity = HASHMAP_INITIAL_CAPACITY; \
    map->size = 0; \
} \
\
static inline size_t MAKE_NAME(get_bucket_index, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    return HASH_FUNC(key) % map->capacity; \
} \
\
static inline void MAKE_NAME(hashmap_resize, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    size_t old_capacity = map->capacity; \
    MAKE_NAME(HashNode, TYPE_NAME)** old_buckets = map->buckets; \
    \
    map->capacity *= 2; \
    map->buckets = (MAKE_NAME(HashNode, TYPE_NAME)**)calloc(map->capacity, sizeof(MAKE_NAME(HashNode, TYPE_NAME)*)); \
    map->size = 0; \
    \
    for (size_t i = 0; i < old_capacity; i++) { \
        MAKE_NAME(HashNode, TYPE_NAME)* node = old_buckets[i]; \
        while (node) { \
            MAKE_NAME(HashNode, TYPE_NAME)* next = node->next; \
            size_t new_index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, node->key); \
            node->next = map->buckets[new_index]; \
            map->buckets[new_index] = node; \
            map->size++; \
            node = next; \
        } \
    } \
    free(old_buckets); \
} \
\
static inline void MAKE_NAME(hashmap_put, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key, V value) { \
    if ((double)map->size / map->capacity >= HASHMAP_LOAD_FACTOR) { \
        MAKE_NAME(hashmap_resize, TYPE_NAME)(map); \
    } \
    \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            node->value = value; \
            return; \
        } \
        node = node->next; \
    } \
    \
    MAKE_NAME(HashNode, TYPE_NAME)* new_node = MAKE_NAME(create_hash_node, TYPE_NAME)(key, value); \
    new_node->next = map->buckets[index]; \
    map->buckets[index] = new_node; \
    map->size++; \
} \
\
static inline bool MAKE_NAME(hashmap_get, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key, V* value) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            *value = node->value; \
            return true; \
        } \
        node = node->next; \
    } \
    return false; \
} \
\
static inline bool MAKE_NAME(hashmap_contains, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            return true; \
        } \
        node = node->next; \
    } \
    return false; \
} \
\
static inline bool MAKE_NAME(hashmap_remove, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    MAKE_NAME(HashNode, TYPE_NAME)* prev = NULL; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            if (prev) { \
                prev->next = node->next; \
            } else { \
                map->buckets[index] = node->next; \
            } \
            free(node); \
            map->size--; \
            return true; \
        } \
        prev = node; \
        node = node->next; \
    } \
    return false; \
} \
\
static inline void MAKE_NAME(hashmap_display, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    printf("HashMap (size: %zu, capacity: %zu) {\n", map->size, map->capacity); \
    for (size_t i = 0; i < map->capacity; i++) { \
        if (map->buckets[i]) { \
            printf("  [%zu]: ", i); \
            MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[i]; \
            while (node) { \
                printf("(" K_FORMAT " -> " V_FORMAT ")", node->key, node->value); \
                if (node->next) printf(" -> "); \
                node = node->next; \
            } \
            printf("\n"); \
        } \
    } \
    printf("}\n"); \
} \
\
static inline void MAKE_NAME(hashmap_print_all, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    printf("{ "); \
    for (size_t i = 0; i < map->capacity; i++) { \
        MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[i]; \
        while (node) { \
            printf("(" K_FORMAT " -> " V_FORMAT ") ", node->key, node->value); \
            node = node->next; \
        } \
    } \
    printf("}\n"); \
} \
\
static inline void MAKE_NAME(hashmap_clear, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    for (size_t i = 0; i < map->capacity; i++) { \
        MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[i]; \
        while (node) { \
            MAKE_NAME(HashNode, TYPE_NAME)* next = node->next; \
            free(node); \
            node = next; \
        } \
        map->buckets[i] = NULL; \
    } \
    map->size = 0; \
} \
\
static inline void MAKE_NAME(hashmap_destroy, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    MAKE_NAME(hashmap_clear, TYPE_NAME)(map); \
    free(map->buckets); \
    map->buckets = NULL; \
    map->capacity = 0; \
    map->size = 0; \
}

// For custom types with custom hash and equality functions
#define DEFINE_HASHMAP_CUSTOM(K, V, TYPE_NAME, K_FORMAT, V_FORMAT, HASH_FUNC, K_EQUAL, K_PRINT, V_PRINT) \
typedef struct MAKE_NAME(HashNode, TYPE_NAME) { \
    K key; \
    V value; \
    struct MAKE_NAME(HashNode, TYPE_NAME)* next; \
} MAKE_NAME(HashNode, TYPE_NAME); \
\
typedef struct { \
    MAKE_NAME(HashNode, TYPE_NAME)** buckets; \
    size_t capacity; \
    size_t size; \
} MAKE_NAME(HashMap, TYPE_NAME); \
\
static inline MAKE_NAME(HashNode, TYPE_NAME)* MAKE_NAME(create_hash_node, TYPE_NAME)(K key, V value) { \
    MAKE_NAME(HashNode, TYPE_NAME)* node = (MAKE_NAME(HashNode, TYPE_NAME)*)malloc(sizeof(MAKE_NAME(HashNode, TYPE_NAME))); \
    node->key = key; \
    node->value = value; \
    node->next = NULL; \
    return node; \
} \
\
static inline void MAKE_NAME(hashmap_init, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    map->buckets = (MAKE_NAME(HashNode, TYPE_NAME)**)calloc(HASHMAP_INITIAL_CAPACITY, sizeof(MAKE_NAME(HashNode, TYPE_NAME)*)); \
    map->capacity = HASHMAP_INITIAL_CAPACITY; \
    map->size = 0; \
} \
\
static inline size_t MAKE_NAME(get_bucket_index, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    return HASH_FUNC(key) % map->capacity; \
} \
\
static inline void MAKE_NAME(hashmap_put, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key, V value) { \
    if ((double)map->size / map->capacity >= HASHMAP_LOAD_FACTOR) { \
        size_t old_capacity = map->capacity; \
        MAKE_NAME(HashNode, TYPE_NAME)** old_buckets = map->buckets; \
        map->capacity *= 2; \
        map->buckets = (MAKE_NAME(HashNode, TYPE_NAME)**)calloc(map->capacity, sizeof(MAKE_NAME(HashNode, TYPE_NAME)*)); \
        size_t old_size = map->size; \
        map->size = 0; \
        for (size_t i = 0; i < old_capacity; i++) { \
            MAKE_NAME(HashNode, TYPE_NAME)* node = old_buckets[i]; \
            while (node) { \
                MAKE_NAME(HashNode, TYPE_NAME)* next = node->next; \
                size_t new_index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, node->key); \
                node->next = map->buckets[new_index]; \
                map->buckets[new_index] = node; \
                map->size++; \
                node = next; \
            } \
        } \
        free(old_buckets); \
    } \
    \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            node->value = value; \
            return; \
        } \
        node = node->next; \
    } \
    \
    MAKE_NAME(HashNode, TYPE_NAME)* new_node = MAKE_NAME(create_hash_node, TYPE_NAME)(key, value); \
    new_node->next = map->buckets[index]; \
    map->buckets[index] = new_node; \
    map->size++; \
} \
\
static inline bool MAKE_NAME(hashmap_get, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key, V* value) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            *value = node->value; \
            return true; \
        } \
        node = node->next; \
    } \
    return false; \
} \
\
static inline bool MAKE_NAME(hashmap_contains, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            return true; \
        } \
        node = node->next; \
    } \
    return false; \
} \
\
static inline bool MAKE_NAME(hashmap_remove, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map, K key) { \
    size_t index = MAKE_NAME(get_bucket_index, TYPE_NAME)(map, key); \
    MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[index]; \
    MAKE_NAME(HashNode, TYPE_NAME)* prev = NULL; \
    \
    while (node) { \
        if (K_EQUAL(node->key, key)) { \
            if (prev) { \
                prev->next = node->next; \
            } else { \
                map->buckets[index] = node->next; \
            } \
            free(node); \
            map->size--; \
            return true; \
        } \
        prev = node; \
        node = node->next; \
    } \
    return false; \
} \
\
static inline void MAKE_NAME(hashmap_display, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    printf("HashMap (size: %zu, capacity: %zu) {\n", map->size, map->capacity); \
    for (size_t i = 0; i < map->capacity; i++) { \
        if (map->buckets[i]) { \
            printf("  [%zu]: ", i); \
            MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[i]; \
            while (node) { \
                printf("("); \
                K_PRINT(node->key); \
                printf(" -> "); \
                V_PRINT(node->value); \
                printf(")"); \
                if (node->next) printf(" -> "); \
                node = node->next; \
            } \
            printf("\n"); \
        } \
    } \
    printf("}\n"); \
} \
\
static inline void MAKE_NAME(hashmap_clear, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    for (size_t i = 0; i < map->capacity; i++) { \
        MAKE_NAME(HashNode, TYPE_NAME)* node = map->buckets[i]; \
        while (node) { \
            MAKE_NAME(HashNode, TYPE_NAME)* next = node->next; \
            free(node); \
            node = next; \
        } \
        map->buckets[i] = NULL; \
    } \
    map->size = 0; \
} \
\
static inline void MAKE_NAME(hashmap_destroy, TYPE_NAME)(MAKE_NAME(HashMap, TYPE_NAME)* map) { \
    MAKE_NAME(hashmap_clear, TYPE_NAME)(map); \
    free(map->buckets); \
    map->buckets = NULL; \
    map->capacity = 0; \
    map->size = 0; \
}

#endif