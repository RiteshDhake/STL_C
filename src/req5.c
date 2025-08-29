#include "../include/set.h"
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double score;
} Student;

// Define comparison function (returns <0, 0, >0 like strcmp)
int student_compare(Student a, Student b) {
    if (a.id != b.id) return a.id - b.id;
    int name_cmp = strcmp(a.name, b.name);
    if (name_cmp != 0) return name_cmp;
    if (a.score < b.score) return -1;
    if (a.score > b.score) return 1;
    return 0;
}

bool student_equal(Student a, Student b) {
    return a.id == b.id && 
           strcmp(a.name, b.name) == 0 && 
           a.score == b.score;
}

void student_print(Student s) {
    printf("{id:%d, name:%s, score:%.1f}", s.id, s.name, s.score);
}
// type, type name , format specifier 
DEFINE_SET(int, int, "%d")
DEFINE_SET(char*, string, "%s")
// type, type name , format specifier , comparison func, equality func, print func for custom structs 
DEFINE_SET_CUSTOM(Student, Student, student_compare, student_equal, student_print)

void demo_set() {
    // Integer set
    Set_int int_set;
    set_init_int(&int_set);
    set_add_int(&int_set, 10);
    set_add_int(&int_set, 5);
    set_add_int(&int_set, 15);
    printf("Integer set: ");
    set_display_int(&int_set);

    Set_int int_set_1;
    set_init_int(&int_set_1);
    set_add_int(&int_set_1, 12);
    set_add_int(&int_set_1, 10);
    set_add_int(&int_set_1, 20);
    printf("Integer set: ");
    set_display_int(&int_set_1);
    
    // String set
    Set_string char_set;
    set_init_string(&char_set);
    set_add_string(&char_set, "apple");
    set_add_string(&char_set, "banana");
    set_add_string(&char_set, "apple"); // Duplicate
    printf("String set: ");
    set_display_string(&char_set);
    
    // Student set
    Set_Student student_set;
    set_init_Student(&student_set);
    
    Student s1 = {101, "Alice", 85.5};
    Student s2 = {102, "Bob", 92.0};
    Student s3 = {100, "Charlie", 78.5};
    Student s4 = {101, "Alice", 85.5}; // Duplicate
    
    set_add_Student(&student_set, s1);
    set_add_Student(&student_set, s2);
    set_add_Student(&student_set, s3);
    set_add_Student(&student_set, s4); // Won't be added (duplicate)
    
    printf("Student set: ");
    set_display_Student(&student_set);
    
    printf("Set size: %zu\n", student_set.size);
    
    Student search = {102, "Bob", 92.0};
    printf("Contains Bob? %s\n", 
           set_contains_Student(&student_set, search) ? "Yes" : "No");
    
    // Test set operations on integer sets
    Set_int set1, set2;
    set_init_int(&set1);
    set_init_int(&set2);
    
    set_add_int(&set1, 1);
    set_add_int(&set1, 2);
    set_add_int(&set1, 3);
    
    set_add_int(&set2, 3);
    set_add_int(&set2, 4);
    set_add_int(&set2, 5);
    
    printf("Set 1: ");
    set_display_int(&set1);
    printf("Set 2: ");
    set_display_int(&set2);
    
    Set_int union_set = set_union_int(&set1, &set2);
    printf("Union: ");
    set_display_int(&union_set);
    
    Set_int intersection_set = set_intersection_int(&set1, &set2);
    printf("Intersection: ");
    set_display_int(&intersection_set);
    
    Set_int difference_set = set_difference_int(&set1, &set2);
    printf("Difference (Set1 - Set2): ");
    set_display_int(&difference_set);
    
    
}