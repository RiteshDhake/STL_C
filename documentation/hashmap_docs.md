# HashMap Library Documentation (hashmap.h)

## Table of Contents
- [Overview](#overview)
- [Architecture](#architecture)
- [Constants and Configuration](#constants-and-configuration)
- [Built-in Hash Functions](#built-in-hash-functions)
- [Predefined Type Combinations](#predefined-type-combinations)
- [Core Macros](#core-macros)
- [Generated API](#generated-api)
- [Implementation Details](#implementation-details)
- [Usage Examples](#usage-examples)
- [Performance Analysis](#performance-analysis)
- [Memory Management](#memory-management)
- [Best Practices](#best-practices)
- [Limitations](#limitations)

## Overview

The HashMap library provides a generic hash table implementation in C using macros. It implements separate chaining for collision resolution and automatic resizing based on load factor. The library supports both primitive types with built-in hash functions and custom types with user-defined hash and equality functions.

### Key Features
- **Generic Implementation**: Type-safe hash tables for any key-value combination
- **Automatic Resizing**: Maintains performance through dynamic capacity management
- **Collision Resolution**: Uses separate chaining with linked lists
- **Built-in Support**: Predefined macros for common primitive type combinations
- **Custom Type Support**: Extensible for user-defined types

## Architecture

The HashMap uses a **separate chaining** approach where:
1. Keys are hashed to bucket indices
2. Colliding elements form linked lists in each bucket
3. The hash table automatically resizes when load factor exceeds threshold

```
Buckets Array:
[0] -> Node1 -> Node3 -> NULL
[1] -> NULL
[2] -> Node2 -> Node4 -> Node5 -> NULL
[3] -> NULL
...
```

## Constants and Configuration

```c
#define HASHMAP_INITIAL_CAPACITY 16    // Starting number of buckets
#define HASHMAP_LOAD_FACTOR 0.75       // Resize threshold (75%)
```

### Load Factor Behavior
- When `size/capacity >= 0.75`, the hashmap doubles its capacity
- All existing elements are rehashed into the new bucket array
- This maintains average O(1) performance for operations

## Built-in Hash Functions

The library provides optimized hash functions for common types:

### Integer Types
```c
static inline size_t hash_int(int key)
static inline size_t hash_long(long key) 
static inline size_t hash_char(char key)
```
Simple casting to `size_t` for integer types.

### Floating Point Types
```c
static inline size_t hash_double(double key)
static inline size_t hash_float(float key)
```
Uses union casting to treat floating-point values as integers for hashing.

### String Type
```c
static inline size_t hash_string(const char* key)
```
Implements the **djb2 algorithm**:
```
hash = 5381
for each character c:
    hash = hash * 33 + c
```

### Equality Macros
```c
#define INT_EQUAL(a, b) ((a) == (b))
#define STRING_EQUAL(a, b) (strcmp((a), (b)) == 0)
#define DOUBLE_EQUAL(a, b) ((a) == (b))
#define FLOAT_EQUAL(a, b) ((a) == (b))
#define LONG_EQUAL(a, b) ((a) == (b))
#define CHAR_EQUAL(a, b) ((a) == (b))
```

## Predefined Type Combinations

The library provides 36 predefined macros covering all combinations of these types:
- **Keys**: `int`, `char*`, `double`, `float`, `long`, `char`
- **Values**: `int`, `char*`, `double`, `float`, `long`, `char`

### Integer Key Maps
```c
HASHMAP_INT_STRING    // int -> char*
HASHMAP_INT_DOUBLE    // int -> double  
HASHMAP_INT_FLOAT     // int -> float
HASHMAP_INT_LONG      // int -> long
HASHMAP_INT_CHAR      // int -> char
HASHMAP_INT_INT       // int -> int
```

### String Key Maps
```c
HASHMAP_STRING_INT    // char* -> int (word count, symbol tables)
HASHMAP_STRING_DOUBLE // char* -> double (configuration values)
HASHMAP_STRING_FLOAT  // char* -> float (metrics)
HASHMAP_STRING_LONG   // char* -> long (timestamps)
HASHMAP_STRING_CHAR   // char* -> char (grade mappings)
HASHMAP_STRING_STRING // char* -> char* (dictionaries)
```

### Numeric Key Maps
Similar patterns exist for:
- `HASHMAP_DOUBLE_*` - For floating-point key lookups
- `HASHMAP_FLOAT_*` - For single-precision key lookups  
- `HASHMAP_LONG_*` - For large integer key lookups
- `HASHMAP_CHAR_*` - For character-based mappings

## Core Macros

### Primary Macro
```c
DEFINE_HASHMAP(K, V, TYPE_NAME, K_FORMAT, V_FORMAT, HASH_FUNC, K_EQUAL)
```

**Parameters:**
- `K` - Key type
- `V` - Value type  
- `TYPE_NAME` - Unique identifier for this hashmap type
- `K_FORMAT` - printf format string for keys
- `V_FORMAT` - printf format string for values
- `HASH_FUNC` - Hash function for keys
- `K_EQUAL` - Equality comparison macro for keys

### Custom Type Macro
```c
DEFINE_HASHMAP_CUSTOM(K, V, TYPE_NAME, K_FORMAT, V_FORMAT, HASH_FUNC, K_EQUAL, K_PRINT, V_PRINT)
```

**Additional Parameters:**
- `K_PRINT` - Custom printing function for keys
- `V_PRINT` - Custom printing function for values

## Generated API

When you use a hashmap macro, it generates the following functions (where `TYPE_NAME` is your specified type name):

### Data Structures
```c
typedef struct HashNode_TYPE_NAME {
    K key;
    V value;
    struct HashNode_TYPE_NAME* next;
} HashNode_TYPE_NAME;

typedef struct {
    HashNode_TYPE_NAME** buckets;
    size_t capacity;
    size_t size;
} HashMap_TYPE_NAME;
```

### Core Functions

#### Initialization
```c
void hashmap_init_TYPE_NAME(HashMap_TYPE_NAME* map)
```
- Allocates initial bucket array (16 buckets)
- Sets size to 0
- Initializes all buckets to NULL

#### Insertion/Update
```c
void hashmap_put_TYPE_NAME(HashMap_TYPE_NAME* map, K key, V value)
```
- **Behavior**: Inserts new key-value pair or updates existing value
- **Resize**: Automatically resizes if load factor threshold exceeded
- **Collision**: Adds to linked list if bucket occupied
- **Time Complexity**: O(1) average, O(n) worst case

#### Retrieval
```c
bool hashmap_get_TYPE_NAME(HashMap_TYPE_NAME* map, K key, V* value)
```
- **Return**: `true` if key found, `false` otherwise
- **Output**: Value stored in `*value` parameter if found
- **Time Complexity**: O(1) average, O(n) worst case

#### Existence Check
```c
bool hashmap_contains_TYPE_NAME(HashMap_TYPE_NAME* map, K key)
```
- **Return**: `true` if key exists, `false` otherwise
- **Time Complexity**: O(1) average, O(n) worst case

#### Removal
```c
bool hashmap_remove_TYPE_NAME(HashMap_TYPE_NAME* map, K key)
```
- **Return**: `true` if key was removed, `false` if not found
- **Behavior**: Removes node from linked list and frees memory
- **Time Complexity**: O(1) average, O(n) worst case

### Utility Functions

#### Debug Display
```c
void hashmap_display_TYPE_NAME(HashMap_TYPE_NAME* map)
```
Shows internal structure with bucket indices and collision chains:
```
HashMap (size: 3, capacity: 16) {
  [2]: (apple -> 5) -> (grape -> 8)
  [7]: (banana -> 3)
}
```

#### Compact Print
```c
void hashmap_print_all_TYPE_NAME(HashMap_TYPE_NAME* map)
```
Prints all key-value pairs in a single line:
```
{ (apple -> 5) (banana -> 3) (grape -> 8) }
```

#### Memory Management
```c
void hashmap_clear_TYPE_NAME(HashMap_TYPE_NAME* map)    // Remove all elements
void hashmap_destroy_TYPE_NAME(HashMap_TYPE_NAME* map)  // Full cleanup
```

### Internal Functions
```c
HashNode_TYPE_NAME* create_hash_node_TYPE_NAME(K key, V value)
size_t get_bucket_index_TYPE_NAME(HashMap_TYPE_NAME* map, K key)  
void hashmap_resize_TYPE_NAME(HashMap_TYPE_NAME* map)
```

## Implementation Details

### Collision Resolution
The hashmap uses **separate chaining**:
```c
// New nodes are inserted at the head of each bucket's linked list
new_node->next = map->buckets[index];
map->buckets[index] = new_node;
```

### Resize Algorithm
When load factor exceeds 0.75:
1. **Save old state**: Store old buckets and capacity
2. **Double capacity**: Allocate new bucket array with 2x capacity
3. **Rehash all elements**: Move all nodes to new buckets based on new capacity
4. **Free old buckets**: Release old bucket array

### Hash Function Application
```c
size_t index = HASH_FUNC(key) % map->capacity;
```
The modulo operation ensures indices fit within the current capacity.

### Key Comparison
Keys are compared using the provided equality function/macro:
```c
if (K_EQUAL(node->key, key)) {
    // Found matching key
}
```

## Usage Examples

### Basic String-to-Integer Mapping
```c
#include "hashmap.h"

HASHMAP_STRING_INT;  // Generates HashMap_string_int type

int main() {
    HashMap_string_int word_count;
    hashmap_init_string_int(&word_count);
    
    // Count word frequencies
    hashmap_put_string_int(&word_count, "hello", 1);
    hashmap_put_string_int(&word_count, "world", 1);
    hashmap_put_string_int(&word_count, "hello", 2);  // Updates existing
    
    // Check results
    int count;
    if (hashmap_get_string_int(&word_count, "hello", &count)) {
        printf("'hello' appears %d times\n", count);  // Output: 2
    }
    
    // Display structure
    hashmap_display_string_int(&word_count);
    
    // Cleanup
    hashmap_destroy_string_int(&word_count);
    return 0;
}
```

### Custom Type Example
```c
typedef struct {
    int id;
    char name[50];
} Person;

// Custom hash function for Person
size_t hash_person(Person p) {
    return (size_t)p.id * 31 + hash_string(p.name);
}

// Custom equality function
bool person_equal(Person a, Person b) {
    return a.id == b.id && strcmp(a.name, b.name) == 0;
}

// Custom print functions
void print_person(Person p) {
    printf("Person{id=%d, name='%s'}", p.id, p.name);
}

void print_double(double d) {
    printf("%.2f", d);
}

// Generate the hashmap type
DEFINE_HASHMAP_CUSTOM(Person, double, person_double, 
                      "", "", hash_person, person_equal, 
                      print_person, print_double);

int main() {
    HashMap_person_double salary_map;
    hashmap_init_person_double(&salary_map);
    
    Person john = {1, "John Doe"};
    Person jane = {2, "Jane Smith"};
    
    hashmap_put_person_double(&salary_map, john, 75000.0);
    hashmap_put_person_double(&salary_map, jane, 82000.0);
    
    double salary;
    if (hashmap_get_person_double(&salary_map, john, &salary)) {
        printf("John's salary: $%.2f\n", salary);
    }
    
    hashmap_display_person_double(&salary_map);
    hashmap_destroy_person_double(&salary_map);
    return 0;
}
```

### Configuration and Monitoring Example
```c
#include "hashmap.h"

HASHMAP_STRING_STRING;  // Configuration key-value store

void load_config(HashMap_string_string* config) {
    hashmap_put_string_string(config, "database_url", "localhost:5432");
    hashmap_put_string_string(config, "api_key", "abc123xyz");
    hashmap_put_string_string(config, "debug_mode", "true");
    hashmap_put_string_string(config, "max_connections", "100");
}

void print_config(HashMap_string_string* config) {
    printf("Configuration Settings:\n");
    hashmap_print_all_string_string(config);
    
    // Check specific setting
    char* debug_mode;
    if (hashmap_get_string_string(config, "debug_mode", &debug_mode)) {
        printf("Debug mode is: %s\n", debug_mode);
    }
}

int main() {
    HashMap_string_string config;
    hashmap_init_string_string(&config);
    
    load_config(&config);
    print_config(&config);
    
    // Update configuration
    hashmap_put_string_string(&config, "debug_mode", "false");
    
    // Remove setting
    if (hashmap_remove_string_string(&config, "api_key")) {
        printf("API key removed for security\n");
    }
    
    printf("Updated configuration:\n");
    hashmap_print_all_string_string(&config);
    
    hashmap_destroy_string_string(&config);
    return 0;
}
```

## Performance Analysis

### Time Complexity
| Operation | Average Case | Worst Case | Notes |
|-----------|-------------|------------|-------|
| Insert    | O(1)        | O(n)       | Worst case when all keys hash to same bucket |
| Get       | O(1)        | O(n)       | Linear search within bucket |
| Remove    | O(1)        | O(n)       | Must traverse bucket chain |
| Contains  | O(1)        | O(n)       | Same as get operation |
| Resize    | O(n)        | O(n)       | Must rehash all elements |

### Space Complexity
- **Storage**: O(n) where n is the number of key-value pairs
- **Overhead**: Additional space for bucket array and node pointers
- **Load Factor**: Maintains ~75% capacity utilization

### Hash Function Performance

#### Integer Hash Functions
```c
// Fastest - simple cast
size_t hash_int(int key) { return (size_t)key; }
```

#### String Hash Function (djb2)
```c
size_t hash_string(const char* key) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
```
- **Quality**: Good distribution for typical string data
- **Speed**: Fast, single pass through string
- **Collisions**: Low collision rate for most string sets

#### Floating Point Hash Functions
```c
size_t hash_double(double key) {
    union { double d; uint64_t i; } u;
    u.d = key;
    return (size_t)u.i;
}
```
- **Approach**: Treats bit representation as integer
- **Precision**: Handles IEEE 754 floating point format
- **Caveat**: May have issues with NaN or very similar values

## Memory Management

### Allocation Strategy
```c
// Initial allocation
map->buckets = calloc(HASHMAP_INITIAL_CAPACITY, sizeof(HashNode_TYPE_NAME*));

// Node allocation
HashNode_TYPE_NAME* node = malloc(sizeof(HashNode_TYPE_NAME));
```

### Resize Memory Management
During resize:
1. **Allocate new buckets**: `calloc(new_capacity, ...)`
2. **Rehash existing nodes**: Move nodes to new buckets
3. **Free old bucket array**: `free(old_buckets)`
4. **Nodes preserved**: Individual nodes are reused, not reallocated

### Cleanup Functions
```c
// Remove all elements, keep structure
void hashmap_clear_TYPE_NAME(HashMap_TYPE_NAME* map);

// Complete destruction
void hashmap_destroy_TYPE_NAME(HashMap_TYPE_NAME* map);
```

## Best Practices

### 1. Initialization and Cleanup
```c
HashMap_string_int map;
hashmap_init_string_int(&map);  // Always initialize
// ... use map ...
hashmap_destroy_string_int(&map);  // Always cleanup
```

### 2. Error Handling
```c
int value;
if (hashmap_get_string_int(&map, "key", &value)) {
    printf("Found: %d\n", value);
} else {
    printf("Key not found\n");
}
```

### 3. String Key Management
```c
// Safe: string literals or static strings
hashmap_put_string_int(&map, "static_key", 42);

// Dangerous: local string variables
char local_key[100];
strcpy(local_key, "temp");
hashmap_put_string_int(&map, local_key, 42);  // Key may become invalid!

// Safe: dynamically allocated strings
char* safe_key = strdup("dynamic_key");
hashmap_put_string_int(&map, safe_key, 42);
// Remember to free safe_key when done with the hashmap
```

### 4. Efficient Batch Operations
```c
// Resize once upfront if you know approximate size
HashMap_string_int map;
hashmap_init_string_int(&map);

// If you know you'll insert ~100 items, the map will resize multiple times
// Consider the load factor when planning insertions
```

### 5. Iteration Pattern
```c
// Manual iteration through all buckets
for (size_t i = 0; i < map.capacity; i++) {
    HashNode_string_int* node = map.buckets[i];
    while (node) {
        printf("Key: %s, Value: %d\n", node->key, node->value);
        node = node->next;
    }
}
```

## Limitations

### 1. No Iterator Interface
- No standard way to iterate through elements
- Must manually traverse bucket array and linked lists
- Order of iteration is not guaranteed

### 2. String Key Lifetime Management
- Library stores key pointers, not copies
- User responsible for ensuring string keys remain valid
- No automatic string duplication or cleanup

### 3. Hash Function Quality
- Built-in hash functions are simple but may not be optimal for all data
- No cryptographic hash functions provided
- Integer hash functions vulnerable to patterns in input data

### 4. Memory Overhead
- Each node requires additional pointer storage
- Bucket array may be sparsely populated
- No memory compaction after removals

### 5. Thread Safety
- Not thread-safe
- Concurrent access requires external synchronization
- Resize operation particularly vulnerable to race conditions

### 6. No Resize Down
- Capacity only increases, never decreases
- May waste memory if many elements are removed
- No automatic shrinking based on low load factor

## Advanced Usage Patterns

### 1. Error Handling Wrapper
```c
typedef enum {
    HASHMAP_SUCCESS,
    HASHMAP_KEY_NOT_FOUND,
    HASHMAP_MEMORY_ERROR
} hashmap_result_t;

hashmap_result_t safe_get_string_int(HashMap_string_int* map, 
                                    const char* key, int* value) {
    if (!map || !key || !value) return HASHMAP_MEMORY_ERROR;
    return hashmap_get_string_int(map, key, value) ? 
           HASHMAP_SUCCESS : HASHMAP_KEY_NOT_FOUND;
}
```

### 2. Statistics and Monitoring
```c
void hashmap_stats_string_int(HashMap_string_int* map) {
    printf("HashMap Statistics:\n");
    printf("  Size: %zu\n", map->size);
    printf("  Capacity: %zu\n", map->capacity);
    printf("  Load Factor: %.2f\n", (double)map->size / map->capacity);
    
    // Analyze distribution
    size_t empty_buckets = 0;
    size_t max_chain_length = 0;
    
    for (size_t i = 0; i < map->capacity; i++) {
        size_t chain_length = 0;
        HashNode_string_int* node = map->buckets[i];
        
        if (!node) {
            empty_buckets++;
        } else {
            while (node) {
                chain_length++;
                node = node->next;
            }
            if (chain_length > max_chain_length) {
                max_chain_length = chain_length;
            }
        }
    }
    
    printf("  Empty Buckets: %zu (%.1f%%)\n", 
           empty_buckets, 100.0 * empty_buckets / map->capacity);
    printf("  Longest Chain: %zu\n", max_chain_length);
}
```

### 3. Functional-Style Operations
```c
// Apply function to all key-value pairs
void hashmap_foreach_string_int(HashMap_string_int* map, 
                               void (*func)(const char* key, int value)) {
    for (size_t i = 0; i < map->capacity; i++) {
        HashNode_string_int* node = map->buckets[i];
        while (node) {
            func(node->key, node->value);
            node = node->next;
        }
    }
}

// Example usage
void print_item(const char* key, int value) {
    printf("%-20s: %d\n", key, value);
}

// Call: hashmap_foreach_string_int(&map, print_item);
```

This HashMap implementation provides a robust, efficient foundation for key-value storage in C with the flexibility to work with any type combination while maintaining type safety through the macro system.