#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

ListNode* create_node(const void *data, size_t element_size, list_copy_func copy_func) {
    ListNode *node = malloc(sizeof(ListNode));  
    if (!node) return NULL;
    
    if (copy_func) {
        node->data = copy_func(data);
    } else {
        node->data = malloc(element_size);
        if (!node->data) {
            free(node);
            return NULL;
        }
        memcpy(node->data, data, element_size);
    }
    
    if (!node->data) {
        free(node);
        return NULL;
    }   
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Keep original function name as requested
List* list(size_t element_size, list_destructor destructor, list_copy_func copy_func, list_compare compare_func) {
    if (element_size == 0) return NULL;

    List *new_list = malloc(sizeof(List));
    if (!new_list) return NULL;

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    new_list->element_size = element_size;
    new_list->destructor = destructor;
    new_list->copy_func = copy_func;
    new_list->compare_func = compare_func;
    
    return new_list;
}   

void list_clear(List *list) {
    if (!list) return;    
    ListNode *current = list->head;
    while (current) {
        ListNode *next = current->next;
        if (list->destructor) {
            list->destructor(current->data);
        } else {
            free(current->data);
        }
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0; 
}

void list_destroy(List *list) {
    if (!list) return;  
    list_clear(list);
    free(list);
}

size_t list_size(const List *list) {
    if (!list) return 0;        
    return list->size;
}

bool list_empty(const List *list) {
    if (!list) return true;     
    return list->size == 0;
}   

void* list_front(const List *list) {
    if (!list || list->size == 0) return NULL;
    return list->head->data;
}

void* list_back(const List *list) {
    if (!list || list->size == 0) return NULL;
    return list->tail->data;
}

void* list_at(const List *list, size_t index) {
    if (!list || index >= list->size) return NULL;
    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++) {
        if (current) {
            current = current->next;
        }
    }
    return current ? current->data : NULL;
}

bool list_push_front(List *list, const void *data) {
    if (!list || !data) return false;
    ListNode *new_node = create_node(data, list->element_size, list->copy_func);
    if (!new_node) return false;
    
    if (list->head) {
        new_node->next = list->head;
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    list->head = new_node;
    list->size++;
    return true;
}

bool list_push_back(List *list, const void *data) {
    if (!list || !data) return false;
    ListNode *new_node = create_node(data, list->element_size, list->copy_func);
    if (!new_node) return false;
    
    if (list->tail) {
        new_node->prev = list->tail;
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
    list->size++;
    return true;
}

bool list_pop_front(List *list) {
    if (!list || list->size == 0) return false;
    ListNode *node_to_remove = list->head;
    
    if (list->head->next) {
        list->head = list->head->next;
        list->head->prev = NULL;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }   
    
    if (list->destructor) {
        list->destructor(node_to_remove->data);
    } else {
        free(node_to_remove->data);
    }
    free(node_to_remove);
    list->size--;
    return true;
}

bool list_pop_back(List *list) {
    if (!list || list->size == 0) return false;         
    ListNode *node_to_remove = list->tail;
    
    if (list->tail->prev) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }
    
    if (list->destructor) {
        list->destructor(node_to_remove->data);
    } else {
        free(node_to_remove->data);
    }
    free(node_to_remove);
    list->size--;
    return true;
}

bool list_insert(List *list, size_t index, const void *data) {
    if (!list || !data || index > list->size) return false;
    
    if (index == 0) {
        return list_push_front(list, data);
    }   
    if (index == list->size) {
        return list_push_back(list, data);
    }
    
    ListNode *new_node = create_node(data, list->element_size, list->copy_func);
    if (!new_node) return false;    
    
    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    new_node->next = current;
    new_node->prev = current->prev;
    
    if (current->prev) {
        current->prev->next = new_node;
    }
    current->prev = new_node;
    
    list->size++;
    return true;
}

bool list_erase(List *list, size_t index) {
    if (!list || index >= list->size) return false;
    
    if (index == 0) {
        return list_pop_front(list);
    }
    if (index == list->size - 1) {
        return list_pop_back(list);
    }   
    
    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }
    
    if (list->destructor) {
        list->destructor(current->data);
    } else {
        free(current->data);
    }
    free(current);
    list->size--;
    return true;
}

// Basic implementations for missing functions
bool list_remove(List *list, const void *data) {
    if (!list || !data || !list->compare_func) return false;
    
    ListNode *current = list->head;
    size_t index = 0;
    
    while (current) {
        if (list->compare_func(current->data, data) == 0) {
            return list_erase(list, index);
        }
        current = current->next;
        index++;
    }
    return false;
}

list_iterator list_find(List *list, const void *data) {
    list_iterator it = {NULL, list};
    if (!list || !data || !list->compare_func) return it;
    
    ListNode *current = list->head;
    while (current) {
        if (list->compare_func(current->data, data) == 0) {
            it.current = current;
            break;
        }
        current = current->next;
    }
    return it;
}

bool list_contains(List *list, const void *data) {
    list_iterator it = list_find(list, data);
    return list_iterator_valid(&it);
}

// Iterator functions
list_iterator list_begin(List *list) {
    list_iterator it = {NULL, list};
    if (list) it.current = list->head;
    return it;
}

list_iterator list_end(List *list) {
    list_iterator it = {NULL, list};
    return it;
}

list_iterator list_rbegin(List *list) {
    list_iterator it = {NULL, list};
    if (list) it.current = list->tail;
    return it;
}

list_iterator list_rend(List *list) {
    list_iterator it = {NULL, list};
    return it;
}

bool list_iterator_valid(const list_iterator *it) {
    return it && it->current != NULL;
}

void* list_iterator_data(const list_iterator *it) {
    if (!list_iterator_valid(it)) return NULL;
    return it->current->data;
}

list_iterator list_iterator_next(const list_iterator *it) {
    list_iterator next_it = {NULL, it->list};
    if (list_iterator_valid(it)) {
        next_it.current = it->current->next;
    }
    return next_it;
}

list_iterator list_iterator_prev(const list_iterator *it) {
    list_iterator prev_it = {NULL, it->list};
    if (list_iterator_valid(it)) {
        prev_it.current = it->current->prev;
    }
    return prev_it;
}

void list_print(const List *list, list_printer print_func) {
    if (!list || !print_func) return;
    
    printf("[");
    ListNode *current = list->head;
    while (current) {
        print_func(current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

List* list_copy(const List *node) {
    if (!node) return NULL;
    
    List *new_list = list(node->element_size, node->destructor, 
                         node->copy_func, node->compare_func);
    if (!new_list) return NULL;
    
    ListNode *current = node->head;
    while (current) {
        if (!list_push_back(new_list, current->data)) {
            list_destroy(new_list);
            return NULL;
        }
        current = current->next;
    }
    return new_list;
}

void list_reverse(List *list) {
    if (!list || list->size <= 1) return;
    
    ListNode *current = list->head;
    ListNode *temp = NULL;
    
    // Swap next and prev for all nodes
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    // Swap head and tail
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void list_sort(List *list) {
    if (!list || !list->compare_func || list->size <= 1) return;
    
    // Simple bubble sort for demonstration
    bool swapped;
    do {
        swapped = false;
        ListNode *current = list->head;
        
        while (current && current->next) {
            if (list->compare_func(current->data, current->next->data) > 0) {
                // Swap data pointers
                void *temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}