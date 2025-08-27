#include "../include/list.h"

// Create List<int> and List<char*>
DEFINE_LIST(int, IntList);
DEFINE_LIST(char*, StrList);

int main() {
    IntList nums;
    IntList_init(&nums);
    IntList_push_back(&nums, 10);
    IntList_push_back(&nums, 20);
    printf("%d\n", IntList_pop_front(&nums)); // prints 10

    StrList words;
    StrList_init(&words);
    StrList_push_back(&words, "hello");
    StrList_push_back(&words, "world");
    printf("%s\n", StrList_pop_front(&words)); // prints "hello"
}
