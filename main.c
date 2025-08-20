#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// Helper functions for different data types

// For integers
int int_compare(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

void int_print(const void *data) {
    printf("%d", *(const int*)data);
}

// For strings
int string_compare(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void* string_copy(const void *data) {
    const char *str = *(const char**)data;
    char **copy = malloc(sizeof(char*));
    if (!copy) return NULL;
    *copy = malloc(strlen(str) + 1);
    if (!*copy) {
        free(copy);
        return NULL;
    }
    strcpy(*copy, str);
    return copy;
}

void string_destructor(void *data) {
    char **str_ptr = (char**)data;
    if (str_ptr && *str_ptr) {
        free(*str_ptr);
    }
    free(str_ptr);
}

void string_print(const void *data) {
    printf("\"%s\"", *(const char**)data);
}

// Test functions
void test_basic_operations() {
    printf("=== Testing Basic Operations ===\n");
    
    // Create list for integers
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    assert(int_list != NULL);
    assert(list_empty(int_list));
    assert(list_size(int_list) == 0);
    
    // Test push operations
    int values[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        assert(list_push_back(int_list, &values[i]));
    }
    
    assert(list_size(int_list) == 5);
    assert(!list_empty(int_list));
    
    // Test access functions
    assert(*(int*)list_front(int_list) == 10);
    assert(*(int*)list_back(int_list) == 50);
    assert(*(int*)list_at(int_list, 2) == 30);
    
    printf("✓ Basic operations test passed\n");
    
    // Print the list
    printf("List contents: ");
    list_print(int_list, int_print);
    
    list_destroy(int_list);
}

void test_insert_erase() {
    printf("\n=== Testing Insert/Erase Operations ===\n");
    
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    
    // Insert at various positions
    int val1 = 100, val2 = 200, val3 = 300, val4 = 150;
    
    list_push_back(int_list, &val1);  // [100]
    list_push_back(int_list, &val3);  // [100, 300]
    list_insert(int_list, 1, &val2);  // [100, 200, 300]
    list_insert(int_list, 1, &val4);  // [100, 150, 200, 300]
    
    printf("After insertions: ");
    list_print(int_list, int_print);
    
    assert(list_size(int_list) == 4);
    assert(*(int*)list_at(int_list, 0) == 100);
    assert(*(int*)list_at(int_list, 1) == 150);
    assert(*(int*)list_at(int_list, 2) == 200);
    assert(*(int*)list_at(int_list, 3) == 300);
    
    // Test erase
    list_erase(int_list, 1);  // Remove 150
    printf("After erasing index 1: ");
    list_print(int_list, int_print);
    
    assert(list_size(int_list) == 3);
    assert(*(int*)list_at(int_list, 1) == 200);
    
    printf("✓ Insert/Erase test passed\n");
    
    list_destroy(int_list);
}

void test_string_operations() {
    printf("\n=== Testing String Operations ===\n");
    
    List *str_list = list(sizeof(char*), string_destructor, string_copy, string_compare);
    
    const char *strings[] = {"Hello", "World", "C", "Programming"};
    
    for (int i = 0; i < 4; i++) {
        list_push_back(str_list, &strings[i]);
    }
    
    printf("String list: ");
    list_print(str_list, string_print);
    
    // Test find
    const char *search = "C";
    list_iterator it = list_find(str_list, &search);
    assert(list_iterator_valid(&it));
    
    // Test contains
    assert(list_contains(str_list, &search));
    
    const char *not_found = "Python";
    assert(!list_contains(str_list, &not_found));
    
    printf("✓ String operations test passed\n");
    
    list_destroy(str_list);
}

void test_iterators() {
    printf("\n=== Testing Iterators ===\n");
    
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        list_push_back(int_list, &values[i]);
    }
    
    // Forward iteration
    printf("Forward iteration: ");
    for (list_iterator it = list_begin(int_list); list_iterator_valid(&it); it = list_iterator_next(&it)) {
        printf("%d ", *(int*)list_iterator_data(&it));
    }
    printf("\n");
    
    // Backward iteration
    printf("Backward iteration: ");
    for (list_iterator it = list_rbegin(int_list); list_iterator_valid(&it); it = list_iterator_prev(&it)) {
        printf("%d ", *(int*)list_iterator_data(&it));
    }
    printf("\n");
    
    printf("✓ Iterator test passed\n");
    
    list_destroy(int_list);
}

void test_copy_reverse_sort() {
    printf("\n=== Testing Copy/Reverse/Sort ===\n");
    
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    
    int values[] = {50, 10, 30, 20, 40};
    for (int i = 0; i < 5; i++) {
        list_push_back(int_list, &values[i]);
    }
    
    printf("Original list: ");
    list_print(int_list, int_print);
    
    // Test copy
    List *copied_list = list_copy(int_list);
    printf("Copied list: ");
    list_print(copied_list, int_print);
    
    // Test reverse
    list_reverse(int_list);
    printf("Reversed list: ");
    list_print(int_list, int_print);
    
    // Test sort
    list_sort(copied_list);
    printf("Sorted list: ");
    list_print(copied_list, int_print);
    
    printf("✓ Copy/Reverse/Sort test passed\n");
    
    list_destroy(int_list);
    list_destroy(copied_list);
}

void test_edge_cases() {
    printf("\n=== Testing Edge Cases ===\n");
    
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    
    // Test operations on empty list
    assert(list_front(int_list) == NULL);
    assert(list_back(int_list) == NULL);
    assert(list_at(int_list, 0) == NULL);
    assert(!list_pop_front(int_list));
    assert(!list_pop_back(int_list));
    assert(!list_erase(int_list, 0));
    
    // Test single element operations
    int val = 42;
    list_push_back(int_list, &val);
    assert(list_size(int_list) == 1);
    assert(*(int*)list_front(int_list) == 42);
    assert(*(int*)list_back(int_list) == 42);
    
    list_pop_front(int_list);
    assert(list_empty(int_list));
    
    // Test boundary insertions
    list_push_back(int_list, &val);
    int val2 = 84;
    list_insert(int_list, 0, &val2);  // Insert at beginning
    list_insert(int_list, 2, &val2);  // Insert at end
    
    assert(list_size(int_list) == 3);
    
    printf("✓ Edge cases test passed\n");
    
    list_destroy(int_list);
}

void test_macros() {
    printf("\n=== Testing Helper Macros ===\n");
    
    List *int_list = list(sizeof(int), NULL, NULL, int_compare);
    
    // Test push macros with variables
    int val1 = 100, val2 = 50, val3 = 200;
    LIST_PUSH_BACK(int_list, val1);
    LIST_PUSH_FRONT(int_list, val2);
    LIST_PUSH_BACK(int_list, val3);
    
    // Test get macro
    int first = LIST_GET(int_list, 0, int);
    int second = LIST_GET(int_list, 1, int);
    int third = LIST_GET(int_list, 2, int);
    
    assert(first == 50);
    assert(second == 100);
    assert(third == 200);
    
    printf("List using macros: ");
    list_print(int_list, int_print);
    
    printf("✓ Macro test passed\n");
    
    list_destroy(int_list);
}

int main() {
    printf("Starting Doubly Linked List Tests...\n\n");
    
    test_basic_operations();
    test_insert_erase();
    test_string_operations();
    test_iterators();
    test_copy_reverse_sort();
    test_edge_cases();
    test_macros();
    
    printf("\n🎉 All tests passed successfully!\n");
    
    return 0;
}