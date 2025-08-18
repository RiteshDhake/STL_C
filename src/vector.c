#include "vector.h"




Vector* vector_create(){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if(!vector){
        return NULL;
    }
    vector->size =0;
    vector->capacity = 16; //inital size be 16;
    vector->data = (void**)malloc(sizeof(void*) * vector->capacity); // creating an array of void*
    
    
    if(!vector->data){
        free(vector);//free allocation
        return NULL;
    }

    return vector;

}
void vector_push(Vector* v,void* item){
        //check size and capacity
        if(v->size >= v->capacity){
            size_t new_capacity = v->capacity*2;
            void ** new_data =realloc(v->data,sizeof(void*)*new_capacity);
            if(!new_data){
                return;
            }
            v->data = new_data;
            v->capacity = new_capacity;
        }
        v->data[v->size] = item;
        v->size++;
}

void* vector_get(Vector* v ,size_t index){
    if(index >= v->size){
        return NULL;
    }
    return v->data[index];
}
void vector_set(Vector* v,size_t index,void* item){
    if(index >= v->size){
        return;
    }
    v->data[index] = item;
}

void vector_insert(Vector* v,size_t index,void* item){
    if(v->size >= v->capacity){
        size_t new_capacity = v->capacity*2;
        void **new_data =realloc(v->data,sizeof(void*)*new_capacity);
        if(!new_data){
            return;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    if(index > v->size){
        return;
    }
    for(size_t i = v->size ; i>index ; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[index] = item;
    v->size++;
}


void vector_remove(Vector* v,size_t index){
    
    if (index >= v->size) {
        return; // invalid index
    }

    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->data[v->size - 1] = NULL;
    v->size--;
    
}

void vector_free(Vector* v, void (*free_func)(void*)){
    if (!v) return;
    
    if (free_func) {
        for (size_t i = 0; i < v->size; i++) {
            if (v->data[i]) {
                free_func(v->data[i]); // free each element
            }
        }
    }

    free(v->data);
    free(v);
}
