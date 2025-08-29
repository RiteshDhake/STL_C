#include "stl.h"

typedef struct {
    int roll_no;
    char* name;
}Student;

// Define types - clean and simple
DEFINE_VEC(Student)
DEFINE_VEC(float)
DEFINE_VEC(vec_float)
DEFINE_VEC(int)  
DEFINE_STACK(int)

void req1_vector_operations() {
    printf("=== REQ1: Vector of Vectors (float) Operations ===\n");
    
    // Create a vector of vectors (2D array-like structure)
    vec_vec_float matrix;
    vec_vec_float_init(&matrix);
    
    // Create and populate first row
    vec_float row1;
    vec_float_init(&row1);
    vec_float_push(&row1, 1.1f);
    vec_float_push(&row1, 2.2f);
    vec_float_push(&row1, 3.3f);
    
    // Create and populate second row  
    vec_float row2;
    vec_float_init(&row2);
    vec_float_push(&row2, 4.4f);
    vec_float_push(&row2, 5.5f);
    vec_float_push(&row2, 6.6f);
    
    // Create and populate third row
    vec_float row3;
    vec_float_init(&row3);
    vec_float_push(&row3, 7.7f);
    vec_float_push(&row3, 8.8f);
    vec_float_push(&row3, 9.9f);
    
    // Add rows to matrix
    vec_vec_float_push(&matrix, row1);
    vec_vec_float_push(&matrix, row2);
    vec_vec_float_push(&matrix, row3);
    
    printf("Created 3x3 matrix:\n");
    for (size_t i = 0; i < matrix.len; i++) {
        vec_float current_row = vec_vec_float_get(&matrix, i);
        printf("Row %zu: ", i);
        for (size_t j = 0; j < current_row.len; j++) {
            printf("%.1f ", vec_float_get(&current_row, j));
        }
        printf("\n");
    }
    
    // Add a new row
    vec_float row4;
    vec_float_init(&row4);
    vec_float_push(&row4, 10.1f);
    vec_float_push(&row4, 11.2f);
    vec_float_push(&row4, 12.3f);
    vec_vec_float_push(&matrix, row4);
    
    printf("\nAfter adding fourth row:\n");
    for (size_t i = 0; i < matrix.len; i++) {
        vec_float current_row = vec_vec_float_get(&matrix, i);
        printf("Row %zu: ", i);
        for (size_t j = 0; j < current_row.len; j++) {
            printf("%.1f ", vec_float_get(&current_row, j));
        }
        printf("\n");
    }
    
    // Calculate sum of all elements
    float total_sum = 0.0f;
    for (size_t i = 0; i < matrix.len; i++) {
        vec_float current_row = vec_vec_float_get(&matrix, i);
        for (size_t j = 0; j < current_row.len; j++) {
            total_sum += vec_float_get(&current_row, j);
        }
    }
    printf("Sum of all elements: %.1f\n", total_sum);
    
    // Free all memory
    for (size_t i = 0; i < matrix.len; i++) {
        vec_float current_row = vec_vec_float_get(&matrix, i);
        vec_float_free(&current_row);
    }
    vec_vec_float_free(&matrix);
    printf("\n");
}

void req1_stack_operations() {
    printf("=== REQ1: Stack Operations ===\n");
    
    stack_int s;
    stack_int_init(&s);
    
    // Push elements onto stack
    printf("Pushing elements: 1, 2, 3, 4, 5\n");
    stack_int_push(&s, 1);
    stack_int_push(&s, 2);
    stack_int_push(&s, 3);
    stack_int_push(&s, 4);
    stack_int_push(&s, 5);
    
    printf("Stack size: %zu\n", stack_int_size(&s));
    printf("Top element: %d\n", stack_int_top(&s));
    
    // Pop elements
    printf("Popping elements: ");
    while (!stack_int_empty(&s)) {
        printf("%d ", stack_int_pop(&s));
    }
    printf("\n");
    
    printf("Stack size after popping all: %zu\n", stack_int_size(&s));
    
    // Push some more elements for demonstration
    printf("Pushing 100, 200, 300\n");
    stack_int_push(&s, 100);
    stack_int_push(&s, 200);
    stack_int_push(&s, 300);
    
    printf("Peek at top: %d\n", stack_int_peek(&s));
    printf("Stack size: %zu\n", stack_int_size(&s));
    
    stack_int_free(&s);
    printf("\n");
}

void req1_vec_struct_operations(){
    printf("=====Demonstrating Vector of Struct=======\n");
    vec_Student students;
    Student*S = (Student*)malloc(sizeof(Student));
    vec_Student_init(&students);

    printf("Enter Names of the Students in Struct\n");
    for(int i =0 ; i < 5 ; i++){
        char name[100]; 
        scanf("%s",name);
        
        S->name = strdup(name);
        S->roll_no = i;

        vec_Student_push(&students,*S);
    }

    printf("Vector of students ");
    printf("\n[");
    for(int i = 0 ; i<5;i++){
        printf("( Name:");
        printf("%s",vec_Student_get(&students,i).name);
        printf(",Age:");
        printf("%d",vec_Student_get(&students,i).roll_no);
        printf(")");
    }
    printf("]\n");

    free(S);
    vec_Student_free(&students);
}