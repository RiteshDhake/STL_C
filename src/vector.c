#include "stl.h"

// Generate vector types with new compact names
DEFINE_VEC(int)
DEFINE_VEC(vec_int)

void print_vector(vec_int *v) {
    printf("Vector(len=%zu, cap=%zu): ", v->len, v->cap);
    for (size_t i = 0; i < v->len; i++) {
        printf("%d ", vec_int_get(v, i));
    }
    printf("\n");
}

int main() {
    vec_int v;
    vec_int_init(&v);

    printf("=== Testing vec_int ===\n");

    // Push values
    for (int i = 1; i <= 5; i++) {
        vec_int_push(&v, i * 10);
        printf("After push %d -> len=%zu, cap=%zu\n", i * 10, v.len, v.cap);
        print_vector(&v);
    }

    // Get element
    printf("Element at index 2 = %d\n", vec_int_get(&v, 2));

    // Set element
    vec_int_set(&v, 2, 99);
    printf("After set index 2 -> len=%zu, cap=%zu\n", v.len, v.cap);
    print_vector(&v);

    // Remove element
    vec_int_remove(&v, 3);
    printf("After remove index 3 -> len=%zu, cap=%zu\n", v.len, v.cap);
    print_vector(&v);

    // Free inner vector
    vec_int_free(&v);

    printf("\n=== Testing vec_vec_int (2D vector) ===\n");

    vec_vec_int vv;
    vec_vec_int_init(&vv);

    for (int i = 0; i < 3; i++) {
        vec_int temp;
        vec_int_init(&temp);
        for (int j = 0; j < 3; j++) {
            vec_int_push(&temp, i * 10 + j);
        }
        vec_vec_int_push(&vv, temp);
        printf("Added sub-vector %d -> outer len=%zu, cap=%zu\n", i, vv.len, vv.cap);
    }

    // Print nested vectors one by one
    for (size_t i = 0; i < vv.len; i++) {
        printf("Sub-vector %zu: ", i);
        print_vector(&vv.data[i]);
    }

    // Print final nested vector representation like [ [..], [..], [..] ]
    printf("\nNested vector representation: [");
    for (size_t i = 0; i < vv.len; i++) {
        printf("[");
        for (size_t j = 0; j < vv.data[i].len; j++) {
            printf("%d", vec_int_get(&vv.data[i], j));
            if (j + 1 < vv.data[i].len) printf(", ");
        }
        printf("]");
        if (i + 1 < vv.len) printf(", ");
    }
    printf("]\n");

    // Cleanup
    for (size_t i = 0; i < vv.len; i++) {
        vec_int_free(&vv.data[i]);
    }
    vec_vec_int_free(&vv);

    return 0;
}