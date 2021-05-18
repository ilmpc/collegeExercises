#ifndef QSORT_SORTS_H
#define QSORT_SORTS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "qsort.h"
#include "msort.h"
void set_sorting(char method);

void sort_int(FILE *input, FILE *output);

void sort_double(FILE *input, FILE *output);

void sort_char(FILE *input, FILE *output);

#endif //QSORT_SORTS_H
