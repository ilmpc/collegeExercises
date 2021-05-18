#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "compare.h"

void print4Unit(const struct unit *p) {
    while (1) {
        printf("%s", p->data);
        if (p->next != NULL)
            p = p->next;
        else
            return;
    }
}

int length4Unit(const struct unit *p) {
    int res = 0;
    while (p->next != NULL) {
        for (int i = 0; p->data[i] != '\0'; ++i) {
            if (p->data[i] == '\n')
                return res;
            res++;
        }
    }
    return res;
}

struct unit *malloc4Unit() {
    struct unit *result = malloc(sizeof(struct unit));
    char *string = malloc(BUFF_SIZE * sizeof(char));
    result->next = NULL;
    result->data = string;
    return result;
}

void free4Unit(struct unit *p) {
    if (p == NULL)
        return;
    free4Unit(p->next);
    free(p->data);
    free(p);
}

int isStringsDiff(const char *first, const char *second) {
    int counter = 0, endl = 0;
    while (first[counter] == second[counter]) {
        if (first[counter] == '\0' || second[counter] == '\0') {
            endl = 1;
            break;
        }
        counter++;
    }
    if (endl) {
        return 0; //no diff
    }
    return ++counter;
}

struct diff_info isFilesDiffBuff(FILE *file_a,FILE *file_b) {
    assert(file_a != NULL && file_b != NULL);
    char buffer_a[BUFF_SIZE], buffer_b[BUFF_SIZE];
    size_t rel_char = 0, abs_char = 0, line_number = 1;
    while (!feof(file_a) || !feof(file_b)) {
        fgets(buffer_a, BUFF_SIZE, file_a);
        fgets(buffer_b, BUFF_SIZE, file_b);

        for (int i = 0;; ++i) {
            if (buffer_a[i] != buffer_b[i]) {
                struct diff_info result = {.line_number = line_number, .rel_char=rel_char, .abs_char=abs_char};
                for (int j = 0; buffer_a[j] != '\0'; ++j) { //TODO optimize code
                    result.string_a[j] = buffer_a[j];
                    if (buffer_a[j] == '\n') {
                        result.string_a[j] = '\0';
                        break;
                    }
                }
                for (int j = 0; buffer_b[j] != '\0'; ++j) {
                    result.string_b[j] = buffer_b[j];
                    if (buffer_b[j] == '\n') {
                        result.string_b[j] = '\0';
                        break;
                    }
                }
                return result;
            }
            if (buffer_a[i] == '\n') {
                abs_char = 0;
                rel_char = 0;
                line_number++;
                break;
            }
            if (buffer_a[i] == '\0') {
                rel_char = 0;
                break;
            }
            abs_char++;
            rel_char++;
        }

    }
    return (struct diff_info){.line_number = 0, .abs_char = 0};
}

void readToEndIfNeeded(struct unit *buffer_a, FILE *file_a) {
    struct unit *p = buffer_a;
    char temp;
    for (int i = 0; (temp = p->data[i]) != '\0'; ++i) {
        if (temp == '\n')
            return;
    }
    while (!feof(file_a)) {
        p->next = malloc4Unit();
        p = p->next;
        fgets(p->data, BUFF_SIZE, file_a);
        for (int i = 0; i < BUFF_SIZE; ++i) {
            if (p->data[i] == '\n') {
                p->data[i] = '\0';
                return;
            }
        }

    }
}

struct diff_info_full
isFilesDiffFull(FILE *file_a, FILE *file_b, struct unit *const string_a, struct unit *const string_b) {
    assert(file_a != NULL && file_b != NULL);
    struct unit *buffer_a = string_a, *buffer_b = string_b;
    size_t abs_char = 0, line_number = 1, diff_flag = 0;

    while ((!feof(file_a) || !feof(file_b)) && !diff_flag) {
        fgets(buffer_a->data, BUFF_SIZE, file_a);
        fgets(buffer_b->data, BUFF_SIZE, file_b);

        for (int i = 0;; ++i) {
            if (buffer_a->data[i] != buffer_b->data[i]) {
                diff_flag = 1;
                break;
            }
            if (buffer_a->data[i] == '\n') {
                free4Unit(string_a->next);
                free4Unit(string_b->next);
                string_a->next = NULL;
                string_b->next = NULL;
                buffer_a = string_a;
                buffer_b = string_b;
                abs_char = 0;
                line_number++;
                break;
            }
            if (buffer_a->data[i] == '\0') {
                buffer_a->next = malloc4Unit();
                buffer_b->next = malloc4Unit();
                buffer_a = buffer_a->next;
                buffer_b = buffer_b->next;
                break;
            }
            abs_char++;
        }
    }
    if (!diff_flag) {
        struct diff_info_full result = {.string_a = string_a, .string_b = string_b, .line_number = 0, .abs_char = 0};
        return result;
    }

    readToEndIfNeeded(buffer_a, file_a);
    readToEndIfNeeded(buffer_b, file_b);

    for (int j = 0; buffer_a->data[j] != '\0'; ++j) { //TODO optimize code
        if (buffer_a->data[j] == '\n') {
            buffer_a->data[j] = '\0';
            break;
        }
    }
    for (int j = 0; buffer_b->data[j] != '\0'; ++j) {
        if (buffer_b->data[j] == '\n') {
            buffer_b->data[j] = '\0';
            break;
        }
    }
    struct diff_info_full result = {.string_a = string_a, .string_b = string_b, .line_number = line_number, .abs_char=abs_char};

    return result;
}