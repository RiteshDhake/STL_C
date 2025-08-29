# Stack Data Structure (`stack.h`)

A generic, type-safe stack implementation in C using preprocessor macros. This stack provides LIFO (Last In, First Out) access to elements and is built on top of a dynamic vector for efficient memory management.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Dependencies](#dependencies)
- [Type Generation](#type-generation)
- [Data Structure](#data-structure)
- [API Reference](#api-reference)
- [Memory Management](#memory-management)
- [Performance Analysis](#performance-analysis)
- [Error Handling](#error-handling)
- [Usage Examples](#usage-examples)
- [Implementation Details](#implementation-details)
- [Best Practices](#best-practices)

## Overview

The stack implementation provides a traditional LIFO container that automatically manages its memory through an underlying dynamic vector. It offers constant-time push and pop operations with amortized complexity, making it suitable for high-performance applications that require stack semantics.

### Key Characteristics

- **Generic**: Works with any C data type
- **Type-Safe**: Compile-time type checking prevents type errors
- **Memory Efficient**: Automatic capacity management with shrinking
- **High Performance**: Static inline functions enable compiler optimizations
- **LIFO Semantics**: Classic stack behavior (Last In, First Out)
- **Vector-Based**: Leverages proven dynamic array implementation

## Features

- **Automatic Memory Management**: Grows and shrinks capacity as needed
- **Type Safety**: Generated functions are type-specific at compile time
- **Zero Dependencies**: Only requires standard C library and vector.h
- **Header-Only**: Simple integration into existing projects
- **Consistent API**: Follows standard stack operation naming conventions
- **Error Reporting**: Built-in bounds checking with error messages

## Dependencies

```c
#include "common.h"   // Standard C library includes
#include "vector.h"   // Dynamic vector implementation
```

**Prerequisites**:
- `DEFINE_VEC(T)` must be called before `DEFINE_STACK(T)` for the same type `T`
- `common.h` must provide standard includes (`<stdlib.h>`, `<stdio.h>`, etc.)

## Type Generation

### Macro Definition

```c
DEFINE_STACK(T)
```

**Purpose**: Generates a complete stack implementation for type `T`.

**What it creates**:
- `stack_T` structure type
- Complete set of `stack_T_*` functions
- All functions are declared as `static inline`

**Example**:
```c
DEFINE_VEC(int)      // Must be called first
DEFINE_STACK(int)    // Creates stack_int type and functions
```

**Naming Convention**:
- Structure: `stack_<typename>`
- Functions: `stack_<typename>_<operation>`

## Data Structure

### Structure Definition

```c
typedef struct {
    vec_T data;    // Underlying vector storage
} stack_T;
```

### Memory Layout

```
Stack (Conceptual View):
┌─────────────────┐ ← Top (last element)
│       E         │
├─────────────────┤
│       D         │
├─────────────────┤
│       C         │
├─────────────────┤
│       B         │
├─────────────────┤
│       A         │ ← Bottom (first element)
└─────────────────┘

Actual Memory Layout (via underlying vector):
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  A  │  B  │  C  │  D  │  E  │     │     │     │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  0     1     2     3     4     5     6     7
                          ↑                     ↑
                        len=5                cap=8
                         top
```

### Capacity Management

- **Initial Capacity**: 4 elements (inherited from vector)
- **Growth Strategy**: Doubles when full
- **Shrink Strategy**: Halves when length ≤ capacity/4
- **Minimum Capacity**: 4 elements

## API Reference

### Initialization

#### `void stack_T_init(stack_T *s)`

**Description**: Initializes an empty stack.

**Parameters**:
- `s`: Pointer to the stack structure to initialize

**Behavior**:
- Sets length to 0
- Sets capacity to 0  
- Sets data pointer to NULL
- No memory allocation performed

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Example**:
```c
stack_int my_stack;
stack_int_init(&my_stack);  // Stack is now ready for use
```

**Preconditions**: None  
**Postconditions**: Stack is empty and ready for operations

---

### Adding Elements

#### `void stack_T_push(stack_T *s, T value)`

**Description**: Pushes an element onto the top of the stack.

**Parameters**:
- `s`: Pointer to the stack
- `value`: Element to add to the top of the stack

**Behavior**:
- Adds element to the end of underlying vector
- Automatically grows capacity if needed
- Element becomes the new top of stack

**Time Complexity**: 
- **Average**: O(1) amortized
- **Worst Case**: O(n) when reallocation occurs

**Space Complexity**: O(1) additional space

**Memory Operations**:
- May trigger reallocation if `len >= cap`
- New capacity = `(cap == 0) ? 4 : cap * 2`
- Uses `realloc()` for efficiency

**Example**:
```c
stack_int s;
stack_int_init(&s);
stack_int_push(&s, 10);  // Stack: [10]
stack_int_push(&s, 20);  // Stack: [10, 20] (20 is top)
stack_int_push(&s, 30);  // Stack: [10, 20, 30] (30 is top)
```

**Error Conditions**:
- Memory allocation failure: Prints error and returns without adding element

---

### Removing Elements

#### `T stack_T_pop(stack_T *s)`

**Description**: Removes and returns the top element from the stack.

**Parameters**:
- `s`: Pointer to the stack

**Returns**: 
- Top element if stack is not empty
- Zero-initialized value (`{0}`) if stack is empty

**Behavior**:
- Retrieves top element before removal
- Decrements stack length
- May shrink capacity to save memory
- Does NOT call destructors (for complex types)

**Time Complexity**:
- **Average**: O(1) amortized  
- **Worst Case**: O(n) when reallocation occurs during shrinking

**Space Complexity**: O(1)

**Memory Operations**:
- Shrinks when `len > 0 && len <= cap/4`
- New capacity = `max(cap/2, 4)`
- Uses `realloc()` for efficiency

**Example**:
```c
stack_int s;
stack_int_init(&s);
stack_int_push(&s, 10);
stack_int_push(&s, 20);

int top = stack_int_pop(&s);  // Returns 20, stack: [10]
int next = stack_int_pop(&s); // Returns 10, stack: []
int empty = stack_int_pop(&s); // Returns 0, prints "Stack underflow"
```

**Error Conditions**:
- Empty stack: Prints "Stack underflow" and returns zero-initialized value
- Reallocation failure during shrinking: Continues with old capacity

---

### Accessing Elements

#### `T stack_T_peek(stack_T *s)`

**Description**: Returns the top element without removing it from the stack.

**Parameters**:
- `s`: Pointer to the stack

**Returns**:
- Top element if stack is not empty
- Zero-initialized value (`{0}`) if stack is empty

**Behavior**:
- Non-destructive read of top element
- Stack remains unchanged
- Useful for examining top without committing to removal

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Example**:
```c
stack_int s;
stack_int_init(&s);
stack_int_push(&s, 42);

int top = stack_int_peek(&s);  // Returns 42, stack unchanged: [42]
int same = stack_int_peek(&s); // Returns 42 again, stack: [42]
```

**Error Conditions**:
- Empty stack: Prints "Stack is empty" and returns zero-initialized value

---

#### `T stack_T_top(stack_T *s)`

**Description**: Alias for `stack_T_peek()`. Returns the top element without removing it.

**Parameters**:
- `s`: Pointer to the stack

**Returns**: Same as `stack_T_peek()`

**Behavior**: Identical to `stack_T_peek()`

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Usage**: Provides familiar naming for users expecting `top()` method

**Example**:
```c
int value = stack_int_top(&s);    // Same as stack_int_peek(&s)
```

---

### Stack Properties

#### `int stack_T_empty(stack_T *s)`

**Description**: Checks whether the stack is empty.

**Parameters**:
- `s`: Pointer to the stack

**Returns**:
- **Non-zero** (true) if stack is empty
- **Zero** (false) if stack contains elements

**Behavior**:
- Tests if length equals zero
- Does not modify the stack

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Example**:
```c
stack_int s;
stack_int_init(&s);

if (stack_int_empty(&s)) {
    printf("Stack is empty\n");  // This will print
}

stack_int_push(&s, 10);

if (!stack_int_empty(&s)) {
    printf("Stack has elements\n");  // This will print
}
```

**Use Cases**:
- Loop termination conditions
- Precondition checks before pop/peek operations
- Algorithm state checking

---

#### `size_t stack_T_size(stack_T *s)`

**Description**: Returns the number of elements currently in the stack.

**Parameters**:
- `s`: Pointer to the stack

**Returns**: Number of elements in the stack (0 to SIZE_MAX)

**Behavior**:
- Returns the current length of underlying vector
- Does not modify the stack

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Example**:
```c
stack_int s;
stack_int_init(&s);

printf("Size: %zu\n", stack_int_size(&s));  // Prints: Size: 0

stack_int_push(&s, 1);
stack_int_push(&s, 2);
stack_int_push(&s, 3);

printf("Size: %zu\n", stack_int_size(&s));  // Prints: Size: 3
```

**Use Cases**:
- Memory usage calculations
- Loop bounds
- Algorithm complexity analysis
- Debugging and logging

---

### Cleanup

#### `void stack_T_free(stack_T *s)`

**Description**: Releases all memory associated with the stack.

**Parameters**:
- `s`: Pointer to the stack to deallocate

**Behavior**:
- Calls `free()` on internal data array
- Resets all fields to safe values
- Stack becomes invalid for further operations

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

**Post-conditions**:
- `s->data.data == NULL`
- `s->data.len == 0`
- `s->data.cap == 0`

**Example**:
```c
stack_int s;
stack_int_init(&s);
stack_int_push(&s, 42);

stack_int_free(&s);  // Memory released, stack invalid

// Must re-initialize before reuse
stack_int_init(&s);  // Now safe to use again
```

**Important Notes**:
- **Must be called** to prevent memory leaks
- Stack must be re-initialized before reuse
- Does not call destructors for complex types
- Safe to call on already-freed or uninitialized stacks

---

## Memory Management

### Allocation Strategy

The stack inherits the vector's sophisticated memory management:

```
Capacity Progression Example:
Initial: cap=0, len=0
After 1 push: cap=4, len=1    [X _ _ _]
After 4 pushes: cap=4, len=4  [X X X X]
After 5 pushes: cap=8, len=5  [X X X X X _ _ _]
After 8 pushes: cap=8, len=8  [X X X X X X X X]
After 9 pushes: cap=16, len=9 [X X X X X X X X X _ _ _ _ _ _ _]
```

### Growth Behavior

**Trigger**: When `length >= capacity`  
**New Capacity**: `(capacity == 0) ? 4 : capacity * 2`  
**Memory Operation**: `realloc(data, new_capacity * sizeof(T))`

### Shrink Behavior

**Trigger**: When `length > 0 && length <= capacity/4`  
**New Capacity**: `max(capacity/2, 4)`  
**Memory Operation**: `realloc(data, new_capacity * sizeof(T))`

### Memory Efficiency Analysis

| State | Length | Capacity | Load Factor | Memory Overhead |
|-------|--------|----------|-------------|-----------------|
| Just grown | n | 2n | 50% | 100% |
| Full | n | n | 100% | 0% |
| After shrink | n | 4n | 25% | 300% |

**Average Load Factor**: ~62.5%  
**Memory Overhead**: Typically 60-100% over minimum required

## Performance Analysis

### Time Complexity Summary

| Operation | Best Case | Average Case | Worst Case | Amortized |
|-----------|-----------|--------------|------------|-----------|
| `push` | O(1) | O(1) | O(n) | O(1) |
| `pop` | O(1) | O(1) | O(n) | O(1) |
| `peek`/`top` | O(1) | O(1) | O(1) | O(1) |
| `empty` | O(1) | O(1) | O(1) | O(1) |
| `size` | O(1) | O(1) | O(1) | O(1) |
| `free` | O(1) | O(1) | O(1) | O(1) |

### Amortized Analysis

For a sequence of n `push` operations starting from an empty stack:

- **Total reallocations**: ⌊log₂(n/4)⌋ + 1
- **Total elements copied**: 4 + 8 + 16 + ... + largest_power_of_2 ≤ n < 2n
- **Amortized cost per push**: (n + 2n)/n = O(1)

### Space Complexity

- **Worst-case space**: O(2n) where n is the number of elements
- **Best-case space**: O(n) when stack is full
- **Average space**: O(1.6n) considering typical load factors

### Performance Optimizations

1. **Static Inline Functions**: Enable compiler optimizations
2. **Minimal Indirection**: Direct array access for top element
3. **Efficient Reallocation**: Uses `realloc()` for memory efficiency  
4. **Predictable Growth**: Powers of 2 improve allocator performance
5. **Lazy Shrinking**: Prevents thrashing around capacity boundaries

## Error Handling

### Error Types and Responses

| Error Condition | Function | Response | Return Value |
|-----------------|----------|----------|--------------|
| Empty stack | `pop` | Print "Stack underflow" | `{0}` |
| Empty stack | `peek`/`top` | Print "Stack is empty" | `{0}` |
| Allocation failure | `push` | Print "Memory allocation failed" | No change |
| Shrink failure | `pop` | Silent (continues with old capacity) | Normal |

### Error Handling Philosophy

The implementation follows a **defensive programming** approach:

- **Graceful Degradation**: Operations fail safely without crashing
- **User Notification**: Error messages printed to `stdout`
- **Safe Returns**: Zero-initialized values for failed reads
- **State Preservation**: Stack remains in valid state after errors

### Custom Error Handling

For production code, you may want to modify the error handling:

```c
// Instead of printf, could use:
// - Custom logging functions
// - Error codes or global error state
// - Assertions for debug builds
// - Exception-like mechanisms
```

## Usage Examples

### Basic Stack Operations

```c
#include "common.h"
#include "vector.h"
#include "stack.h"

// Generate the required types
DEFINE_VEC(int)
DEFINE_STACK(int)

int main() {
    stack_int calc_stack;
    stack_int_init(&calc_stack);
    
    // Push some values
    printf("Pushing: 10, 20, 30\n");
    stack_int_push(&calc_stack, 10);
    stack_int_push(&calc_stack, 20);
    stack_int_push(&calc_stack, 30);
    
    printf("Stack size: %zu\n", stack_int_size(&calc_stack));
    printf("Top element: %d\n", stack_int_peek(&calc_stack));
    
    // Pop all values
    printf("Popping values:\n");
    while (!stack_int_empty(&calc_stack)) {
        printf("  %d\n", stack_int_pop(&calc_stack));
    }
    
    printf("Final size: %zu\n", stack_int_size(&calc_stack));
    
    // Cleanup
    stack_int_free(&calc_stack);
    return 0;
}

/* Output:
Pushing: 10, 20, 30
Stack size: 3
Top element: 30
Popping values:
  30
  20
  10
Final size: 0
*/
```

### Expression Evaluation (Postfix Calculator)

```c
#include "common.h"
#include "vector.h" 
#include "stack.h"

DEFINE_VEC(double)
DEFINE_STACK(double)

double evaluate_postfix(const char* expression) {
    stack_double operands;
    stack_double_init(&operands);
    
    // Simplified tokenization (space-separated)
    char* expr_copy = strdup(expression);
    char* token = strtok(expr_copy, " ");
    
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            double b = stack_double_pop(&operands);
            double a = stack_double_pop(&operands);
            stack_double_push(&operands, a + b);
        }
        else if (strcmp(token, "-") == 0) {
            double b = stack_double_pop(&operands);
            double a = stack_double_pop(&operands);
            stack_double_push(&operands, a - b);
        }
        else if (strcmp(token, "*") == 0) {
            double b = stack_double_pop(&operands);
            double a = stack_double_pop(&operands);
            stack_double_push(&operands, a * b);
        }
        else if (strcmp(token, "/") == 0) {
            double b = stack_double_pop(&operands);
            double a = stack_double_pop(&operands);
            stack_double_push(&operands, a / b);
        }
        else {
            // Assume it's a number
            double value = atof(token);
            stack_double_push(&operands, value);
        }
        token = strtok(NULL, " ");
    }
    
    double result = stack_double_pop(&operands);
    
    free(expr_copy);
    stack_double_free(&operands);
    return result;
}

int main() {
    // Test postfix expressions
    printf("3 4 + 2 * = %.2f\n", evaluate_postfix("3 4 + 2 *"));  // (3+4)*2 = 14
    printf("15 7 1 1 + - / 3 * 2 1 1 + + - = %.2f\n", 
           evaluate_postfix("15 7 1 1 + - / 3 * 2 1 1 + + -"));    // Complex expression
    return 0;
}
```

### Balanced Parentheses Checker

```c
#include "common.h"
#include "vector.h"
#include "stack.h"

DEFINE_VEC(char)
DEFINE_STACK(char)

int is_balanced(const char* expression) {
    stack_char brackets;
    stack_char_init(&brackets);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        // Push opening brackets
        if (ch == '(' || ch == '[' || ch == '{') {
            stack_char_push(&brackets, ch);
        }
        // Check closing brackets
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack_char_empty(&brackets)) {
                stack_char_free(&brackets);
                return 0;  // Unmatched closing bracket
            }
            
            char top = stack_char_pop(&brackets);
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                stack_char_free(&brackets);
                return 0;  // Mismatched brackets
            }
        }
    }
    
    int balanced = stack_char_empty(&brackets);
    stack_char_free(&brackets);
    return balanced;
}

int main() {
    const char* test_cases[] = {
        "(())",           // Balanced
        "([{}])",         // Balanced
        "(((",            // Unbalanced
        "())",            // Unbalanced
        "{[()]}",         // Balanced
        "{[(])}",         // Mismatched
        "",               // Balanced (empty)
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("'%s' is %s\n", test_cases[i], 
               is_balanced(test_cases[i]) ? "balanced" : "not balanced");
    }
    
    return 0;
}
```

### Function Call Stack Simulation

```c
typedef struct {
    char function_name[32];
    int line_number;
    int local_vars[4];  // Simplified local variables
} StackFrame;

DEFINE_VEC(StackFrame)
DEFINE_STACK(StackFrame)

void print_call_stack(stack_StackFrame* call_stack) {
    printf("Call Stack (top to bottom):\n");
    
    // Create a temporary stack to preserve original
    stack_StackFrame temp;
    stack_StackFrame_init(&temp);
    
    // Copy to temp stack (reversing order)
    while (!stack_StackFrame_empty(call_stack)) {
        stack_StackFrame_push(&temp, stack_StackFrame_pop(call_stack));
    }
    
    // Print and restore original
    int depth = 0;
    while (!stack_StackFrame_empty(&temp)) {
        StackFrame frame = stack_StackFrame_pop(&temp);
        printf("  #%d %s() at line %d\n", depth++, frame.function_name, frame.line_number);
        stack_StackFrame_push(call_stack, frame);  // Restore to original
    }
    
    stack_StackFrame_free(&temp);
}

int main() {
    stack_StackFrame call_stack;
    stack_StackFrame_init(&call_stack);
    
    // Simulate function calls
    StackFrame main_frame = {"main", 45, {0}};
    stack_StackFrame_push(&call_stack, main_frame);
    
    StackFrame foo_frame = {"foo", 23, {1, 2}};
    stack_StackFrame_push(&call_stack, foo_frame);
    
    StackFrame bar_frame = {"bar", 67, {3, 4, 5}};
    stack_StackFrame_push(&call_stack, bar_frame);
    
    print_call_stack(&call_stack);
    
    // Simulate function return
    printf("\nAfter bar() returns:\n");
    stack_StackFrame_pop(&call_stack);
    print_call_stack(&call_stack);
    
    stack_StackFrame_free(&call_stack);
    return 0;
}
```

## Implementation Details

### Macro Expansion

When you call `DEFINE_STACK(int)`, the preprocessor generates:

```c
typedef struct { 
    vec_int data; 
} stack_int;

static inline void stack_int_init(stack_int *s) { 
    vec_int_init(&s->data); 
}

static inline void stack_int_push(stack_int *s, int value) { 
    vec_int_push(&s->data, value); 
}

// ... (all other functions expanded similarly)
```

### Why Static Inline?

1. **Performance**: Function calls are inlined at compile time
2. **Type Safety**: Each instantiation creates type-specific functions
3. **Linkage**: `static` prevents symbol conflicts between translation units
4. **Optimization**: Enables aggressive compiler optimizations

### Vector Dependency

The stack implementation is a **thin wrapper** around the vector:

```c
stack_T_push(s, val) → vec_T_push(&s->data, val)
stack_T_pop(s) → custom logic + vec length manipulation  
stack_T_peek(s) → direct access to vec_T_data[len-1]
```

This design provides:
- **Code Reuse**: Leverages proven vector implementation
- **Consistency**: Same memory management behavior
- **Maintainability**: Changes to vector benefit stack automatically
- **Performance**: No additional abstraction overhead

## Best Practices

### Memory Management

```c
// ✅ Good: Proper initialization and cleanup
void process_stack_data() {
    stack_int numbers;
    stack_int_init(&numbers);    // Always initialize
    
    // Use the stack...
    
    stack_int_free(&numbers);    // Always cleanup
}

// ❌ Bad: Missing initialization
void bad_example() {
    stack_int numbers;  // Uninitialized!
    stack_int_push(&numbers, 42);  // Undefined behavior
}
```

### Error Handling

```c
// ✅ Good: Check for empty before pop
if (!stack_int_empty(&s)) {
    int value = stack_int_pop(&s);
    // Use value...
} else {
    // Handle empty stack case
}

// ✅ Good: Use peek for non-destructive access
if (!stack_int_empty(&s)) {
    int top = stack_int_peek(&s);
    if (should_process(top)) {
        stack_int_pop(&s);  // Now remove it
        process(top);
    }
}
```

### Performance Considerations

```c
// ✅ Good: Check size once for batch operations
size_t count = stack_int_size(&s);
for (size_t i = 0; i < count; i++) {
    process(stack_int_pop(&s));
}

// ❌ Inefficient: Repeated size calls
while (stack_int_size(&s) > 0) {  // size() called every iteration
    process(stack_int_pop(&s));
}

// ✅ Better: Use empty() check
while (!stack_int_empty(&s)) {    // More direct check
    process(stack_int_pop(&s));
}
```

### Type Definitions

```c
// ✅ Good: Define in header for shared use
// In your_stack_types.h:
DEFINE_VEC(int)
DEFINE_STACK(int)

// ✅ Good: Consistent custom type naming
typedef struct { double x, y; } Point2D;
DEFINE_VEC(Point2D)
DEFINE_STACK(Point2D)    // Creates stack_Point2D
```

### Thread Safety

**Important**: This implementation is **NOT thread-safe**.

For concurrent access:
```c
// ✅ Use external synchronization
pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER;

void thread_safe_push(stack_int* s, int value) {
    pthread_mutex_lock(&stack_mutex);
    stack_int_push(s, value);
    pthread_mutex_unlock(&stack_mutex);
}

// ✅ Consider per-thread stacks
__thread stack_int thread_local_stack;  // Each thread has its own
```

### Debugging Tips

```c
// ✅ Good: Add debug printing
void debug_print_stack(stack_int* s) {
    printf("Stack (size=%zu, cap=%zu): [", 
           stack_int_size(s), s->data.cap);
    
    // Print from bottom to top
    for (size_t i = 0; i < s->data.len; i++) {
        printf("%d", s->data.data[i]);
        if (i < s->data.len - 1) printf(", ");
    }
    printf("] (top: %s)\n", 
           stack_int_empty(s) ? "empty" : "rightmost");
}
```

This comprehensive documentation provides everything needed to understand and effectively use the stack implementation, from basic usage to advanced performance considerations.