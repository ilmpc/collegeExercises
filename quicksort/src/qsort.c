#include <stddef.h>
#include "qsort.h"

static int size_flag;
static size_t s_t_size;

static int (*s_t_cmp)(const void *, const void *);

static void makeOrder(void *arr, ptrdiff_t first, ptrdiff_t last);

static void *selectPivot(void *first, void *last);

static void swap(void *left, void *right);

//------------------------------------------------------------------

void quicksort(void *ptr, size_t length, size_t size, int (*cmp)(const void *, const void *)) {
    s_t_size = size;
    s_t_cmp = cmp;
    size_flag = 0;
    makeOrder(ptr, 0, length - 1);
}

static void makeOrder(void *arr, ptrdiff_t first, ptrdiff_t last) {
    ptrdiff_t l_ind = first, r_ind = last;

    //------Выбор и копирование разделеителя----
    char flag = 0;
    void *pivot;
    size_t buff = 0;
    if (size_flag || s_t_size <= sizeof(size_t)) { //Выбор между стеком и кучей
        pivot = &buff;
        if (!size_flag) //Будет ли это быстрее?
            size_flag = 1;
    } else {
        pivot = malloc(s_t_size);
        flag = 1;
    }
    memcpy(pivot, selectPivot(arr + first * s_t_size, arr + last * s_t_size), s_t_size);
    //------------------------------------------

    while (l_ind <= r_ind) {
        while (s_t_cmp(((char *) arr + l_ind * s_t_size), pivot) < 0) ++l_ind;
        while (s_t_cmp(((char *) arr + r_ind * s_t_size), pivot) > 0) --r_ind;
        if (l_ind <= r_ind) {
            if (l_ind < r_ind) {
                swap((char *) arr + (l_ind * s_t_size), (char *) arr + (r_ind * s_t_size));
            }
            --r_ind;
            ++l_ind;
        }
    }
    if (flag) free(pivot);
    if (first < r_ind) {
        makeOrder(arr, first, r_ind);
    }
    if (l_ind < last) {
        makeOrder(arr, l_ind, last);
    }

}

static void *selectPivot(void *first, void *last) {
    void *m = first + (last - first) / s_t_size / 2 * s_t_size;
    void *arr[3] = {first, m, last};
    for (int i = 1; i < 3; ++i) {
        if (s_t_cmp(arr[i], arr[0]) > 0) {
            void *temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
        }
    }
    if (s_t_cmp(arr[1], arr[2]) > 0)
        return arr[1];
    else
        return arr[2];
}

static void swap(void *left, void *right) {
    char flag = 0;
    void *temp;
    size_t buff;
    if (size_flag || s_t_size <= sizeof(size_t)) { //Выбор между стеком и кучей
        temp = &buff;
        if (!size_flag) //Будет ли это быстрее?
            size_flag = 1;
    } else {
        temp = malloc(s_t_size);
        flag = 1;
    }
    memcpy(temp, right, s_t_size);
    memcpy(right, left, s_t_size);
    memcpy(left, temp, s_t_size);
    if (flag) free(temp);
}


