// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/set.h"

typedef struct {
    char *name;
    unsigned int num;
} person;

static size_t hash(const void *item) {
    const person *a = (const person *) item;
    return strlen(a->name) % a->num;
}

static bool eq(const void *item1, const void *item2) {
    const person *a = (const person *) item1;
    const person *b = (const person *) item2;
    if (a->num != b->num) {
        return false;
    }
    for (size_t i = 0;; i++) {
        if (a->name[i] != b->name[i]) {
            return false;
        }
        if (a->name[i] == '\0') {
            return true;
        }
    }
}

static person *createPerson(const char *name, unsigned int num) {
    person *per = malloc(sizeof(person));
    char *_name = malloc(sizeof(char) * 20);
    strncpy(_name, name, 19);
    per->name = _name;
    per->num = num;
    return per;
}

static void destroyPerson(void *item) {
    person *a = (person *) item;
    free(a->name);
}

static bool onePersonFirstPrevCurrentTest(void *set) {
    set_clear(set, 0);
    person *per = createPerson("Mark", 10);
    set_insert(set, per);
    free(per);
    size_t f = set_first(set);
    size_t i = set_prev(set, f);
    const void *p = set_current(set, i);
    set_erase(set, f, &destroyPerson);
    return (p == NULL);
}

static bool onePersonLastPrevStopTest(void *set) {
    set_clear(set, 0);
    person *per = createPerson("Mark", 10);
    set_insert(set, per);
    free(per);
    size_t l = set_last(set);
    size_t i = set_prev(set, l);
    set_prev(set,i);
    if (i != set_stop(set)) return false;
    const void *p = set_current(set, i);
    set_erase(set, l, &destroyPerson);
    set_clear(set, 0);
    return (p == NULL);
}
static bool onePersonLastNextStopTest(void *set) {
    set_clear(set, 0);
    person *per = createPerson("Mark", 10);
    set_insert(set, per);
    free(per);
    size_t l = set_last(set);
    size_t i = set_next(set, l);
    set_next(set,i);
    if (i != set_stop(set)) return false;
    const void *p = set_current(set, i);
    set_erase(set, l, &destroyPerson);
    set_clear(set, 0);
    return (p == NULL);
}
static bool onePersonRemove(void * set){
    set_clear(set, 0);

    for (int i = 0; i < 100; ++i) {
        person *per = createPerson("Mark", 10);
        set_insert(set, per);
        set_remove(set,per,&destroyPerson);
        free(per);
    }

    return true;
}
bool test() {
    void *set = set_create(sizeof(person), hash, eq);
    if (!onePersonFirstPrevCurrentTest(set)) return false;
    if (!onePersonLastPrevStopTest(set)) return false;
    if (!onePersonLastNextStopTest(set)) return false;
    if (!onePersonRemove(set)) return false;
    set_destroy(set, &destroyPerson);
    return true;
};