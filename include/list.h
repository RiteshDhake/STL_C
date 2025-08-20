#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

// ==== Function pointer types for generic operations ====
typedef void (*list_destructor)(void *data);
typedef int  (*list_compare)(const void *a, const void *b);
typedef void* (*list_copy_func)(const void *data);
typedef void (*list_printer)(const void *data);

// ==== Node structure ====
typedef struct ListNode {
    void *data;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

// ==== List structure ====
typedef struct {
    ListNode *head;
    ListNode *tail;
    size_t size;
    size_t element_size;
    list_destructor destructor;
    list_copy_func copy_func;
    list_compare compare_func;
} List;

// ==== Iterator ====
typedef struct {
    ListNode *current;
    List *list;
} list_iterator;

// ==== Core functions ====
List* list(size_t element_size,
           list_destructor destructor,
           list_copy_func copy_func,
           list_compare compare_func);

void list_clear(List *list);
void list_destroy(List *list);

// ==== Size / capacity ====
size_t list_size(const List *list);
bool list_empty(const List *list);

// ==== Element access ====
void* list_front(const List *list);
void* list_back(const List *list);
void* list_at(const List *list, size_t index);

// ==== Modifiers ====
bool list_push_front(List *list, const void *data);
bool list_push_back(List *list, const void *data);
bool list_pop_front(List *list);
bool list_pop_back(List *list);
bool list_insert(List *list, size_t index, const void *data);
bool list_erase(List *list, size_t index);
bool list_remove(List *list, const void *data);

// ==== Search ====
list_iterator list_find(List *list, const void *data);
bool list_contains(List *list, const void *data);

// ==== Iterators ====
list_iterator list_begin(List *list);
list_iterator list_end(List *list);
list_iterator list_rbegin(List *list);
list_iterator list_rend(List *list);

bool list_iterator_valid(const list_iterator *it);
void* list_iterator_data(const list_iterator *it);
list_iterator list_iterator_next(const list_iterator *it);
list_iterator list_iterator_prev(const list_iterator *it);

// ==== Utilities ====
void list_print(const List *list, list_printer print_func);
List* list_copy(const List *list);
void list_reverse(List *list);
void list_sort(List *list);

// ==== Helper macros for type safety ====

#define LIST_PUSH_BACK(list, value) \
    list_push_back(list, &(value))

#define LIST_PUSH_FRONT(list, value) \
    list_push_front(list, &(value))

#define LIST_GET(list, index, type) \
    (*((type*)list_at(list, index)))

// Note: No list() macro since we use list as the actual function name

#endif // LIST_H