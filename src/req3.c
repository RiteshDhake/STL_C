#include "stl.h"


// Instantiate hashmap types for testing
HASHMAP_INT_STRING;
HASHMAP_STRING_INT;
HASHMAP_INT_INT;
HASHMAP_STRING_STRING;
HASHMAP_DOUBLE_INT;
HASHMAP_FLOAT_STRING;
HASHMAP_LONG_CHAR;
HASHMAP_CHAR_DOUBLE;

// Test result tracking
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_ASSERT(condition, message) \
    do { \
        if (condition) { \
            printf("✓ PASS: %s\n", message); \
            tests_passed++; \
        } else { \
            printf("✗ FAIL: %s\n", message); \
            tests_failed++; \
        } \
    } while(0)

void test_int_string_hashmap() {
    printf("\n=== Testing HashMap_int_string ===\n");
    
    HashMap_int_string map;
    hashmap_init_int_string(&map);
    
    // Test initialization
    TEST_ASSERT(map.size == 0, "Initial size is 0");
    TEST_ASSERT(map.capacity == HASHMAP_INITIAL_CAPACITY, "Initial capacity is correct");
    
    // Test basic put and get
    hashmap_put_int_string(&map, 1, "one");
    hashmap_put_int_string(&map, 2, "two");
    hashmap_put_int_string(&map, 3, "three");
    
    TEST_ASSERT(map.size == 3, "Size after adding 3 elements");
    
    char* value;
    TEST_ASSERT(hashmap_get_int_string(&map, 1, &value) && strcmp(value, "one") == 0, "Get key 1");
    TEST_ASSERT(hashmap_get_int_string(&map, 2, &value) && strcmp(value, "two") == 0, "Get key 2");
    TEST_ASSERT(hashmap_get_int_string(&map, 3, &value) && strcmp(value, "three") == 0, "Get key 3");
    
    // Test contains
    TEST_ASSERT(hashmap_contains_int_string(&map, 1), "Contains key 1");
    TEST_ASSERT(hashmap_contains_int_string(&map, 2), "Contains key 2");
    TEST_ASSERT(!hashmap_contains_int_string(&map, 4), "Does not contain key 4");
    
    // Test update existing key
    hashmap_put_int_string(&map, 1, "ONE");
    TEST_ASSERT(hashmap_get_int_string(&map, 1, &value) && strcmp(value, "ONE") == 0, "Update existing key");
    TEST_ASSERT(map.size == 3, "Size unchanged after update");
    
    // Test remove
    TEST_ASSERT(hashmap_remove_int_string(&map, 2), "Remove existing key");
    TEST_ASSERT(!hashmap_contains_int_string(&map, 2), "Key 2 no longer exists");
    TEST_ASSERT(map.size == 2, "Size after removal");
    TEST_ASSERT(!hashmap_remove_int_string(&map, 2), "Cannot remove non-existent key");
    
    // Test get non-existent key
    TEST_ASSERT(!hashmap_get_int_string(&map, 99, &value), "Get non-existent key returns false");
    
    printf("HashMap contents:\n");
    hashmap_display_int_string(&map);
    
    hashmap_destroy_int_string(&map);
    printf("HashMap destroyed\n");
}

void test_string_int_hashmap() {
    printf("\n=== Testing HashMap_string_int ===\n");
    
    HashMap_string_int map;
    hashmap_init_string_int(&map);
    
    // Test string keys
    hashmap_put_string_int(&map, "apple", 100);
    hashmap_put_string_int(&map, "banana", 200);
    hashmap_put_string_int(&map, "cherry", 300);
    
    int value;
    TEST_ASSERT(hashmap_get_string_int(&map, "apple", &value) && value == 100, "Get 'apple'");
    TEST_ASSERT(hashmap_get_string_int(&map, "banana", &value) && value == 200, "Get 'banana'");
    TEST_ASSERT(hashmap_get_string_int(&map, "cherry", &value) && value == 300, "Get 'cherry'");
    
    TEST_ASSERT(!hashmap_get_string_int(&map, "orange", &value), "Get non-existent 'orange'");
    
    // Test collision handling (if keys hash to same bucket)
    hashmap_put_string_int(&map, "test1", 1);
    hashmap_put_string_int(&map, "test2", 2);
    
    TEST_ASSERT(hashmap_get_string_int(&map, "test1", &value) && value == 1, "Collision handling test1");
    TEST_ASSERT(hashmap_get_string_int(&map, "test2", &value) && value == 2, "Collision handling test2");
    
    printf("All entries: ");
    hashmap_print_all_string_int(&map);
    
    hashmap_destroy_string_int(&map);
}

void test_resize_functionality() {
    printf("\n=== Testing Resize Functionality ===\n");
    
    HashMap_int_int map;
    hashmap_init_int_int(&map);
    
    size_t initial_capacity = map.capacity;
    printf("Initial capacity: %zu\n", initial_capacity);
    
    // Add enough elements to trigger resize
    int resize_threshold = (int)(initial_capacity * HASHMAP_LOAD_FACTOR) + 1;
    printf("Adding %d elements to trigger resize...\n", resize_threshold);
    
    for (int i = 0; i < resize_threshold; i++) {
        hashmap_put_int_int(&map, i, i * 10);
    }
    
    TEST_ASSERT(map.capacity > initial_capacity, "Capacity increased after resize");
    TEST_ASSERT(map.size == resize_threshold, "All elements preserved after resize");
    
    // Verify all elements are still accessible
    int value;
    bool all_found = true;
    for (int i = 0; i < resize_threshold; i++) {
        if (!hashmap_get_int_int(&map, i, &value) || value != i * 10) {
            all_found = false;
            break;
        }
    }
    TEST_ASSERT(all_found, "All elements accessible after resize");
    
    printf("Final capacity: %zu, size: %zu\n", map.capacity, map.size);
    
    hashmap_destroy_int_int(&map);
}

void test_different_types() {
    printf("\n=== Testing Different Type Combinations ===\n");
    
    // Test double keys with int values
    HashMap_double_int double_map;
    hashmap_init_double_int(&double_map);
    
    hashmap_put_double_int(&double_map, 3.14, 314);
    hashmap_put_double_int(&double_map, 2.71, 271);
    
    int int_val;
    TEST_ASSERT(hashmap_get_double_int(&double_map, 3.14, &int_val) && int_val == 314, "Double key 3.14");
    TEST_ASSERT(hashmap_get_double_int(&double_map, 2.71, &int_val) && int_val == 271, "Double key 2.71");
    
    // Test float keys with string values
    HashMap_float_string float_map;
    hashmap_init_float_string(&float_map);
    
    hashmap_put_float_string(&float_map, 1.5f, "one-and-half");
    hashmap_put_float_string(&float_map, 2.5f, "two-and-half");
    
    char* str_val;
    TEST_ASSERT(hashmap_get_float_string(&float_map, 1.5f, &str_val) && strcmp(str_val, "one-and-half") == 0, "Float key 1.5");
    
    // Test long keys with char values
    HashMap_long_char long_map;
    hashmap_init_long_char(&long_map);
    
    hashmap_put_long_char(&long_map, 1000L, 'A');
    hashmap_put_long_char(&long_map, 2000L, 'B');
    
    char char_val;
    TEST_ASSERT(hashmap_get_long_char(&long_map, 1000L, &char_val) && char_val == 'A', "Long key 1000");
    TEST_ASSERT(hashmap_get_long_char(&long_map, 2000L, &char_val) && char_val == 'B', "Long key 2000");
    
    // Test char keys with double values
    HashMap_char_double char_map;
    hashmap_init_char_double(&char_map);
    
    hashmap_put_char_double(&char_map, 'x', 99.99);
    hashmap_put_char_double(&char_map, 'y', 88.88);
    
    double double_val;
    TEST_ASSERT(hashmap_get_char_double(&char_map, 'x', &double_val) && double_val == 99.99, "Char key 'x'");
    TEST_ASSERT(hashmap_get_char_double(&char_map, 'y', &double_val) && double_val == 88.88, "Char key 'y'");
    
    hashmap_destroy_double_int(&double_map);
    hashmap_destroy_float_string(&float_map);
    hashmap_destroy_long_char(&long_map);
    hashmap_destroy_char_double(&char_map);
}

void test_edge_cases() {
    printf("\n=== Testing Edge Cases ===\n");
    
    HashMap_string_string map;
    hashmap_init_string_string(&map);
    
    // Test empty string keys and values
    hashmap_put_string_string(&map, "", "empty_key");
    hashmap_put_string_string(&map, "empty_value", "");
    
    char* value;
    TEST_ASSERT(hashmap_get_string_string(&map, "", &value) && strcmp(value, "empty_key") == 0, "Empty string key");
    TEST_ASSERT(hashmap_get_string_string(&map, "empty_value", &value) && strcmp(value, "") == 0, "Empty string value");
    
    // Test clear functionality
    hashmap_put_string_string(&map, "key1", "value1");
    hashmap_put_string_string(&map, "key2", "value2");
    TEST_ASSERT(map.size == 4, "Size before clear");
    
    hashmap_clear_string_string(&map);
    TEST_ASSERT(map.size == 0, "Size after clear");
    TEST_ASSERT(!hashmap_contains_string_string(&map, "key1"), "No elements after clear");
    
    hashmap_destroy_string_string(&map);
}

void test_collision_handling() {
    printf("\n=== Testing Collision Handling ===\n");
    
    HashMap_int_string map;
    hashmap_init_int_string(&map);
    
    // Force collisions by using keys that will hash to same bucket
    // With capacity 16, keys 1 and 17 should hash to same bucket (1 % 16 = 1, 17 % 16 = 1)
    hashmap_put_int_string(&map, 1, "first");
    hashmap_put_int_string(&map, 17, "seventeenth");
    hashmap_put_int_string(&map, 33, "thirty-third");
    
    char* value;
    TEST_ASSERT(hashmap_get_int_string(&map, 1, &value) && strcmp(value, "first") == 0, "Collision: key 1");
    TEST_ASSERT(hashmap_get_int_string(&map, 17, &value) && strcmp(value, "seventeenth") == 0, "Collision: key 17");
    TEST_ASSERT(hashmap_get_int_string(&map, 33, &value) && strcmp(value, "thirty-third") == 0, "Collision: key 33");
    
    // Test removal with collisions
    TEST_ASSERT(hashmap_remove_int_string(&map, 17), "Remove middle collision element");
    TEST_ASSERT(!hashmap_contains_int_string(&map, 17), "Key 17 removed");
    TEST_ASSERT(hashmap_get_int_string(&map, 1, &value) && strcmp(value, "first") == 0, "Key 1 still accessible");
    TEST_ASSERT(hashmap_get_int_string(&map, 33, &value) && strcmp(value, "thirty-third") == 0, "Key 33 still accessible");
    
    printf("Collision test map structure:\n");
    hashmap_display_int_string(&map);
    
    hashmap_destroy_int_string(&map);
}

void test_large_dataset() {
    printf("\n=== Testing Large Dataset Performance ===\n");
    
    HashMap_int_int map;
    hashmap_init_int_int(&map);
    
    const int num_elements = 1000;
    printf("Adding %d elements...\n", num_elements);
    
    // Add many elements
    for (int i = 0; i < num_elements; i++) {
        hashmap_put_int_int(&map, i, i * 2);
    }
    
    TEST_ASSERT(map.size == num_elements, "All elements added");
    printf("Final capacity: %zu (resized from %d)\n", map.capacity, HASHMAP_INITIAL_CAPACITY);
    
    // Verify random elements
    int value;
    TEST_ASSERT(hashmap_get_int_int(&map, 0, &value) && value == 0, "First element correct");
    TEST_ASSERT(hashmap_get_int_int(&map, 500, &value) && value == 1000, "Middle element correct");
    TEST_ASSERT(hashmap_get_int_int(&map, 999, &value) && value == 1998, "Last element correct");
    
    // Test batch removal
    int removed_count = 0;
    for (int i = 0; i < num_elements; i += 2) {  // Remove even keys
        if (hashmap_remove_int_int(&map, i)) {
            removed_count++;
        }
    }
    
    TEST_ASSERT(removed_count == num_elements / 2, "Removed half the elements");
    TEST_ASSERT(map.size == num_elements - removed_count, "Size correct after batch removal");
    
    // Verify odd keys still exist and even keys are gone
    TEST_ASSERT(!hashmap_contains_int_int(&map, 0), "Even key 0 removed");
    TEST_ASSERT(hashmap_contains_int_int(&map, 1), "Odd key 1 still exists");
    TEST_ASSERT(!hashmap_contains_int_int(&map, 500), "Even key 500 removed");
    TEST_ASSERT(hashmap_contains_int_int(&map, 501), "Odd key 501 still exists");
    
    hashmap_destroy_int_int(&map);
}

void test_all_primitive_combinations() {
    printf("\n=== Testing All Primitive Type Combinations ===\n");
    
    // Test a few key combinations to ensure they compile and work
    HashMap_string_string ss_map;
    hashmap_init_string_string(&ss_map);
    hashmap_put_string_string(&ss_map, "hello", "world");
    
    char* ss_value;
    TEST_ASSERT(hashmap_get_string_string(&ss_map, "hello", &ss_value) && strcmp(ss_value, "world") == 0, "String-String map");
    
    HashMap_double_int di_map;
    hashmap_init_double_int(&di_map);
    hashmap_put_double_int(&di_map, 3.14159, 42);
    
    int di_value;
    TEST_ASSERT(hashmap_get_double_int(&di_map, 3.14159, &di_value) && di_value == 42, "Double-Int map");
    
    HashMap_char_double cd_map;
    hashmap_init_char_double(&cd_map);
    hashmap_put_char_double(&cd_map, 'A', 3.14159);
    
    double cd_value;
    TEST_ASSERT(hashmap_get_char_double(&cd_map, 'A', &cd_value) && cd_value == 3.14159, "Char-Double map");
    
    hashmap_destroy_string_string(&ss_map);
    hashmap_destroy_double_int(&di_map);
    hashmap_destroy_char_double(&cd_map);
}

void test_boundary_conditions() {
    printf("\n=== Testing Boundary Conditions ===\n");
    
    HashMap_int_int map;
    hashmap_init_int_int(&map);
    
    // Test with zero key
    hashmap_put_int_int(&map, 0, 999);
    int value;
    TEST_ASSERT(hashmap_get_int_int(&map, 0, &value) && value == 999, "Zero key handling");
    
    // Test with negative keys
    hashmap_put_int_int(&map, -1, -999);
    hashmap_put_int_int(&map, -100, -1000);
    
    TEST_ASSERT(hashmap_get_int_int(&map, -1, &value) && value == -999, "Negative key -1");
    TEST_ASSERT(hashmap_get_int_int(&map, -100, &value) && value == -1000, "Negative key -100");
    
    // Test multiple operations on same key
    hashmap_put_int_int(&map, 42, 1);
    hashmap_put_int_int(&map, 42, 2);
    hashmap_put_int_int(&map, 42, 3);
    
    TEST_ASSERT(hashmap_get_int_int(&map, 42, &value) && value == 3, "Multiple updates to same key");
    TEST_ASSERT(map.size == 4, "Size correct after multiple updates"); // 0, -1, -100, 42 (duplicates don't increase size)
    
    hashmap_destroy_int_int(&map);
}

void demonstrate_usage() {
    printf("\n=== Usage Demonstration ===\n");
    
    // Create a word frequency counter
    HashMap_string_int word_freq;
    hashmap_init_string_int(&word_freq);
    
    char* text[] = {"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog", "the"};
    int text_len = sizeof(text) / sizeof(text[0]);
    
    printf("Counting word frequencies in: ");
    for (int i = 0; i < text_len; i++) {
        printf("%s ", text[i]);
    }
    printf("\n");
    
    // Count frequencies
    for (int i = 0; i < text_len; i++) {
        int count;
        if (hashmap_get_string_int(&word_freq, text[i], &count)) {
            hashmap_put_string_int(&word_freq, text[i], count + 1);
        } else {
            hashmap_put_string_int(&word_freq, text[i], 1);
        }
    }
    
    printf("\nWord frequencies:\n");
    hashmap_display_string_int(&word_freq);
    
    // Verify specific counts
    int count;
    TEST_ASSERT(hashmap_get_string_int(&word_freq, "the", &count) && count == 3, "Word 'the' appears 3 times");
    TEST_ASSERT(hashmap_get_string_int(&word_freq, "quick", &count) && count == 1, "Word 'quick' appears 1 time");
    
    hashmap_destroy_string_int(&word_freq);
}

void run_stress_test() {
    printf("\n=== Stress Test ===\n");
    
    HashMap_int_string map;
    hashmap_init_int_string(&map);
    
    const int stress_size = 5000;
    printf("Stress testing with %d operations...\n", stress_size);
    
    // Mixed operations
    for (int i = 0; i < stress_size; i++) {
        char buffer[32];
        sprintf(buffer, "value_%d", i);
        hashmap_put_int_string(&map, i, strdup(buffer));  // Note: In real code, manage memory carefully
        
        if (i % 3 == 0 && i > 0) {
            hashmap_remove_int_string(&map, i - 1);
        }
    }
    
    printf("Final map size: %zu, capacity: %zu\n", map.size, map.capacity);
    TEST_ASSERT(map.size > 0, "Map not empty after stress test");
    
    // Note: In a real implementation, you'd want to free the strdup'd strings
    // For this test, we'll just destroy the map
    hashmap_destroy_int_string(&map);
}

// Custom type example for advanced testing
typedef struct {
    int x, y;
} Point;

static size_t hash_point(Point p) {
    return hash_int(p.x) ^ (hash_int(p.y) << 1);
}

static bool point_equal(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

static void print_point(Point p) {
    printf("(%d,%d)", p.x, p.y);
}

static void print_string_custom(char* s) {
    printf("%s", s);
}

// Define custom hashmap
DEFINE_HASHMAP_CUSTOM(Point, char*, point_string, "(%d,%d)", "%s", hash_point, point_equal, print_point, print_string_custom);

void test_custom_type() {
    printf("\n=== Testing Custom Type (Point -> String) ===\n");
    
    HashMap_point_string map;
    hashmap_init_point_string(&map);
    
    Point p1 = {1, 2};
    Point p2 = {3, 4};
    Point p3 = {1, 2};  // Same as p1
    
    hashmap_put_point_string(&map, p1, "first point");
    hashmap_put_point_string(&map, p2, "second point");
    
    char* value;
    TEST_ASSERT(hashmap_get_point_string(&map, p1, &value) && strcmp(value, "first point") == 0, "Custom type: Point(1,2)");
    TEST_ASSERT(hashmap_get_point_string(&map, p2, &value) && strcmp(value, "second point") == 0, "Custom type: Point(3,4)");
    TEST_ASSERT(hashmap_get_point_string(&map, p3, &value) && strcmp(value, "first point") == 0, "Custom type: Equal points");
    
    // Test update with equal key
    hashmap_put_point_string(&map, p3, "updated point");
    TEST_ASSERT(hashmap_get_point_string(&map, p1, &value) && strcmp(value, "updated point") == 0, "Custom type: Update equal key");
    TEST_ASSERT(map.size == 2, "Size unchanged after update with equal key");
    
    printf("Custom type map:\n");
    hashmap_display_point_string(&map);
    
    hashmap_destroy_point_string(&map);
}

void print_test_summary() {
    printf("\n================================================\n");
    printf("TEST SUMMARY\n");
    printf("================================================\n");
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);
    printf("Total tests:  %d\n", tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("\nALL TESTS PASSED!\n");
    } else {
        printf("\nSome tests failed. Please check the output above.\n");
    }
}

void demo_hashmap() {
    printf("HashMap Implementation Test Suite\n");
    printf("=================================\n");
    
    test_int_string_hashmap();
    test_string_int_hashmap();
    test_resize_functionality();
    test_different_types();
    test_edge_cases();
    test_collision_handling();
    test_boundary_conditions();
    demonstrate_usage();
    run_stress_test();
    test_custom_type();
    
    print_test_summary();
    
   
}