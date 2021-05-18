#ifndef QSORT_MSORT_H
#define QSORT_MSORT_H
#include <stdlib.h>
#include <memory.h>
#include <stddef.h>
void mergesort(void *ptr, size_t length, size_t size, int (*cmp)(const void *, const void *));
#endif //QSORT_MSORT_H
