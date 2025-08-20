#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Free function for heap-allocated integers
void free_int(void* ptr) {
    free(ptr);
}

void print_vector(Vector* v) {
    printf("Vector(size=%zu, capacity=%zu): ", v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", *(int*)vector_get(v, i));
    }
    printf("\n");
}

int main() {
    // Create vector
    Vector* a = vector_create();

    // Push back 17 elements
    for (int i = 1; i <= 17; i++) {
        int* val = malloc(sizeof(int));
        *val = i * 10;  // store multiples of 10
        vector_push_back(a, val);
        printf("After push_back(%d): size=%zu, capacity=%zu\n", *val, a->size, a->capacity);
    }

    printf("\nFinal vector contents:\n");
    print_vector(a);

    // Test vector_set (overwrite index 5)
    int* new_val = malloc(sizeof(int));
    *new_val = 999;
    vector_set(a, 5, new_val);
    printf("\nAfter vector_set at index 5:\n");
    print_vector(a);

    // Test vector_insert at index 3
    int* insert_val = malloc(sizeof(int));
    *insert_val = 777;
    vector_insert(a, 3, insert_val);
    printf("\nAfter vector_insert at index 3:\n");
    print_vector(a);

    // Test vector_remove at index 10
    vector_remove(a, 10);
    printf("\nAfter vector_remove at index 10:\n");
    print_vector(a);

    // Now repeatedly remove elements to test shrinking
    printf("\n--- Testing shrinking logic ---\n");
    while (a->size > 0) {
        vector_remove(a, a->size - 1);  // remove from end
        printf("After remove: size=%zu, capacity=%zu\n", a->size, a->capacity);
    }

    // Free vector (with free_func)
    printf("\nFreeing vector...\n");
    vector_free(a, free_int);

    return 0;
}
