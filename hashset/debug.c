// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/set.h"
#include "debug2.h"
size_t hash(const void *item) {
    return (size_t) ((*(int *) item) * (*(int *) item)) % 1024;
}

bool eq(const void *item1, const void *item2) {
    if (*((int *) item1) == *((int *) item2)) {
        return true;
    }
    return false;
}

bool simpleTest() {
    void *set1 = set_create(sizeof(int), hash, eq);
    int a = 12, b = 123, c = 1025;
    if (set_insert(set1, &a) != 1) {
        return false;
    }
    if (set_insert(set1, &b) != 1) {
        return false;
    } //1
    if (set_insert(set1, &c) != 1) {
        return false;
    }
    if (set_insert(set1, &b) != 0) {
        return false;
    } //0
    if (set_contains(set1, &a) != 1) {
        return false;
    } //1
    if (set_count(set1) != 3) {
        return false;
    } //3
    set_remove(set1, &a, NULL); //size-1
    if (set_count(set1) != 2) {
        return false;
    } //2
    if (*((int *) set_current(set1, set_first(set1))) != 1025) {
        return false;
    } //item c = 1025
    set_clear(set1, NULL); //size = 0
    if (set_count(set1) != 0) {
        return false;
    } // 0
    set_destroy(set1, NULL);
    return true;
}

bool nullTest() {
    void *set1 = set_create(1, NULL, NULL);
    if (set1 != NULL) {
        return false;
    }
    return true;
}

size_t shash(const void *item) {
    return strlen((char *) item);
}

bool seq(const void *item1, const void *item2) {
    return strcmp((const char *) item1, (const char *) item2) == 0 ? true : false;
}

bool oneStringLastCurrentTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    size_t last = set_last(set);
    return seq(set_current(set, last), "qwerty");
}

bool oneStringFirstPrevCurrentTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    size_t f = set_first(set);
    size_t i = set_prev(set, f);
    const void *p = set_current(set, i);
    return (p == NULL);
}

bool oneStringFirstLastTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    size_t last = set_last(set);
    size_t first = set_first(set);
    return seq(set_current(set, last), set_current(set, first));
}

bool oneStringFirstNextStopTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    size_t first = set_first(set);
    first = set_next(set, first);
    return first == set_stop(set);
}

bool oneStringLastPrevStopTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    size_t p = set_last(set);
    p = set_prev(set, p);
    return (p == set_stop(set));
}
bool oneStringRemoveTest(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_remove(set,"qwerty",NULL);
    return (set_count(set) == 0);
}

bool twoStringNextPrev(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_insert(set, "qwerg");
    size_t iter = set_first(set);
    size_t first = iter;
    iter = set_next(set, iter);
    iter = set_prev(set, iter);
    return iter == set_first(set);
}

bool twoStringInvalid(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_insert(set, "qwerg");
    size_t iter = set_first(set);
    iter = 0x787855;
    iter = set_next(set, iter);
    bool result = true;
    if (iter != set_stop(set)) {
        result = false;
    }
    iter = set_prev(set, iter);
    if (iter != set_stop(set)) {
        result = false;
    }
    return result;
}

bool threeStringLoop(void *set) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_insert(set, "qwerg");
    set_insert(set, "qq");
    size_t iter = set_last(set);
    iter = set_prev(set, iter);
    iter = set_prev(set, iter);
    if (iter != set_first(set))
        return false;
    iter = set_prev(set, iter);
    return iter == set_stop(set);
}

bool threeStringInvalid(void *set,size_t num) {
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_insert(set, "qwerg");
    set_insert(set, "qq");
    size_t iter = num;
    if (set_current(set, iter) != NULL) return false;
    if (set_prev(set, iter) != set_stop(set)) return false;
    if (set_next(set, iter) != set_stop(set)) return false;
    set_erase(set, iter, NULL);
    return true;
}
bool threeStringErase(void *set){
    set_clear(set, 0);
    set_insert(set, "qwerty");
    set_insert(set, "qwerg");
    set_insert(set, "qq");
    size_t iter = set_first(set);
    set_erase(set,iter,NULL);
    if(set_count(set) != 2) return false;
    set_erase(set,set_last(set),NULL);
    if(set_count(set) != 1) return false;
    return seq(set_current(set,set_first(set)),"qwerg");
}

int main() {
    void *set = set_create(10 * sizeof(char), shash, seq);
    printf("%s\n", simpleTest() == 1 ? "pass" : "fail");
    printf("%s\n", nullTest() == 1 ? "pass" : "fail");
    printf("%s\n", oneStringLastCurrentTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", oneStringFirstLastTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", oneStringFirstNextStopTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", oneStringRemoveTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", twoStringNextPrev(set) == 1 ? "pass" : "fail");
    printf("%s\n", oneStringLastPrevStopTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", twoStringInvalid(set) == 1 ? "pass" : "fail");
    printf("%s\n", threeStringLoop(set) == 1 ? "pass" : "fail");
    printf("%s\n", oneStringFirstPrevCurrentTest(set) == 1 ? "pass" : "fail");
    printf("%s\n", threeStringInvalid(set,0) == 1 ? "pass" : "fail");
    printf("%s\n", threeStringInvalid(set,(size_t)-1) == 1 ? "pass" : "fail");
    printf("%s\n", threeStringErase(set) == 1 ? "pass" : "fail");
    printf("%s\n", test() == 1 ? "pass" : "fail");
    set_destroy(set, 0);
}