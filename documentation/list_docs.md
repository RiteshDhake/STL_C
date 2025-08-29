# Doubly-Linked List Documentation (list.h)

## Table of Contents
- [Overview](#overview)
- [Architecture](#architecture)
- [Core Macro](#core-macro)
- [Generated API](#generated-api)
- [Implementation Details](#implementation-details)
- [Performance Analysis](#performance-analysis)
- [Usage Examples](#usage-examples)
- [Memory Management](#memory-management)
- [Best Practices](#best-practices)
- [Common Use Cases](#common-use-cases)
- [Limitations](#limitations)

## Overview

The List library provides a generic doubly-linked list implementation in C. It supports efficient insertion and deletion at both ends, bidirectional traversal, and dynamic sizing. The implementation uses macros to generate type-safe list structures and functions for any data type.

### Key Features
- **Doubly-Linked**: Each node has pointers to both next and previous nodes
- **Head/Tail Pointers**: O(1) access to both ends of the list
- **Dynamic Size**: Automatically tracks the number of elements
- **Type Safety**: Macro-generated functions prevent type errors
- **Memory Efficient**: Only allocates memory as needed

## Architecture

The doubly-linked list maintains pointers to both head and tail nodes, with each node containing:

```
List Structure:
┌──────────────────┐
│ head  │ tail │ size │
└───┬──────┬───┬────┘
    │      │   └── Size counter
    │      └── Pointer to last node
    └── Pointer to first node

Node Chain:
NULL ← [prev|data|next] ⟷ [prev|data|next] ⟷ [prev|data|next] → NULL
       ^                                                      ^
       head                                                   tail
```

### Benefits of Doubly-Linked Design
1. **Bidirectional Traversal**: Can move forward or backward through the list
2. **Efficient Deletion**: Can remove nodes without traversing from head
3. **Tail Operations**: O(1) insertion/deletion at the end
4. **Flexible Navigation**: Easier implementation of complex algorithms

## Core Macro

```c
DEFINE_LIST(T, Name)
```

**Parameters:**
- `T` - The data type to store in the list
- `Name` - The name prefix for generated types and functions

**Generated Types:**
- `Name` - The list structure type
- `NameNode` - The node structure type

## Generated API

When you use `DEFINE_LIST(int, IntList)`, the following types and functions are generated:

### Data Structures
```c
struct IntListNode {
    int data;                    // The stored value
    struct IntListNode *next;    // Pointer to next node
    struct IntListNode *prev;    // Pointer to previous node
};
typedef struct IntListNode IntListNode;

struct IntList {
    IntListNode *head;    // Pointer to first node
    IntListNode *tail;    // Pointer to last node  
    size_t size;         // Number of elements
};
typedef struct IntList IntList;
```

### Core Functions

#### Initialization
```c
void IntList_init(IntList *l)
```
- **Purpose**: Initializes an empty list
- **Behavior**: Sets head and tail to NULL, size to 0
- **Time Complexity**: O(1)
- **Usage**: Must be called before any other operations

#### Size Operations
```c
size_t IntList_size(const IntList *l)
bool IntList_empty(const IntList *l)
```
- **Purpose**: Query list size and empty status
- **Return**: Current number of elements / boolean empty status
- **Time Complexity**: O(1)
- **Thread Safety**: Safe for read-only access

#### Insertion Operations

##### Push Back (Append)
```c
void IntList_push_back(IntList *l, int val)
```
- **Purpose**: Adds element to the end of the list
- **Behavior**: 
  - Creates new node with given value
  - Links it as the new tail
  - Updates tail pointer and size
- **Time Complexity**: O(1)
- **Memory**: Allocates one new node

##### Push Front (Prepend)  
```c
void IntList_push_front(IntList *l, int val)
```
- **Purpose**: Adds element to the beginning of the list
- **Behavior**:
  - Creates new node with given value  
  - Links it as the new head
  - Updates head pointer and size
- **Time Complexity**: O(1)
- **Memory**: Allocates one new node

#### Removal Operations

##### Pop Back
```c
int IntList_pop_back(IntList *l)
```
- **Purpose**: Removes and returns the last element
- **Return**: Value of the removed element
- **Behavior**: Updates tail pointer, decrements size, frees node
- **Time Complexity**: O(1)
- **Error**: Exits program if called on empty list

##### Pop Front
```c
int IntList_pop_front(IntList *l)  
```
- **Purpose**: Removes and returns the first element
- **Return**: Value of the removed element
- **Behavior**: Updates head pointer, decrements size, frees node
- **Time Complexity**: O(1)
- **Error**: Exits program if called on empty list

#### Cleanup Operations
```c
void IntList_clear(IntList *l)
```
- **Purpose**: Removes all elements from the list
- **Behavior**: Traverses list, frees all nodes, resets pointers
- **Time Complexity**: O(n)
- **Result**: Empty list ready for reuse

## Implementation Details

### Node Creation and Linking

#### Push Back Implementation
```c
void Name_push_back(Name *l, T val) {
    // 1. Allocate new node
    NameNode *node = malloc(sizeof(NameNode));
    if (!node) { perror("malloc"); exit(1); }
    
    // 2. Initialize node data
    node->data = val;
    node->next = NULL;           // New tail points to nothing
    node->prev = l->tail;        // New node's prev points to old tail
    
    // 3. Update existing tail's next pointer
    if (l->tail) 
        l->tail->next = node;    // Old tail points to new node
    else 
        l->head = node;          // List was empty, new node is also head
    
    // 4. Update list pointers
    l->tail = node;              // New node becomes tail
    l->size++;                   // Increment size
}
```

#### Push Front Implementation  
```c
void Name_push_front(Name *l, T val) {
    // 1. Allocate new node
    NameNode *node = malloc(sizeof(NameNode));
    if (!node) { perror("malloc"); exit(1); }
    
    // 2. Initialize node data
    node->data = val;
    node->prev = NULL;           // New head has no previous
    node->next = l->head;        // New node points to old head
    
    // 3. Update existing head's prev pointer
    if (l->head) 
        l->head->prev = node;    // Old head's prev points to new node
    else 
        l->tail = node;          // List was empty, new node is also tail
    
    // 4. Update list pointers
    l->head = node;              // New node becomes head
    l->size++;                   // Increment size
}
```

### Error Handling Strategy
```c
// Memory allocation failure
if (!node) { perror("malloc"); exit(1); }

// Empty list operations  
if (!l->tail) { fprintf(stderr, "pop_back on empty list\n"); exit(1); }
```
The library uses **fail-fast** error handling, terminating the program on critical errors.

## Performance Analysis

### Time Complexity Summary
| Operation | Complexity | Notes |
|-----------|------------|-------|
| `init` | O(1) | Simple pointer initialization |
| `push_back` | O(1) | Direct tail access |
| `push_front` | O(1) | Direct head access |
| `pop_back` | O(1) | Direct tail access |
| `pop_front` | O(1) | Direct head access |
| `size` | O(1) | Cached size value |
| `empty` | O(1) | Simple size check |
| `clear` | O(n) | Must traverse and free all nodes |

### Space Complexity
- **Storage**: O(n) for n elements
- **Overhead per node**: 2 pointers + data = 16 bytes + sizeof(T) on 64-bit systems
- **List overhead**: 2 pointers + size = 24 bytes on 64-bit systems

### Performance Comparison

| Data Structure | Insert Front | Insert Back | Remove Front | Remove Back | Random Access |
|----------------|--------------|-------------|--------------|-------------|---------------|
| **Doubly-Linked List** | O(1) | O(1) | O(1) | O(1) | O(n) |
| Array/Vector | O(n) | O(1)* | O(n) | O(1) | O(1) |
| Singly-Linked List | O(1) | O(n) | O(1) | O(n) | O(n) |

*Amortized complexity

## Usage Examples

### Basic Operations Example
```c
#include "list.h"

// Define an integer list type
DEFINE_LIST(int, IntList);

int main() {
    IntList numbers;
    IntList_init(&numbers);
    
    // Add elements to both ends
    IntList_push_back(&numbers, 10);   // [10]
    IntList_push_back(&numbers, 20);   // [10, 20]  
    IntList_push_front(&numbers, 5);   // [5, 10, 20]
    IntList_push_front(&numbers, 1);   // [1, 5, 10, 20]
    
    printf("List size: %zu\n", IntList_size(&numbers));  // Output: 4
    printf("Is empty: %s\n", IntList_empty(&numbers) ? "Yes" : "No");  // Output: No
    
    // Remove elements
    int back = IntList_pop_back(&numbers);    // back = 20, list = [1, 5, 10]
    int front = IntList_pop_front(&numbers);  // front = 1, list = [5, 10]
    
    printf("Removed from back: %d\n", back);   // Output: 20
    printf("Removed from front: %d\n", front); // Output: 1
    printf("Remaining size: %zu\n", IntList_size(&numbers));  // Output: 2
    
    // Cleanup
    IntList_clear(&numbers);
    printf("After clear size: %zu\n", IntList_size(&numbers));  // Output: 0
    
    return 0;
}
```

### String List Example
```c
#include "list.h"
#include <string.h>

// Define a string list type
DEFINE_LIST(char*, StringList);

int main() {
    StringList words;
    StringList_init(&words);
    
    // Add some words
    StringList_push_back(&words, "hello");
    StringList_push_back(&words, "world");
    StringList_push_front(&words, "hi");
    
    // Size: 3, Order: ["hi", "hello", "world"]
    printf("Word count: %zu\n", StringList_size(&words));
    
    // Remove words
    char* first = StringList_pop_front(&words);  // first = "hi"
    char* last = StringList_pop_back(&words);    // last = "world"  
    
    printf("First word: %s\n", first);
    printf("Last word: %s\n", last);
    // Remaining: ["hello"]
    
    StringList_clear(&words);
    return 0;
}
```

### Custom Structure Example
```c
#include "list.h"

typedef struct {
    int id;
    char name[50];
    double salary;
} Employee;

// Define employee list type
DEFINE_LIST(Employee, EmployeeList);

Employee create_employee(int id, const char* name, double salary) {
    Employee emp;
    emp.id = id;
    strncpy(emp.name, name, sizeof(emp.name) - 1);
    emp.name[sizeof(emp.name) - 1] = '\0';
    emp.salary = salary;
    return emp;
}

void print_employee(Employee emp) {
    printf("Employee{id=%d, name='%s', salary=%.2f}\n", 
           emp.id, emp.name, emp.salary);
}

int main() {
    EmployeeList staff;
    EmployeeList_init(&staff);
    
    // Add employees
    Employee john = create_employee(1, "John Doe", 75000.0);
    Employee jane = create_employee(2, "Jane Smith", 82000.0);
    Employee bob = create_employee(3, "Bob Johnson", 68000.0);
    
    EmployeeList_push_back(&staff, john);
    EmployeeList_push_back(&staff, jane);
    EmployeeList_push_front(&staff, bob);  // Bob becomes first
    
    printf("Staff size: %zu\n", EmployeeList_size(&staff));
    
    // Process employees (LIFO for recent hires)
    while (!EmployeeList_empty(&staff)) {
        Employee emp = EmployeeList_pop_front(&staff);
        print_employee(emp);
    }
    
    return 0;
}
```

### Stack Simulation Using List
```c
#include "list.h"

DEFINE_LIST(int, Stack);

// Stack operations using list functions
#define stack_push(stack, val) IntList_push_back(stack, val)
#define stack_pop(stack) IntList_pop_back(stack)
#define stack_top(stack) ((stack)->tail->data)  // Peek at top
#define stack_empty(stack) IntList_empty(stack)
#define stack_size(stack) IntList_size(stack)

int main() {
    Stack stack;
    IntList_init(&stack);
    
    // Push elements
    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);
    
    printf("Stack size: %zu\n", stack_size(&stack));  // Output: 3
    printf("Top element: %d\n", stack_top(&stack));   // Output: 30
    
    // Pop elements
    while (!stack_empty(&stack)) {
        int val = stack_pop(&stack);
        printf("Popped: %d\n", val);  // Output: 30, 20, 10
    }
    
    return 0;
}
```

### Deque (Double-Ended Queue) Usage
```c
#include "list.h"

DEFINE_LIST(char, CharDeque);

int main() {
    CharDeque deque;
    CharDeque_init(&deque);
    
    // Add elements to both ends
    CharDeque_push_back(&deque, 'B');   // ['B']
    CharDeque_push_back(&deque, 'C');   // ['B', 'C']
    CharDeque_push_front(&deque, 'A');  // ['A', 'B', 'C']
    CharDeque_push_back(&deque, 'D');   // ['A', 'B', 'C', 'D']
    
    // Remove from both ends
    char first = CharDeque_pop_front(&deque);  // first = 'A', deque = ['B', 'C', 'D']
    char last = CharDeque_pop_back(&deque);    // last = 'D', deque = ['B', 'C']
    
    printf("Removed first: %c, last: %c\n", first, last);
    printf("Remaining size: %zu\n", CharDeque_size(&deque));  // Output: 2
    
    CharDeque_clear(&deque);
    return 0;
}
```

## Memory Management

### Allocation Strategy
```c
// Node allocation with error checking
NameNode *node = malloc(sizeof(NameNode));
if (!node) { 
    perror("malloc"); 
    exit(1);
}
```

### Memory Layout
For a list of integers on a 64-bit system:
```
IntListNode structure:
┌─────────────────┬─────────────────┬─────────────────┐
│   int data      │  next pointer   │  prev pointer   │
│   4 bytes       │   8 bytes       │   8 bytes       │
└─────────────────┴─────────────────┴─────────────────┘
Total: 20 bytes + padding = ~24 bytes per node
```

### Memory Safety Features
1. **Allocation Check**: Every malloc is checked for failure
2. **Fail-Fast**: Program terminates on memory allocation failure
3. **Complete Cleanup**: `clear()` function frees all allocated nodes
4. **No Memory Leaks**: Proper pointer management prevents leaks

### Cleanup Patterns
```c
// Pattern 1: Clear and reuse
IntList_clear(&list);           // Removes all elements
IntList_push_back(&list, 42);   // List can be reused

// Pattern 2: One-time use
IntList temp_list;
IntList_init(&temp_list);
// ... use list ...
IntList_clear(&temp_list);      // Clean up when done
```

## Best Practices

### 1. Always Initialize
```c
// Correct
IntList mylist;
IntList_init(&mylist);  // Essential!

// Incorrect - undefined behavior
IntList mylist;  // Uninitialized pointers
IntList_push_back(&mylist, 42);  // May crash
```

### 2. Check Empty Before Popping
```c
// Safe approach
if (!IntList_empty(&list)) {
    int value = IntList_pop_back(&list);
    printf("Popped: %d\n", value);
} else {
    printf("List is empty\n");
}

// Or use size check
if (IntList_size(&list) > 0) {
    int value = IntList_pop_front(&list);
    // ...
}
```

### 3. Efficient Batch Operations
```c
// Efficient: build list from one end
for (int i = 0; i < 1000; i++) {
    IntList_push_back(&list, i);  // O(1) each = O(n) total
}

// Less efficient but valid
for (int i = 999; i >= 0; i--) {
    IntList_push_front(&list, i);  // Same result, different approach
}
```

### 4. Memory Management Best Practices
```c
void process_data() {
    IntList local_list;
    IntList_init(&local_list);
    
    // ... use list ...
    
    // Always clean up before function exit
    IntList_clear(&local_list);
}  // No memory leaks
```

### 5. String Lists Require Special Care
```c
DEFINE_LIST(char*, StringList);

int main() {
    StringList words;
    StringList_init(&words);
    
    // Safe: string literals (stored in program memory)
    StringList_push_back(&words, "hello");
    StringList_push_back(&words, "world");
    
    // Safe: dynamically allocated strings
    char* dynamic_str = strdup("dynamic");
    StringList_push_back(&words, dynamic_str);
    
    // Dangerous: stack-allocated strings
    char local_str[100];
    strcpy(local_str, "local");
    StringList_push_back(&words, local_str);  // Pointer may become invalid!
    
    StringList_clear(&words);
    // Note: For dynamically allocated strings, you need to free them separately
    free(dynamic_str);
    
    return 0;
}
```

## Common Use Cases

### 1. Undo/Redo System
```c
DEFINE_LIST(char*, CommandList);

typedef struct {
    CommandList undo_stack;
    CommandList redo_stack;
} UndoRedoSystem;

void init_undo_redo(UndoRedoSystem* sys) {
    CommandList_init(&sys->undo_stack);
    CommandList_init(&sys->redo_stack);
}

void execute_command(UndoRedoSystem* sys, char* command) {
    // Execute the command...
    
    // Add to undo stack
    CommandList_push_back(&sys->undo_stack, command);
    
    // Clear redo stack (new action invalidates redo history)
    CommandList_clear(&sys->redo_stack);
}

void undo(UndoRedoSystem* sys) {
    if (!CommandList_empty(&sys->undo_stack)) {
        char* command = CommandList_pop_back(&sys->undo_stack);
        CommandList_push_back(&sys->redo_stack, command);
        // Undo the command...
    }
}

void redo(UndoRedoSystem* sys) {
    if (!CommandList_empty(&sys->redo_stack)) {
        char* command = CommandList_pop_back(&sys->redo_stack);
        CommandList_push_back(&sys->undo_stack, command);
        // Redo the command...
    }
}
```

### 2. Recent Items Cache (LRU-like)
```c
#define MAX_RECENT_ITEMS 10

DEFINE_LIST(int, RecentList);

void add_recent_item(RecentList* recent, int item) {
    // Add to front (most recent)
    RecentList_push_front(recent, item);
    
    // Limit size
    while (RecentList_size(recent) > MAX_RECENT_ITEMS) {
        RecentList_pop_back(recent);  // Remove oldest
    }
}

void show_recent_items(RecentList* recent) {
    printf("Recent items (newest first):\n");
    // Manual traversal would require extending the API
    // For now, we can only access via pop operations
}
```

### 3. Music Playlist
```c
typedef struct {
    char title[100];
    char artist[100];
    int duration_seconds;
} Song;

DEFINE_LIST(Song, Playlist);

Song create_song(const char* title, const char* artist, int duration) {
    Song song;
    strncpy(song.title, title, sizeof(song.title) - 1);
    strncpy(song.artist, artist, sizeof(song.artist) - 1);
    song.title[sizeof(song.title) - 1] = '\0';
    song.artist[sizeof(song.artist) - 1] = '\0';
    song.duration_seconds = duration;
    return song;
}

int main() {
    Playlist my_playlist;
    Playlist_init(&my_playlist);
    
    // Add songs
    Song song1 = create_song("Bohemian Rhapsody", "Queen", 355);
    Song song2 = create_song("Hotel California", "Eagles", 391);
    Song song3 = create_song("Imagine", "John Lennon", 183);
    
    Playlist_push_back(&my_playlist, song1);
    Playlist_push_back(&my_playlist, song2);
    Playlist_push_back(&my_playlist, song3);
    
    printf("Playlist has %zu songs\n", Playlist_size(&my_playlist));
    
    // Play songs (remove from front)
    while (!Playlist_empty(&my_playlist)) {
        Song current = Playlist_pop_front(&my_playlist);
        printf("Now playing: %s by %s (%d:%02d)\n", 
               current.title, current.artist,
               current.duration_seconds / 60, 
               current.duration_seconds % 60);
    }
    
    return 0;
}
```

### 4. Browser History Implementation
```c
DEFINE_LIST(char*, BrowserHistory);

typedef struct {
    BrowserHistory history;
    size_t current_position;  // Not directly supported, would need extension
} Browser;

void visit_page(BrowserHistory* history, char* url) {
    StringList_push_back(history, url);
    printf("Visited: %s\n", url);
}

char* go_back(BrowserHistory* history) {
    if (StringList_size(history) > 1) {
        StringList_pop_back(history);  // Remove current page
        // Would need additional logic to maintain current position
        // This is a simplified example
    }
    return "previous_page";  // Placeholder
}
```

## Limitations

### 1. No Random Access
```c
// Cannot do this efficiently:
// int third_element = IntList_get(&list, 2);  // Not available

// Must traverse manually:
IntListNode* node = list.head;
for (int i = 0; i < 2 && node; i++) {
    node = node->next;
}
if (node) {
    int third_element = node->data;
}
```

### 2. No Built-in Iterator
The library doesn't provide iterator functions. To traverse:

```c
// Manual traversal (requires exposing internal structure)
IntListNode* current = list.head;
while (current) {
    printf("%d ", current->data);
    current = current->next;
}
```

### 3. No Insert/Remove at Arbitrary Position
```c
// These operations are not provided:
// IntList_insert(&list, index, value);
// IntList_remove_at(&list, index);
// int value = IntList_get(&list, index);
```

### 4. Error Handling Limitations
- **Fatal Errors**: Memory allocation failures terminate the program
- **Pop on Empty**: Causes program termination rather than returning error codes
- **No Graceful Degradation**: Limited options for error recovery

### 5. Thread Safety
- **Not Thread-Safe**: Concurrent access requires external synchronization
- **Critical Sections**: All operations that modify pointers need protection
- **Size Counter**: The size field is particularly vulnerable to race conditions

## Extension Possibilities

### Adding Iterator Support
```c
// Could extend with iterator functions:
typedef struct {
    NameNode* current;
    Name* list;
} NameIterator;

NameIterator Name_begin(Name* list);
NameIterator Name_end(Name* list);
bool Name_iterator_has_next(NameIterator* it);
T Name_iterator_next(NameIterator* it);
```

### Adding Search Functionality
```c
// Could add search functions:
bool Name_contains(Name* list, T value);
NameNode* Name_find(Name* list, T value);
size_t Name_index_of(Name* list, T value);
```

### Adding Insertion at Position
```c
// Could add positional operations:
void Name_insert_at(Name* list, size_t index, T value);
T Name_remove_at(Name* list, size_t index);
T Name_get_at(Name* list, size_t index);
```

## Advanced Usage Patterns

### 1. List Copying
```c
IntList copy_list(IntList* original) {
    IntList copy;
    IntList_init(&copy);
    
    // Manual copy (no built-in copy function)
    IntListNode* current = original->head;
    while (current) {
        IntList_push_back(&copy, current->data);
        current = current->next;
    }
    
    return copy;
}
```

### 2. List Reversal
```c
void reverse_list_contents(IntList* list) {
    if (IntList_size(list) <= 1) return;
    
    IntList temp;
    IntList_init(&temp);
    
    // Move all elements to temporary list (reverses order)
    while (!IntList_empty(list)) {
        int val = IntList_pop_back(list);
        IntList_push_back(&temp, val);
    }
    
    // Move back to original list
    while (!IntList_empty(&temp)) {
        int val = IntList_pop_back(&temp);
        IntList_push_back(list, val);
    }
}
```

This doubly-linked list implementation provides an efficient foundation for algorithms requiring frequent insertion and deletion at the ends, with the flexibility to work with any data type while maintaining type safety.