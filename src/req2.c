#include "stl.h"

typedef char* string;

DEFINE_VEC(string);
// Define types - clean and simple
DEFINE_VEC(int)
DEFINE_STACK(int)
DEFINE_QUEUE(int)


void req2_vector_operations() {
    printf("=== REQ2: Vector Operations (int) ===\n");
    
    vec_int v;
    vec_int_init(&v);
    
    // Push some integers
    printf("Pushing elements: 15, 27, 314, 40, 599\n");
    vec_int_push(&v, 15);
    vec_int_push(&v, 27);
    vec_int_push(&v, 314);
    vec_int_push(&v, 40);
    vec_int_push(&v, 599);
    
    // Display vector contents
    printf("Vector contents: ");
    for (size_t i = 0; i < v.len; i++) {
        printf("%d ", vec_int_get(&v, i));
    }
    printf("\n");
    
    // Mathematical operations on vector elements
    printf("Doubling all elements...\n");
    for (size_t i = 0; i < v.len; i++) {
        int val = vec_int_get(&v, i);
        vec_int_set(&v, i, val * 2);
    }
    
    printf("Vector after doubling: ");
    for (size_t i = 0; i < v.len; i++) {
        printf("%d ", vec_int_get(&v, i));
    }
    printf("\n");
    
    // Find sum of all elements
    int sum = 0;
    for (size_t i = 0; i < v.len; i++) {
        sum += vec_int_get(&v, i);
    }
    printf("Sum of all elements: %d\n", sum);
    
    vec_int_free(&v);
    printf("\n");
}

void req2_stack_operations() {
    printf("=== REQ2: Stack Operations (int) ===\n");
    
    stack_int s;
    stack_int_init(&s);
    
    // Simulate a calculator stack with integers
    printf("Integer calculator simulation using stack:\n");
    
    // Push operands
    printf("Pushing operands: 105, 32\n");
    stack_int_push(&s, 105);
    stack_int_push(&s, 32);
    
    // Perform addition
    if (stack_int_size(&s) >= 2) {
        int b = stack_int_pop(&s);
        int a = stack_int_pop(&s);
        int result = a + b;
        printf("%d + %d = %d\n", a, b, result);
        stack_int_push(&s, result);
    }
    
    printf("Result on stack: %d\n", stack_int_top(&s));
    
    // Push more operands for multiplication
    printf("Pushing 2 for multiplication\n");
    stack_int_push(&s, 2);
    
    if (stack_int_size(&s) >= 2) {
        int b = stack_int_pop(&s);
        int a = stack_int_pop(&s);
        int result = a * b;
        printf("%d * %d = %d\n", a, b, result);
        stack_int_push(&s, result);
    }
    
    printf("Final result: %d\n", stack_int_top(&s));
    
    // Demonstrate stack reversal
    printf("\nDemonstrating stack reversal:\n");
    stack_int temp;
    stack_int_init(&temp);
    
    // Clear current stack and add test data
    while (!stack_int_empty(&s)) {
        stack_int_pop(&s);
    }
    
    printf("Original order: 11, 22, 33, 44\n");
    stack_int_push(&s, 11);
    stack_int_push(&s, 22);
    stack_int_push(&s, 33);
    stack_int_push(&s, 44);
    
    // Move to temporary stack (reverses order)
    printf("After one reversal: ");
    while (!stack_int_empty(&s)) {
        int val = stack_int_pop(&s);
        printf("%d ", val);
        stack_int_push(&temp, val);
    }
    printf("\n");
    
    stack_int_free(&s);
    stack_int_free(&temp);
    printf("\n");
}

void req2_string_vec_ops(){
    printf("=====Demonstrating Vector of String=======");
    vec_string names;
    vec_string_init;
    printf("\nPushing Names in Vec of String");
    vec_string_push(&names,"Ritesh");
    vec_string_push(&names,"Aditya");
    vec_string_push(&names,"Arnav");
    vec_string_push(&names,"Parth");
    

    printf("\n[");
    for(int i = 0; i<4;i++){
        printf(" %s",vec_string_get(&names,i));
        if(i < 3){
            printf(",");
        }
        
    }
    printf("]\n");
    
}

void req2_queue_int_ops(){
    queue_int q;
    queue_int_init(&q);
    printf("\nEnqueuing 0-9 numbers in queue of integers");
    for(int i = 0 ; i<10 ; i++){
        queue_int_enqueue(&q,i);
    }
    printf("\nQueue front is: %d",queue_int_front(&q));
    printf("\nQueue rear is: %d",queue_int_rear(&q));
    
}