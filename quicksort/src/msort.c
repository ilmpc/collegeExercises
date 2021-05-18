#include "msort.h"

static size_t s_t_size;

static int (*s_t_cmp)(const void *, const void *);

static void makeOrder(void *first, void *last);

static void merge(void *first, void *middle, void *last);

//------------------------------------------------------------------

void mergesort(void *ptr, size_t length, size_t size, int (*cmp)(const void *, const void *)) {
    s_t_size = size;
    s_t_cmp = cmp;
    makeOrder(ptr, ptr + (length - 1) * size);
}

static void makeOrder(void *first, void *last) {
    if (first < last) {
        void *middle = first + (last - first) / s_t_size / 2 * s_t_size;

        makeOrder(first, middle);
        makeOrder(middle + s_t_size, last);
        merge(first, middle, last);
    }
}

static void merge(void *first, void *middle, void *last) {

    size_t length_L = middle - first + 1 * s_t_size;
    size_t length_R = last - middle;

    // create temp arrays
    void *L = malloc(length_L * s_t_size);
    void *R = malloc(length_R * s_t_size);

    // Copy data to temp arrays L and R
    memcpy(L, first, length_L);
    memcpy(R, middle + 1 * s_t_size, length_R);
    void *L_p = L,     //Left subarray
            *R_p = R,     //Right subarray
            *M_p = first; //Merged array
    while ((L_p - L) < length_L && (R_p - R) < length_R) {
        if (s_t_cmp(L_p, R_p) <= 0) {
            memcpy(M_p, L_p, s_t_size);
            L_p += s_t_size;
        } else {
            memcpy(M_p, R_p, s_t_size);
            R_p += s_t_size;
        }
        M_p += s_t_size;
    }

    // Copy the remaining elements of L
    while ((L_p - L) < length_L) {
        memcpy(M_p, L_p, s_t_size);
        L_p += s_t_size;
        M_p += s_t_size;
    }

    //Copy the remaining elements of R
    while ((R_p - R) < length_R) {
        memcpy(M_p, R_p, s_t_size);
        R_p += s_t_size;
        M_p += s_t_size;
    }
    free(L);
    free(R);
}

