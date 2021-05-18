#include "file_sorts.h"

static void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void *)) = &mergesort;

static int cmp_int(const void *a, const void *b);

static int cmp_double(const void *a, const void *b);

static int cmp_char(const void *a, const void *b);

static void *reallocate(void *old_data, size_t old_size, size_t new_size, size_t data_size);

//----------------------------------------------------------------------------------------------

static int cmp_int(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}
static int cmp_char(const void *a, const void *b) {
    return *((char *) a) - *((char *) b);
}


static int cmp_double(const void *a, const void *b) {
    double result = *((double *) a) - *((double *) b);
    if (result > 0)
        return 1;
    if (result < 0)
        return -1;
    return 0; //Норм ли?
}

static void *reallocate(void *old_data, size_t old_size, size_t new_size, size_t data_size) {
    void *new_data = malloc(new_size * data_size);
    memcpy(new_data, old_data, old_size * data_size);
    free(old_data);
    return new_data;
}

void sort_int(FILE *input, FILE *output) {
    assert(input != NULL && output != NULL);
    size_t size = 1024;
    int *arr = malloc(sizeof(int) * size);
    if (arr == NULL) {
        exit(666);
    }
    size_t r_size = 0;
    do {
        if(fscanf(input, "%d", arr + r_size) == EOF) break;
        if (r_size == (size - 1)) {
            size *= 2;
            arr = reallocate(arr, r_size + 1, size, sizeof(int));
        }
        ++r_size;
    } while (!feof(input));
    sort(arr, r_size, sizeof(int), cmp_int);
    for (int i = 0; i < r_size; ++i) {
        fprintf(output, "%d ", arr[i]);
    }
    free(arr);
}

void sort_double(FILE *input, FILE *output) {
    assert(input != NULL && output != NULL);
    size_t size = 1024;
    double *arr = malloc(sizeof(double) * size);
    if (arr == NULL) {
        exit(666);
    }
    size_t r_size = 0;
    do {
        if (fscanf(input, "%lf", arr + r_size) == EOF) break;
        if (r_size == (size - 1)) {
            size *= 2;
            arr = reallocate(arr, r_size + 1, size, sizeof(double));
        }
        ++r_size;
    } while (!feof(input));
    sort(arr, r_size, sizeof(double), cmp_double);
    for (int i = 0; i < r_size; ++i) {
        fprintf(output, "%lf ", arr[i]);
    }
    free(arr);
}

void sort_char(FILE *input, FILE *output) {
    assert(input != NULL && output != NULL);
    size_t size = 1024;
    char *arr = malloc(sizeof(char) * size);
    if (arr == NULL) {
        exit(666);
    }
    size_t r_size = 0;
    do {
        if (fscanf(input, "%c", arr + r_size) == EOF) break;
        if (r_size == (size - 1)) {
            size *= 2;
            arr = reallocate(arr, r_size + 1, size, sizeof(char));
        }
        ++r_size;
    } while (!feof(input));
    sort(arr, r_size, sizeof(char), cmp_char);
    for (int i = 0; i < r_size; ++i) {
        fprintf(output, "%c", arr[i]);
    }
    free(arr);
}

void set_sorting(char method) {
    switch (method) {
        case 'm':
            sort = &mergesort;
            break;
        case 'q':
            sort = &quicksort;
            break;
        default:
            sort = &mergesort;
    }
}


