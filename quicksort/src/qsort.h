#ifndef QSORT_QSORT_H
#define QSORT_QSORT_H
#include <stdlib.h>
#include <memory.h>
#include <stddef.h>
void quicksort(void *ptr, size_t length, size_t size, int (*cmp)(const void *, const void *));
#endif //QSORT_QSORT_H
