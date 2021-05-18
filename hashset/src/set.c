// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "set.h"

//-----------Errors---------------------------
static void printError(char *message) {
    //fprintf(stderr, "%s\n", message);
    free(message);
}

static void memError(const char *funcName) {
    char *message = malloc(sizeof(char) * 1024);
    sprintf(message, "Cannot allocate memory in function \"%s\".", funcName);
    printError(message);
    exit(666);
}

static void nullPointerError(const char *funcName, const char *varName) {
    char *message = malloc(sizeof(char) * 1024);
    sprintf(message, "Function \"%s\" get null pointer for \"%s\" parameter.", funcName, varName);
    printError(message);
}

static void invalidArgumentError(const char *funcName, const char *varName) {
    char *message = malloc(sizeof(char) * 1024);
    sprintf(message, "Function \"%s\" get incorrect value for \"%s\" parameter.", funcName, varName);
    printError(message);
}

static void assertError(const char *funcName) {
    char *message = malloc(sizeof(char) * 1024);
    sprintf(message, "Unreachable code was executed in function \"%s\".", funcName);
    printError(message);
}

//----------Definitions----------------------
static const size_t hashTableBuckets = 4096; //32 kB

struct _node {
    size_t hash;
    void *item;
    struct _node *next; //Double linked List
    struct _node *prev;
};

struct _set {
    size_t itemSize;

    size_t (*hash)(const void *);

    bool (*equals)(const void *, const void *);

    size_t size;
    bool modified;
    struct _node **validIt;
    struct _node **hashTable; //Array of pointers
};

typedef struct _set *Set;
typedef const struct _set *constSet;
typedef struct _node *Node;
typedef const struct _node *constNode;
typedef struct _node *Iterator;
static const size_t SET_STOP_ITER = (size_t) NULL;

//-------------------------------------------
//---------static-func-----------------------
static size_t _getBucket(size_t hash) {
    return hash % hashTableBuckets;
}

static Node _createNode(size_t itemSize, size_t hash, const void *item) {
    if (itemSize == 0) {
        invalidArgumentError("_createNode", "itemSize");
        return NULL;
    }
    if (item == NULL) {
        nullPointerError("_createNode", "item");
        return NULL;
    }
    Node pNode = malloc(sizeof(struct _node));
    if (pNode == NULL) {
        memError("_createNode");
        return NULL;
    }
    void *itemCopy = malloc(itemSize);
    if (itemCopy == NULL) {
        memError("_createNode");
        free(pNode);
        return NULL;
    }
    memcpy(itemCopy, item, itemSize);
    pNode->item = itemCopy;
    pNode->hash = hash;
    pNode->next = NULL;
    pNode->prev = NULL;
    return pNode;
}

static Iterator next(constSet pSet, Iterator iter) {
    if (iter->next != NULL) {
        return iter->next;
    }
    for (size_t currentBucket = _getBucket(iter->hash) + 1; currentBucket < hashTableBuckets; ++currentBucket) {
        if (pSet->hashTable[currentBucket] != NULL) {
            return pSet->hashTable[currentBucket];
        }
    }
    return (Iterator) SET_STOP_ITER;
}

static void genItList(Set set) {
    if (set == NULL) {
        nullPointerError("genItList", "set");
        return;
    }
    free(set->validIt);
    set->validIt = malloc(set->size * sizeof(Iterator));
    if (set->validIt == NULL) {
        memError("genItList");
    }
    size_t i = 0;
    for (Iterator it = (Iterator) set_first(set);
         it != (Iterator) set_stop(set); it = next(set, it)) {
        if (i == set->size) {
            assertError("genItList");
        }
        set->validIt[i++] = it;
    }

    set->modified = false;
}

static bool isInvalidIt(constSet set, Iterator it) {
    if (set == NULL) {
        nullPointerError("isInvalidIt", "set");
        return true;
    }
    if (it == NULL) {
        return true;
    }
    if (set->modified) {
        genItList(((Set) (size_t) (const void *) (set))); //Deconst
    }
    for (size_t i = 0; i < set->size; ++i) {
        if (set->validIt[i] == it) {
            return false;
        }
    }
    return true;
}

//----------------func-----------------------
void *set_create(size_t itemSize, size_t (*hash)(const void *), bool (*equals)(const void *, const void *)) {
    if (itemSize == 0) {
        invalidArgumentError("set_init", "itemSize");
        return NULL;
    }
    if (hash == NULL) {
        nullPointerError("set_create", "pointer to hash function");
        return NULL;
    }
    if (equals == NULL) {
        nullPointerError("set_create", "pointer to equality function");
        return NULL;
    }
    Set pSet = malloc(sizeof(struct _set));
    if (pSet == NULL) {
        memError("set_create");
        return NULL;
    }
    pSet = set_init(pSet, itemSize, hash, equals);
    return pSet;
}

void *set_init(void *set, size_t itemSize, size_t (*hash)(const void *), bool (*equals)(const void *, const void *)) {
    Set pSet = set;
    //---------body--------------
    if (itemSize == 0) {
        invalidArgumentError("set_init", "itemSize");
        return NULL;
    }
    if (hash == NULL) {
        nullPointerError("set_init", "pointer to hash function");
        return NULL;
    }
    if (equals == NULL) {
        nullPointerError("set_init", "pointer to equality function");
        return NULL;
    }
    if (pSet == NULL) {
        nullPointerError("set_init", "set");
        return NULL;
    }
    pSet->size = 0;
    pSet->validIt = NULL;
    pSet->modified = false;
    pSet->itemSize = itemSize;
    pSet->hash = hash;
    pSet->equals = equals;
    pSet->hashTable = calloc(hashTableBuckets, sizeof(Node));
    if (pSet->hashTable == NULL) {
        memError("set_init");
        return NULL;
    }
    return pSet;
}

void set_destroy(void *set, void (*destroy)(void *)) {
    Set pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_destroy", "set");
        return;
    }
    set_clear(pSet, destroy);
    free(pSet->hashTable);
    free(pSet);
}

void set_clear(void *set, void (*destroy)(void *)) {
    Set pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_clear", "set");
        return;
    }
    free(pSet->validIt);
    pSet->validIt = NULL; //No more SEH!
    pSet->modified = false;
    if (pSet->size == 0) {
        return;
    }
    Iterator iter = (Iterator) set_first(set);
    if (iter == NULL) {
        return;
    }
    for (size_t i = _getBucket(iter->hash); i < hashTableBuckets; ++i) {
        iter = pSet->hashTable[i];
        pSet->hashTable[i] = NULL;
        while (iter != NULL) {
            if (destroy != NULL) {
                destroy(iter->item);
            }
            free(iter->item);
            Node temp = iter->next;
            free(iter);
            iter = temp;
            pSet->size--;
        }
    }
    if (pSet->size != 0) {
        assertError("set_clear");
    }
}

bool set_contains(const void *set, const void *item) {
    constSet pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_contains", "set");
        return false;
    }
    if (item == NULL) {
        nullPointerError("set_contains", "item");
        return false;
    }
    size_t hash = pSet->hash(item);
    size_t bucket = _getBucket(hash);
    Node currentNode = pSet->hashTable[bucket];
    while (currentNode != NULL) {
        if (currentNode->hash > hash)
            return false;
        if (currentNode->hash == hash)
            if (pSet->equals(currentNode->item, item))
                return true;
        currentNode = currentNode->next;
    }
    return false;
}

bool set_insert(void *set, const void *item) {
    Set pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_insert", "set");
        return false;
    }
    if (item == NULL) {
        nullPointerError("set_insert", "item");
        return false;
    }
    pSet->modified = true;
    size_t hash = pSet->hash(item);
    size_t bucket = _getBucket(hash);
    Node currentNode = pSet->hashTable[bucket];
    while (currentNode != NULL) {
        if (currentNode->hash >= hash) {//Place into prev position
            if (currentNode->hash == hash) {
                if (pSet->equals(currentNode->item, item)) {
                    return false;
                } //if it's diff nodes then push into prev position
            }
            if (currentNode->prev == NULL) { //if it's first item
                pSet->hashTable[bucket] = _createNode(pSet->itemSize, hash, item);
                pSet->hashTable[bucket]->next = currentNode;
                currentNode->prev = pSet->hashTable[bucket];
            } else {
                Node temp = _createNode(pSet->itemSize, hash, item);
                temp->next = currentNode;
                temp->prev = currentNode->prev;
                currentNode->prev = temp;
                temp->prev->next = temp;
            }
            pSet->size++;
            return true;
        }
        if (currentNode->next == NULL) { //End of list
            Node temp = _createNode(pSet->itemSize, hash, item);
            currentNode->next = temp;
            temp->prev = currentNode;
            pSet->size++;
            return true;
        }
        currentNode = currentNode->next;
    }
    pSet->hashTable[bucket] = _createNode(pSet->itemSize, hash, item); //No items in bucket
    pSet->size++;
    return true;
}

void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    Set pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_remove", "set");
        return;
    }
    if (item == NULL) {
        nullPointerError("set_remove", "item");
        return;
    }
    pSet->modified = true;
    size_t hash = pSet->hash(item);
    Node currentNode = pSet->hashTable[_getBucket(hash)];
    while (currentNode != NULL) {
        if (currentNode->hash > hash)
            return;
        if (currentNode->hash == hash)
            if (pSet->equals(currentNode->item, item)) {
                set_erase(pSet, (size_t) currentNode, destroy); //Remove same item!
                return;
            }
        currentNode = currentNode->next;
    }
}

size_t set_first(const void *set) {
    constSet pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_first", "set");
        return SET_STOP_ITER;
    }
    if (pSet->size == 0)
        return SET_STOP_ITER;
    for (size_t i = 0; i < hashTableBuckets; ++i) {
        if (pSet->hashTable[i] != NULL) {
            return (size_t) pSet->hashTable[i];
        }
    }
    assertError("set_first");
    return SET_STOP_ITER;
}

size_t set_last(const void *set) {
    constSet pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_last", "set");
        return SET_STOP_ITER;
    }
    if (pSet->size == 0)
        return SET_STOP_ITER;
    for (long long int i = hashTableBuckets - 1; i >= 0; --i) {
        if (pSet->hashTable[i] != NULL) {
            Iterator temp = pSet->hashTable[i];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            return (size_t) temp;
        }
    }
    assertError("set_last");
    return SET_STOP_ITER;
}

size_t set_next(const void *set, size_t it) {
    constSet pSet = set;
    Iterator iter = (Iterator) it;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_next", "set");
        return SET_STOP_ITER;
    }
    if (it == SET_STOP_ITER) {
        nullPointerError("set_next", "iterator");
        return SET_STOP_ITER;
    }
    if (isInvalidIt(pSet, iter)) {
        invalidArgumentError("set_next", "it");
        return SET_STOP_ITER;
    }
    if (iter->next != NULL) {
        return (size_t) iter->next;
    }
    for (size_t currentBucket = _getBucket(iter->hash) + 1; currentBucket < hashTableBuckets; ++currentBucket) {
        if (pSet->hashTable[currentBucket] != NULL) {
            return (size_t) pSet->hashTable[currentBucket];
        }
    }
    return SET_STOP_ITER;    //Это был последний элемент
}

size_t set_prev(const void *set, size_t it) {
    constSet pSet = set;
    Iterator iter = (Iterator) it;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_prev", "set");
        return SET_STOP_ITER;
    }
    if (isInvalidIt(pSet, iter)) {
        invalidArgumentError("set_prev", "it");
        return SET_STOP_ITER;
    }
    if (iter->prev != NULL) {
        return (size_t) iter->prev;
    }
    for (long long int currentBucket = _getBucket(iter->hash) - 1; currentBucket >= 0; --currentBucket) {
        if (pSet->hashTable[currentBucket] != NULL) {
            Iterator resultIter = pSet->hashTable[currentBucket];
            while (resultIter->prev != NULL) {
                resultIter = resultIter->prev;
            }
            return (size_t) resultIter;
        }
    }
    //Это был первый элемент
    return SET_STOP_ITER;
}

const void *set_current(const void *set, size_t it) {
    constSet pSet = set;
    Iterator iter = (Iterator) it;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_current", "set");
        return NULL;
    }
    if (isInvalidIt(pSet, iter)) {
        invalidArgumentError("set_current", "it");
        return NULL;
    }
    return iter->item;
}

void set_erase(void *set, size_t it, void (*destroy)(void *)) {
    Set pSet = set;
    Iterator iter = (Iterator) it;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_erase", "set");
        return;
    }
    if (isInvalidIt(pSet, iter)) {
        invalidArgumentError("set_erase", "it");
        return;
    }
    if (iter->prev == NULL) {
        pSet->hashTable[_getBucket(iter->hash)] = iter->next;
    } else {
        iter->prev->next = iter->next;
    }
    if (iter->next != NULL) {
        iter->next->prev = iter->prev;
    }
    if (destroy != NULL) {
        destroy(iter->item);
    }
    free(iter->item);
    free(iter);
    pSet->size--;
    pSet->modified = true;
}

size_t set_stop(const void *set) {
    return SET_STOP_ITER;
}

size_t set_count(const void *set) {
    constSet pSet = set;
    //---------body--------------
    if (pSet == NULL) {
        nullPointerError("set_count", "set");
        return (size_t) -1;
    }
    return pSet->size;
}




