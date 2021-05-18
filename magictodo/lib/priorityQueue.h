#ifndef PRIORITYQUEUE_PRIORITYQUEUE_H
#define PRIORITYQUEUE_PRIORITYQUEUE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


typedef void *Pointer;

typedef struct {
    int priority;
    Pointer data;
} node;
typedef struct {
    Pointer data;
    size_t elementSize;
    size_t length;
    size_t size;
    node *arr;
} PriorityQueue;

/* Create empty priority queue. */
PriorityQueue *createPQ(size_t elementSize);

/* Destroy priority queue and free its memory. */
void destroyPQ(PriorityQueue *pq);

/* Add new value into the priority queue. */
int insertPQ(PriorityQueue *pq, int priority, Pointer value);

/* Delete maximum value from the priority queue and return it. */
Pointer extractMaxPQ(PriorityQueue *pq);

size_t getLengthPQ(PriorityQueue *pq);

#endif //PRIORITYQUEUE_PRIORITYQUEUE_H
