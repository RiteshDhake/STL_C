# Queue Module Documentation

The `queue.h` file provides a generic macro-based implementation of a
queue in C, built on top of the dynamic array (`vector`) implementation.

------------------------------------------------------------------------

## Features

-   Generic queue for any data type.
-   Supports enqueue, dequeue, front, rear, size, empty, and free
    operations.
-   Built using `vector.h`.

------------------------------------------------------------------------

## Usage

### Define a Queue for a Type

``` c
DEFINE_QUEUE(int);     // Defines queue_int
DEFINE_QUEUE(float);   // Defines queue_float
```

### Example

``` c
#include "queue.h"

int main() {
    queue_int q;
    queue_int_init(&q);

    queue_int_enqueue(&q, 10);
    queue_int_enqueue(&q, 20);
    queue_int_enqueue(&q, 30);

    printf("Front: %d\n", queue_int_front(&q));
    printf("Rear: %d\n", queue_int_rear(&q));

    int val = queue_int_dequeue(&q);
    printf("Dequeued: %d\n", val);

    queue_int_free(&q);
    return 0;
}
```

### Functions

-   `void queue_##T##_init(queue_##T *q)`
    -   Initialize a queue.
-   `void queue_##T##_enqueue(queue_##T *q, T item)`
    -   Add element at the rear.
-   `T queue_##T##_dequeue(queue_##T *q)`
    -   Remove element from the front.
-   `T queue_##T##_front(queue_##T *q)`
    -   Get front element.
-   `T queue_##T##_rear(queue_##T *q)`
    -   Get rear element.
-   `size_t queue_##T##_size(queue_##T *q)`
    -   Get number of elements.
-   `int queue_##T##_empty(queue_##T *q)`
    -   Check if queue is empty.
-   `void queue_##T##_free(queue_##T *q)`
    -   Free memory.

------------------------------------------------------------------------
