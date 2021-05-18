#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "src/point.h"
#include "src/circle.h"
#include "src/new.h"
#include "src/rect.h"
#include "src/line.h"

#define STR_BUFF_SIZE (1000)
#define BUFFER_SIZE (100)
typedef struct {
    void **items;
    size_t size;
} Array;

void exec_objs(void(*exec)(void *), Array *array) {
    for (int i = 0; i < array->size; ++i) {
        exec(array->items[i]);
    }
}

void const_exec_objs(void(*exec)(const void *), Array *array) {
    for (int i = 0; i < array->size; ++i) {
        exec(array->items[i]);
    }
}

void *generate_obj(char *string) {
    char name[32];
    int arg1 = 0, arg2 = 0, arg3 = 0, arg4 = 0;
    int read;
    read = sscanf(string, "%s%d%d%d%d", name, &arg1, &arg2, &arg3, &arg4);
    if (read == 0) return NULL;
    if (strcmp(name, "point") == 0 && read == 3) {
        return new(Point, arg1, arg2);
    }
    if (strcmp(name, "line") == 0 && read == 5) {
        return new(Line, arg1, arg2, arg3, arg4);
    }
    if (strcmp(name, "rect") == 0 && read == 5) {
        return new(Rect, arg1, arg2, arg3, arg4);
    }
    if (strcmp(name, "circle") == 0 && read == 4) {
        return new(Circle, arg1, arg2, arg3);
    }
    fprintf(stderr, "Can't resolve string: \"%s\"",string);
    return NULL;
}

Array *parse_file(FILE *ptr_file) {
    size_t buff_size = BUFFER_SIZE;
    void **objs = malloc(buff_size * sizeof(void *));
    char buf[STR_BUFF_SIZE];
    size_t objs_l = 0;
    while (fgets(buf, STR_BUFF_SIZE, ptr_file) != NULL) {
        if (objs_l == buff_size) {
            buff_size *= 2;
            objs = realloc(objs, buff_size * sizeof(void*));
        }
        void *p = generate_obj(buf);
        if (p != NULL) {
            objs[objs_l++] = p;
        }
    }
    printf("%zd objects created\n", objs_l);
    Array *array = malloc(sizeof(Array));
    array->items = objs;
    array->size = objs_l;
    return array;
}

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    FILE *ptr_file = fopen(argv[1], "r");
    if (!ptr_file)
        return -1;
    Array *objs = parse_file(ptr_file);
    const_exec_objs(draw, objs);
    exec_objs(delete, objs);
}