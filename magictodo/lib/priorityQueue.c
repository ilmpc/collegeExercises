#include "priorityQueue.h"

static const short STD_SIZE = 1024;

static size_t parent(size_t i) {
    if (i == 0) {
        return 0;
    }
    return (i - 1) / 2;
}

static size_t leftChild(size_t i) {
    return 2 * i + 1;
}

static size_t rightChild(size_t i) {
    return 2 * i + 2;
}

static void siftUp(PriorityQueue *pq, size_t i) {
    while (i > 0 && pq->arr[parent(i)].priority < pq->arr[i].priority) {
        node temp = pq->arr[parent(i)]; //SWAP
        pq->arr[parent(i)] = pq->arr[i];
        pq->arr[i] = temp;
        i = parent(i);
    }
}

static void siftDown(PriorityQueue *pq, size_t i) {
    size_t maxIndex = i;
    size_t left = leftChild(i);
    if (left < pq->length && pq->arr[left].priority > pq->arr[maxIndex].priority) {
        maxIndex = left;
    }
    size_t right = rightChild(i);
    if (right < pq->length && pq->arr[right].priority > pq->arr[maxIndex].priority) {
        maxIndex = right;
    }
    if (i != maxIndex) {
        node temp = pq->arr[maxIndex]; //SWAP
        pq->arr[maxIndex] = pq->arr[i];
        pq->arr[i] = temp;
        siftDown(pq, maxIndex);
    }
}

PriorityQueue *createPQ(size_t elementSize) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->elementSize = elementSize;
    pq->size = STD_SIZE;
    pq->length = 0;
    pq->data = malloc(STD_SIZE * elementSize);
    if(pq->data == NULL){
        return NULL;
    }
    pq->arr = malloc(STD_SIZE * sizeof(node));
    if(pq->arr == NULL){
        return NULL;
    }
    return pq;
}

void destroyPQ(PriorityQueue *pq) {
    free(pq->data);
    free(pq->arr);
    free(pq);
}

int insertPQ(PriorityQueue *pq, int priority, Pointer value) {
    if(pq == NULL){
        return 0;
    }
    if (pq->length == pq->size) {
        pq->size *= 2;
        void *temp = realloc(pq->data, pq->size * pq->elementSize);
        if (temp == NULL){
            return 0;
        }
        pq->data = temp;
        temp = realloc(pq->arr, pq->size * sizeof(node));
        if(temp == NULL){
            return 0;
        }
        pq->arr = temp;
    }
    memcpy(pq->data + (++pq->length) * pq->elementSize, value, pq->elementSize);
    pq->arr[pq->length - 1] = (node) {.data = pq->data + (pq->length) * pq->elementSize, .priority=priority};
    siftUp(pq, pq->length - 1);
    return 1;
}

Pointer extractMaxPQ(PriorityQueue *pq) {
    if (pq->length == 0) {
        return NULL;
    }
    Pointer result = malloc(pq->elementSize);
    memcpy(result, pq->arr[0].data, pq->elementSize); //copy root
    pq->arr[0] = pq->arr[--pq->length];
    siftDown(pq, 0);
    return result;
}

size_t getLengthPQ(PriorityQueue *pq) {
    return pq->length;
}

