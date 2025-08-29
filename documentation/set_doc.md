# Set Module Documentation

The `set.h` file provides a macro-based generic implementation of a
**Set** in C using a binary search tree (BST).

------------------------------------------------------------------------

## Features

-   Supports sets for primitive types (int, float, etc.) and custom
    types.
-   Provides operations:
    -   Add
    -   Contains
    -   Display
    -   Union
    -   Intersection
    -   Difference
    -   Subset check
    -   Equality
    -   Power set
    -   Cartesian product (for primitive types)

------------------------------------------------------------------------

## Usage

### Define a Set for a Primitive Type

``` c
DEFINE_SET(int, int, "%d");     // Set_int
DEFINE_SET(float, float, "%f"); // Set_float
```

### Define a Set for a Custom Type

``` c
int cmp_student(Student a, Student b) { return strcmp(a.name, b.name); }
bool eq_student(Student a, Student b) { return strcmp(a.name, b.name) == 0; }
void print_student(Student s) { printf("(%d,%s)", s.roll_no, s.name); }

DEFINE_SET_CUSTOM(Student, Student, cmp_student, eq_student, print_student);
```

------------------------------------------------------------------------

### Example

``` c
#include "set.h"

int main() {
    Set_int A, B;
    set_init_int(&A);
    set_init_int(&B);

    set_add_int(&A, 1);
    set_add_int(&A, 2);
    set_add_int(&B, 2);
    set_add_int(&B, 3);

    printf("Set A: ");
    set_display_int(&A);

    printf("Set B: ");
    set_display_int(&B);

    Set_int U = set_union_int(&A, &B);
    printf("Union: ");
    set_display_int(&U);

    return 0;
}
```

### Functions for Primitive Sets

-   `void set_init_##TYPE(Set_##TYPE *s)`
-   `void set_add_##TYPE(Set_##TYPE *s, T val)`
-   `bool set_contains_##TYPE(Set_##TYPE *s, T val)`
-   `void set_display_##TYPE(Set_##TYPE *s)`
-   `Set_##TYPE set_union_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`
-   `Set_##TYPE set_intersection_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`
-   `Set_##TYPE set_difference_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`
-   `bool set_is_subset_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`
-   `bool set_is_equal_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`
-   `void set_power_set_##TYPE(Set_##TYPE *A)`
-   `void set_cartesian_product_##TYPE(Set_##TYPE *A, Set_##TYPE *B)`

------------------------------------------------------------------------

## Notes

-   Internally uses a Binary Search Tree (BST).
-   Only unique elements are stored.
-   For custom structs, you must define comparison, equality, and print
    functions.
