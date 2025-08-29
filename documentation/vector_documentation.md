# Vector Library Documentation

## Table of Contents
- [Overview](#overview)
- [Getting Started](#getting-started)
- [Data Structure](#data-structure)
- [API Reference](#api-reference)
- [Usage Examples](#usage-examples)
- [Memory Management](#memory-management)
- [Performance Characteristics](#performance-characteristics)
- [Multi-dimensional Vectors](#multi-dimensional-vectors)

## Overview

The Vector Library provides a dynamic array implementation for C, similar to `std::vector` in C++. It supports automatic memory management, dynamic resizing, and type-safe operations through C macros.

### Key Features
- **Dynamic resizing**: Automatically grows and shrinks as needed
- **Type safety**: Compile-time type checking through macros
- **Memory efficient**: Uses capacity doubling and shrinking strategies
- **Multi-dimensional support**: Easily create vectors of vectors
- **STL-like interface**: Familiar function names and patterns

## Getting Started

### Include the Header
```c
#include "stl.h"
```

### Generate Vector Types
```c
// Generate functions for int vectors
DEFINE_VEC(int)

// For 2D vectors (vector of vectors)
DEFINE_VEC(vec_int)
```

### Basic Usage
```c
vec_int v;
vec_int_init(&v);
vec_int_push(&v, 42);
int value = vec_int_get(&v, 0);
vec_int_free(&v);
```

## Data Structure

### Vector Structure Layout
```
vec_T {
    T *data     ──┐
    size_t cap   │
    size_t len   │
}               │
                │
    ┌───────────┘
    │
    ▼
┌─────┬─────┬─────┬─────┬─────┬─────┐
│  10 │  20 │  30 │ ??? │ ??? │ ??? │  Memory Block
└─────┴─────┴─────┴─────┴─────┴─────┘
  [0]   [1]   [2]   [3]   [4]   [5]
        
len = 3 (number of valid elements)
cap = 6 (total allocated space)
```

### Memory Growth Pattern
```
Initial: cap = 0, len = 0
   │
   ▼ (first push)
cap = 4, len = 1
┌─────┬─────┬─────┬─────┐
│  10 │ ??? │ ??? │ ??? │
└─────┴─────┴─────┴─────┘
   │
   ▼ (when len >= cap)
cap = 8, len = 5
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  10 │  20 │  30 │  40 │  50 │ ??? │ ??? │ ??? │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
```

### Capacity Shrinking
```
Before removal: cap = 8, len = 5
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  10 │  20 │  30 │  40 │  50 │ ??? │ ??? │ ??? │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

After removals: cap = 8, len = 2 (len <= cap/4)
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  10 │  20 │ ??? │ ??? │ ??? │ ??? │ ??? │ ??? │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
   │
   ▼ (shrink to cap/2)
cap = 4, len = 2
┌─────┬─────┬─────┬─────┐
│  10 │  20 │ ??? │ ??? │
└─────┴─────┴─────┴─────┘
```

## API Reference

### Type Definition
```c
DEFINE_VEC(T)
```
Generates all vector functions for type `T`. Creates:
- Type: `vec_T`
- Functions: `vec_T_init()`, `vec_T_push()`, etc.

### Initialization
```c
void vec_T_init(vec_T *v)
```
**Purpose**: Initialize an empty vector  
**Parameters**: 
- `v`: Pointer to vector to initialize
**Postcondition**: `v->len = 0, v->cap = 0, v->data = NULL`

### Adding Elements

#### Push (Append)
```c
void vec_T_push(vec_T *v, T val)
```
**Purpose**: Add element to end of vector  
**Time Complexity**: O(1) amortized, O(n) worst case  
**Parameters**:
- `v`: Vector to modify
- `val`: Value to add

**Behavior Diagram**:
```
Before: [10, 20, 30]    len=3, cap=4
                  ↑
              push(40)
                  ↓
After:  [10, 20, 30, 40] len=4, cap=4
```

#### Insert at Position
```c
void vec_T_insert(vec_T *v, size_t i, T item)
```
**Purpose**: Insert element at specific position  
**Time Complexity**: O(n)  
**Parameters**:
- `v`: Vector to modify  
- `i`: Insert position (0-based)
- `item`: Value to insert

**Behavior Diagram**:
```
Before: [10, 20, 30]    insert(1, 99)
         [0] [1] [2]
                  ↓
After:  [10, 99, 20, 30]
         [0] [1] [2] [3]
```

### Accessing Elements

#### Get Element
```c
T vec_T_get(vec_T *v, size_t i)
```
**Purpose**: Retrieve element at index  
**Time Complexity**: O(1)  
**Returns**: Element value or default value if index invalid  
**Parameters**:
- `v`: Vector to read from
- `i`: Index to access

#### Set Element
```c
void vec_T_set(vec_T *v, size_t i, T item)
```
**Purpose**: Modify element at index  
**Time Complexity**: O(1)  
**Parameters**:
- `v`: Vector to modify
- `i`: Index to modify
- `item`: New value

### Removing Elements
```c
void vec_T_remove(vec_T *v, size_t i)
```
**Purpose**: Remove element at index  
**Time Complexity**: O(n)  
**Parameters**:
- `v`: Vector to modify
- `i`: Index to remove

**Behavior Diagram**:
```
Before: [10, 20, 30, 40]  remove(1)
         [0] [1] [2] [3]
                  ↓
After:  [10, 30, 40]     (elements shift left)
         [0] [1] [2]
```

### Cleanup
```c
void vec_T_free(vec_T *v)
```
**Purpose**: Free allocated memory  
**Parameters**: 
- `v`: Vector to free
**Postcondition**: `v->data = NULL, v->len = 0, v->cap = 0`

## Usage Examples

### Basic Vector Operations
```c
#include "stl.h"

DEFINE_VEC(int)

int main() {
    vec_int numbers;
    vec_int_init(&numbers);
    
    // Add some numbers
    vec_int_push(&numbers, 10);
    vec_int_push(&numbers, 20);
    vec_int_push(&numbers, 30);
    
    // Access elements
    printf("First: %d\n", vec_int_get(&numbers, 0));  // Output: 10
    printf("Length: %zu\n", numbers.len);              // Output: 3
    
    // Modify element
    vec_int_set(&numbers, 1, 99);
    printf("Modified: %d\n", vec_int_get(&numbers, 1)); // Output: 99
    
    // Insert element
    vec_int_insert(&numbers, 0, 5);  // Insert 5 at beginning
    // Vector is now: [5, 10, 99, 30]
    
    // Remove element
    vec_int_remove(&numbers, 2);     // Remove element at index 2
    // Vector is now: [5, 10, 30]
    
    // Print all elements
    for (size_t i = 0; i < numbers.len; i++) {
        printf("%d ", vec_int_get(&numbers, i));
    }
    printf("\n");  // Output: 5 10 30
    
    // Cleanup
    vec_int_free(&numbers);
    return 0;
}
```

### String Vector Example
```c
DEFINE_VEC(char*)

int main() {
    vec_charptr words;
    vec_charptr_init(&words);
    
    vec_charptr_push(&words, "hello");
    vec_charptr_push(&words, "world");
    vec_charptr_push(&words, "vector");
    
    for (size_t i = 0; i < words.len; i++) {
        printf("%s ", vec_charptr_get(&words, i));
    }
    printf("\n");  // Output: hello world vector
    
    vec_charptr_free(&words);
    return 0;
}
```

## Memory Management

### Growth Strategy
- **Initial capacity**: 4 elements
- **Growth factor**: 2x when `len >= cap`
- **Shrink threshold**: When `len <= cap/4`
- **Shrink factor**: `cap/2` (minimum 4)

### Memory Allocation Flow
```
Push Operation:
┌─────────────────┐
│ len >= cap ?    │
└─────────────────┘
         │ Yes
         ▼
┌─────────────────┐    ┌─────────────────┐
│ new_cap = cap*2 │ ──▶│ realloc memory  │
│ (or 4 if cap=0) │    │ copy old data   │
└─────────────────┘    └─────────────────┘
         │                       │
         ▼                       ▼
┌─────────────────┐    ┌─────────────────┐
│ Add element     │◀───│ Update pointers │
│ Increment len   │    │ cap = new_cap   │
└─────────────────┘    └─────────────────┘
```

### Memory Safety
- **Bounds checking**: All access functions check array bounds
- **Null pointer safety**: Functions handle NULL data gracefully  
- **Memory leak prevention**: Always call `vec_T_free()` when done

## Performance Characteristics

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| `init()` | O(1) | O(1) |
| `push()` | O(1) amortized | O(1) |
| `get()` | O(1) | O(1) |
| `set()` | O(1) | O(1) |
| `insert()` | O(n) | O(1) |
| `remove()` | O(n) | O(1) |
| `free()` | O(1) | O(1) |

### Amortized Analysis for Push
```
Sequence of n pushes:
- Most pushes: O(1) - just add element
- Some pushes: O(k) - when resize happens, copy k elements
- Total work: O(n) for n elements
- Average: O(n)/n = O(1) amortized
```

## Multi-dimensional Vectors

### 2D Vector (Matrix)
```c
DEFINE_VEC(int)
DEFINE_VEC(vec_int)  // Vector of int vectors

int main() {
    vec_vec_int matrix;
    vec_vec_int_init(&matrix);
    
    // Create rows
    for (int i = 0; i < 3; i++) {
        vec_int row;
        vec_int_init(&row);
        
        // Add elements to row
        for (int j = 0; j < 4; j++) {
            vec_int_push(&row, i * 4 + j);
        }
        
        // Add row to matrix
        vec_vec_int_push(&matrix, row);
    }
    
    // Access element: matrix[1][2]
    vec_int second_row = vec_vec_int_get(&matrix, 1);
    int element = vec_int_get(&second_row, 2);
    printf("matrix[1][2] = %d\n", element);  // Output: 6
    
    // Cleanup
    for (size_t i = 0; i < matrix.len; i++) {
        vec_int_free(&matrix.data[i]);  // Free each row
    }
    vec_vec_int_free(&matrix);  // Free matrix structure
    
    return 0;
}
```

### 2D Vector Memory Layout
```
matrix (vec_vec_int):
┌─────────────┐
│ data ────┐  │
│ len = 3  │  │
│ cap = 4  │  │
└──────────┼──┘
           │
           ▼
┌─────┬─────┬─────┬─────┐
│row0 │row1 │row2 │ ??? │  Array of vec_int
└─────┴─────┴─────┴─────┘
  │     │     │
  │     │     └──▶ ┌─────┬─────┬─────┬─────┐
  │     │          │  8  │  9  │ 10  │ 11  │
  │     │          └─────┴─────┴─────┴─────┘
  │     │
  │     └──────▶ ┌─────┬─────┬─────┬─────┐
  │              │  4  │  5  │  6  │  7  │
  │              └─────┴─────┴─────┴─────┘
  │
  └────────────▶ ┌─────┬─────┬─────┬─────┐
                 │  0  │  1  │  2  │  3  │
                 └─────┴─────┴─────┴─────┘
```

### 3D Vector Example
```c
DEFINE_VEC(int)
DEFINE_VEC(vec_int)
DEFINE_VEC(vec_vec_int)

// Usage: cube[x][y][z]
vec_vec_vec_int cube;
vec_vec_vec_int_init(&cube);
```

## Best Practices

### 1. Always Initialize
```c
// Good
vec_int v;
vec_int_init(&v);

// Bad - undefined behavior
vec_int v;
vec_int_push(&v, 42);  // v.data is garbage!
```

### 2. Always Free
```c
// Good
vec_int v;
vec_int_init(&v);
// ... use vector ...
vec_int_free(&v);

// Bad - memory leak
vec_int v;
vec_int_init(&v);
// ... use vector ...
// No vec_int_free() - memory leaked!
```

### 3. Check Bounds When Needed
```c
// Safe access
if (i < v.len) {
    int val = vec_int_get(&v, i);  // Safe
}

// Direct access (faster but less safe)
int val = v.data[i];  // Only if you're sure i < v.len
```

### 4. Pre-allocate for Performance
```c
// If you know the size, pre-allocate to avoid reallocations
vec_int v;
vec_int_init(&v);

// Reserve space (manual implementation)
v.data = malloc(expected_size * sizeof(int));
v.cap = expected_size;
```

### 5. Multi-dimensional Cleanup
```c
// Always free inner vectors first
for (size_t i = 0; i < matrix.len; i++) {
    vec_int_free(&matrix.data[i]);  // Free each row
}
vec_vec_int_free(&matrix);  // Then free the matrix
```

## Common Pitfalls

### 1. Forgetting to Initialize
```c
// Wrong
vec_int v;  // Uninitialized!
vec_int_push(&v, 42);  // Crash!

// Correct  
vec_int v;
vec_int_init(&v);
vec_int_push(&v, 42);  // OK
```

### 2. Using After Free
```c
vec_int_free(&v);
vec_int_push(&v, 42);  // Wrong! v is freed
```

### 3. Index Out of Bounds
```c
vec_int v;
vec_int_init(&v);
int x = vec_int_get(&v, 0);  // Wrong! Vector is empty
```

### 4. Memory Leaks with 2D Vectors
```c
// Wrong - leaks row memory
vec_vec_int_free(&matrix);

// Correct
for (size_t i = 0; i < matrix.len; i++) {
    vec_int_free(&matrix.data[i]);
}
vec_vec_int_free(&matrix);
```

---

*This documentation covers the complete vector library API. For additional examples and advanced usage patterns, see the example files included with the library.*