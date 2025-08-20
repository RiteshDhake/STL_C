#include "common.h"

// vector structure containg a array of void* so that we can use any generic data rather than 
//using type specfic macros 
//also there is size and capacity for the vector.it usese size_t , which automatically adpats to 32bit or 64 bit systems


typedef struct {
    void **data;
    size_t size;
    size_t capacity;
}Vector;

// Protypes of Methods

Vector* vector_create();
void vector_push_back(Vector*,void*);
void* vector_get(Vector*,size_t);
void vector_set(Vector*,size_t,void*);
void vector_insert(Vector*,size_t,void*);
void vector_remove(Vector*,size_t);
void vector_free(Vector*,void (*free_func)(void*));

