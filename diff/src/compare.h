#ifndef DIFF_COMPARE_H
#define DIFF_COMPARE_H
#define BUFF_SIZE 16
struct diff_info {
    char string_a[BUFF_SIZE];
    char string_b[BUFF_SIZE];
    size_t line_number;
    size_t rel_char;
    size_t abs_char;
};
struct diff_info_full {
    struct unit *string_a;
    struct unit *string_b;
    size_t line_number;
    size_t abs_char;
};
struct unit {
    char *data;
    struct unit *next;
};

void print4Unit(const struct unit *p);

struct unit *malloc4Unit();

int length4Unit(const struct unit *p);

void free4Unit(struct unit *p);

int isStringsDiff(const char *first, const char *second);

struct diff_info isFilesDiffBuff(FILE *file_a, FILE *file_b);

struct diff_info_full
isFilesDiffFull( FILE *file_a, FILE *file_b, struct unit *string_a, struct unit *string_b);

#endif //DIFF_COMPARE_H
