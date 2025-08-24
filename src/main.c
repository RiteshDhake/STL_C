#include "stl.h"

// Function declarations
void req1_vector_operations();
void req1_stack_operations();
void req2_vector_operations();
void req2_stack_operations();

int main() {
    printf("STL-for-C Demonstration\n");
    printf("======================\n\n");
    
    // Call functions from req1.c
    req1_vector_operations();
    req1_stack_operations();
    
    // Call functions from req2.c  
    req2_vector_operations();
    req2_stack_operations();
    
    printf("=== Demonstration Complete ===\n");
    
    return 0;
}