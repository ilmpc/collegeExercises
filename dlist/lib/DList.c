#include "DList.h"

static short STD_SIZE = 1024;

DList *createDList(size_t elementSize) {
    assert(elementSize > 0);
    DList *dl = malloc(sizeof(DList));
    dl->head = NULL;
    dl->tail = NULL;
    dl->length = 0;
    dl->elementSize = elementSize;
    return dl;
}

void destroyDList(DList *dl) {
    if (dl == NULL) {
        return;
    }
    node *temp = dl->head;
    if (temp != NULL) {
        do {
            free(temp->data);
            temp = temp->prev;
        } while (temp != NULL);
    }
    free(dl);
}

int pushHead(DList *dl, Pointer item) {
    assert(dl != NULL && item != NULL);

    node *nd = malloc(sizeof(node));
    nd->prev = dl->head;
    nd->next = NULL;
    if (dl->head != NULL) {
        dl->head->next = nd;
    }
    dl->head = nd;

    //link data
    nd->data = malloc(dl->elementSize);
    if (nd->data == NULL) {
        return 1; //mem_error
    }
    //copy data
    memcpy(nd->data, item, dl->elementSize);
    dl->length++;
    //check tail
    if (dl->tail == NULL) {
        dl->tail = dl->head;
    }
    return 0;

}

int pushTail(DList *dl, Pointer item) {
    assert(dl != NULL && item != NULL);

    node *nd = malloc(sizeof(node));
    nd->next = dl->tail;
    nd->prev = NULL;
    if (dl->tail != NULL) {
        dl->tail->prev = nd;
    }
    dl->tail = nd;
    //link data
    nd->data = malloc(dl->elementSize);
    if (nd->data == NULL) {
        return 1; //mem_error
    }
    //copy data
    memcpy(nd->data, item, dl->elementSize);
    dl->length++;
    //check head
    if (dl->head == NULL) {
        dl->head = dl->tail;
    }
    return 0;
}

Pointer popHead(DList *dl) {
    assert(dl != NULL);
    if (dl->head == NULL || dl->length == 0) {
        return NULL;
    }

    Pointer item = dl->head->data;
    node *newHead = dl->head->prev;
    if (newHead == NULL) {
        dl->tail = NULL;
    } else {
        newHead->next = NULL;
    }
    free(dl->head);
    dl->head = newHead;
    dl->length--;
    return item;
}

Pointer popTail(DList *dl) {
    assert(dl != NULL);
    if (dl->tail == NULL || dl->length == 0) {
        return NULL;
    }

    Pointer item = dl->tail->data;
    node *newTail = dl->tail->next;
    if (newTail == NULL) {
        dl->head = NULL;
    } else {
        newTail->prev = NULL;
    }
    free(dl->tail);
    dl->tail = newTail;
    dl->length--;
    return item;
}

Pointer const at(DList *dl, size_t index) {
    assert(dl != NULL);
    if (index < 0 || index >= dl->length) {
        return NULL;
    }

    node *item = dl->head;
    size_t i = index;
    while (i > 0 && item->prev != NULL) {
        item = item->prev;
        i--;
    }
    if (item != NULL) {
        return item->data;
    } else {
        return NULL;
    }
}

size_t getLength(DList *dl) {
    assert(dl != NULL);
    return dl->length;
}


