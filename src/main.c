#include "stl.h"

// Function declarations
void demo_req1();
void demo_req2();
void demo_hashmap();
void demo_list();
void demo_set();

int main() {
    printf("STL-for-C Demonstration\n");
    printf("======================\n\n");
    
    int app = 1;
    while(app){
        int choice;
        printf("1:Vector,Stack,Queue Demo\n");
        printf("2: List Demo\n");
        printf("3:Sets Demo\n");
        printf("4:HashmapsDemo\n");
        printf("0: Exit\n");
        printf("======================\n\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        if(choice ==1){
            demo_req1();
            demo_req2();
        }
        else if(choice ==2){demo_list();}
        else if(choice ==3){demo_set();}
        else if(choice ==4){demo_hashmap();}
        else if(choice ==0){
            app =0;
            break;
        }
    }

    printf("=== Demonstration Complete ===\n");
    
    return 0;
}