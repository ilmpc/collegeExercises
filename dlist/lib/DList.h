#ifndef DLIST_DLIST_H
#define DLIST_DLIST_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void *Pointer;
typedef struct _node {
    struct _node *next;
    struct _node *prev;
    Pointer data;
} node;

typedef struct {
    node *head;
    node *tail;
    size_t elementSize;
    size_t length;
} DList;

DList *createDList(size_t elementSize);

void destroyDList(DList *dl);

int pushHead(DList *dl, Pointer item);

int pushTail(DList *dl, Pointer item);

Pointer popHead(DList *dl);

Pointer popTail(DList *dl);

Pointer const at(DList *dl, size_t index);

size_t getLength(DList *dl);

#endif //DLIST_DLIST_H
