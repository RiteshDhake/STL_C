# STL_C

A comprehensive, type-safe Standard Template Library implementation for C, providing generic data structures and algorithms similar to C++ STL.

## 🚀 Overview

STL_C is a header-only library that brings modern data structures and algorithms to C programming. Using advanced preprocessor macros, it provides compile-time type safety and performance comparable to hand-written C code, while maintaining the familiar interface patterns from C++ STL.

## ✨ Features

- **Type-Safe**: Compile-time type checking prevents common programming errors
- **Header-Only**: Simple integration - just include `stl.h`
- **Zero Dependencies**: Only uses standard C library
- **High Performance**: Static inline functions enable aggressive compiler optimizations
- **Memory Efficient**: Automatic capacity management with smart allocation strategies
- **STL-Like API**: Familiar interface for developers coming from C++
- **Generic**: Works with any C data type (primitives, structs, pointers)

## 📦 Data Structures

### Currently Implemented

| Data Structure | Header | Description | Status |
|----------------|--------|-------------|---------|
| **Vector** | `vector.h` | Dynamic resizable array with O(1) amortized append | ✅ Complete |
| **Stack** | `stack.h` | LIFO container built on vector foundation | ✅ Complete |
| **List** | `list.h` | Doubly-linked list with O(1) insertion/deletion | ✅ Complete |
| **Set** | `set.h` | Ordered collection of unique elements | ✅ Complete |
| **HashMap** | `hashmap.h` | Hash table with fast key-value lookups | ✅ Complete |
| **Queue** | `queue.h` | FIFO container with efficient enqueue/dequeue | ✅ Complete |



## 🛠️ Quick Start

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/STL_C.git
cd STL_C
```

2. Include the main header in your C project:
```c
#include "include/stl.h"
```

That's it! All implemented data structures are now available.

### Basic Usage

```c
#include "include/stl.h"

// Generate vector and stack for integers
DEFINE_VEC(int)
DEFINE_STACK(int)

int main() {
    // Vector example
    vec_int numbers;
    vec_int_init(&numbers);
    
    vec_int_push(&numbers, 10);
    vec_int_push(&numbers, 20);
    vec_int_push(&numbers, 30);
    
    printf("Element at index 1: %d\n", vec_int_get(&numbers, 1));
    printf("Vector size: %zu\n", numbers.len);
    
    // Stack example  
    stack_int calc_stack;
    stack_int_init(&calc_stack);
    
    stack_int_push(&calc_stack, 42);
    stack_int_push(&calc_stack, 24);
    
    printf("Top element: %d\n", stack_int_peek(&calc_stack));
    printf("Popped: %d\n", stack_int_pop(&calc_stack));
    
    // Cleanup
    vec_int_free(&numbers);
    stack_int_free(&calc_stack);
    
    return 0;
}
```

### Working with Custom Types

```c
#include "include/stl.h"

// Define your custom type
typedef struct {
    int id;
    char name[50];
    double salary;
} Employee;

// Generate data structures for your type
DEFINE_VEC(Employee)
DEFINE_STACK(Employee)

int main() {
    // Use with your custom types
    vec_Employee staff;
    vec_Employee_init(&staff);
    
    Employee emp = {1001, "John Doe", 75000.0};
    vec_Employee_push(&staff, emp);
    
    Employee retrieved = vec_Employee_get(&staff, 0);
    printf("Employee: %s (ID: %d)\n", retrieved.name, retrieved.id);
    
    // Stack of employees
    stack_Employee emp_stack;
    stack_Employee_init(&emp_stack);
    stack_Employee_push(&emp_stack, emp);
    
    if (!stack_Employee_empty(&emp_stack)) {
        Employee top_emp = stack_Employee_peek(&emp_stack);
        printf("Top employee salary: %.2f\n", top_emp.salary);
    }
    
    vec_Employee_free(&staff);
    stack_Employee_free(&emp_stack);
    return 0;
}
```

## 📚 API Reference

### Vector Operations
```c
DEFINE_VEC(T)                         // Generate vector for type T

// Structure
typedef struct {
    T *data;                          // Pointer to data array
    size_t cap;                       // Current capacity
    size_t len;                       // Current length
} vec_T;

// Functions
void vec_T_init(vec_T *v)             // Initialize empty vector
void vec_T_push(vec_T *v, T val)      // Append element
T vec_T_get(vec_T *v, size_t i)       // Get element at index
void vec_T_set(vec_T *v, size_t i, T val)     // Set element at index
void vec_T_insert(vec_T *v, size_t i, T val)  // Insert at index
void vec_T_remove(vec_T *v, size_t i)         // Remove at index
void vec_T_free(vec_T *v)             // Free all memory
```

### Stack Operations
```c
DEFINE_STACK(T)                       // Generate stack for type T (requires DEFINE_VEC(T))

// Structure  
typedef struct {
    vec_T data;                       // Underlying vector storage
} stack_T;

// Functions
void stack_T_init(stack_T *s)         // Initialize empty stack
void stack_T_push(stack_T *s, T val)  // Push element onto stack
T stack_T_pop(stack_T *s)             // Pop and return top element
T stack_T_peek(stack_T *s)            // Peek at top element (non-destructive)
T stack_T_top(stack_T *s)             // Alias for peek
int stack_T_empty(stack_T *s)         // Check if stack is empty
size_t stack_T_size(stack_T *s)       // Get number of elements
void stack_T_free(stack_T *s)         // Free all memory
```

## 🏗️ Building

### Prerequisites
- C99 compliant compiler (GCC, Clang, MSVC)
- Make (optional, for examples)

### Compile Examples
```bash
# Build all examples
make

# Build specific example  
gcc -std=c99 -O2 -o example src/main.c -Iinclude

# With debug information
gcc -std=c99 -g -DDEBUG -o example src/main.c -Iinclude

# Example with warnings
gcc -std=c99 -Wall -Wextra -O2 -o example src/main.c -Iinclude
```

### Integration into Your Project
Since STL_C is header-only, simply:

1. Copy the `include/` directory to your project
2. Add `-Ipath/to/include` to your compiler flags  
3. Include `#include "stl.h"` in your source files

## 📊 Performance

STL_C is designed for high performance with the currently implemented data structures:

| Operation | Vector | Stack | Complexity |
|-----------|--------|-------|------------|
| Insert/Push | O(1)* | O(1)* | Amortized |
| Access/Peek | O(1) | O(1) | Constant |
| Remove/Pop | O(n) / O(1)* | O(1)* | Linear/Amortized |
| Search | O(n) | N/A | Linear |

*Amortized complexity due to dynamic resizing

### Memory Management
- **Growth Factor**: 2x (doubles capacity when full)
- **Shrink Factor**: 0.5x (halves when length ≤ capacity/4)
- **Initial Capacity**: 4 elements
- **Minimum Capacity**: 4 elements
- **Memory Overhead**: Typically 60-100% over minimum required

## 💡 Usage Examples

### Expression Evaluator (Stack)
```c
#include "include/stl.h"

DEFINE_VEC(double)
DEFINE_STACK(double)

double evaluate_postfix(const char* expr) {
    stack_double operands;
    stack_double_init(&operands);
    
    // Simplified: "3 4 + 2 *" evaluates to 14
    char* token = strtok(strdup(expr), " ");
    while (token) {
        if (strcmp(token, "+") == 0) {
            double b = stack_double_pop(&operands);
            double a = stack_double_pop(&operands);
            stack_double_push(&operands, a + b);
        } else {
            stack_double_push(&operands, atof(token));
        }
        token = strtok(NULL, " ");
    }
    
    double result = stack_double_pop(&operands);
    stack_double_free(&operands);
    return result;
}
```

### Dynamic Array Processing (Vector)
```c
#include "include/stl.h"

DEFINE_VEC(int)

void process_numbers() {
    vec_int numbers;
    vec_int_init(&numbers);
    
    // Read numbers from user
    printf("Enter numbers (0 to stop): ");
    int num;
    while (scanf("%d", &num) && num != 0) {
        vec_int_push(&numbers, num);
    }
    
    // Process the numbers
    printf("You entered %zu numbers:\n", numbers.len);
    for (size_t i = 0; i < numbers.len; i++) {
        printf("Index %zu: %d\n", i, vec_int_get(&numbers, i));
    }
    
    // Find maximum
    if (numbers.len > 0) {
        int max = vec_int_get(&numbers, 0);
        for (size_t i = 1; i < numbers.len; i++) {
            int current = vec_int_get(&numbers, i);
            if (current > max) max = current;
        }
        printf("Maximum: %d\n", max);
    }
    
    vec_int_free(&numbers);
}
```

## 🔧 Project Structure

```
STL_C/
├── include/
│   ├── stl.h         # Main header (includes all others)
│   ├── common.h      # Common includes and definitions
│   ├── vector.h      # Dynamic array implementation
│   ├── stack.h       # Stack implementation
│   ├── queue.h       # [Planned] Queue implementation  
│   ├── list.h        # [Planned] Linked list implementation
│   ├── set.h         # [Planned] Set implementation
│   └── hashmap.h     # [Planned] HashMap implementation
├── src/
│   ├── main.c        # Example usage and tests
│   ├── req1.c        # Additional examples
│   └── req2.c        # More examples
├── build/            # Build artifacts
├── README.md         # This file
└── Makefile          # Build configuration
```

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. **Implement new data structures**: Queue, List, Set, HashMap
2. **Add algorithms**: Sorting, searching, string processing
3. **Improve documentation**: Add examples, fix typos
4. **Performance optimizations**: Benchmark and optimize existing code
5. **Bug reports**: Report issues with existing implementations

### Development Guidelines
- Follow the existing macro-based generic programming pattern
- Use `static inline` for all generated functions
- Include comprehensive error handling
- Add usage examples for new features
- Maintain consistent naming conventions

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by C++ STL design principles
- Built for C developers who want modern data structures
- Focuses on performance and type safety

## 📈 Roadmap

### Version 1.0 
- ✅ Vector implementation
- ✅ Stack implementation
- ✅ Basic documentation
- ✅ Example programs

### Version 1.1
- ✅ Queue implementation
- ✅ Doubly-linked list implementation


### Version 2.0 (Current)
- ✅ Set implementation (balanced binary search tree)
- ✅ HashMap implementation (hash table)
- 🚧 Common algorithms (sort, search, etc.)

---

**STL_C** - Bringing modern data structures to C programming. Simple, fast, and type-safe.
