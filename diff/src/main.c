#include <stdio.h>
#include <stdlib.h>
#include "compare.h"


enum errors {
    OpenFile
};

void error(const enum errors err) {
    switch (err) {
        case OpenFile:
            printf("Can't open file!\n For more instructions check --help");
            exit(OpenFile);
    }

}

int main(int argc, char *argv[]) {
    FILE *file_a, *file_b;
    if (argc == 3) {
        file_a = fopen(argv[1], "r");
        file_b = fopen(argv[2], "r");
        if (file_a == NULL || file_b == NULL) {
            error(OpenFile);
        }
    } else {
        printf("Compare files row by row\nSyntax is\ndiff <file1> <file2>");
        return 0;
    }
    struct diff_info_full result = isFilesDiffFull(file_a, file_b, malloc4Unit(), malloc4Unit());//inline malloc
    if(result.line_number == 0 && result.abs_char == 0){ //No diff
        printf("No difference");
        free4Unit(result.string_a);
        free4Unit(result.string_b);
        fclose(file_a);
        fclose(file_b);
        return 0;
    }
    printf("Diff in string %lld\nColumn %lld\nPreview:\n", result.line_number, result.abs_char+1);
    print4Unit(result.string_a);
    printf("\n");
    print4Unit(result.string_b);
    free4Unit(result.string_a);
    free4Unit(result.string_b);
    size_t place = result.abs_char;
    char ind[place+2];
    for (int i = 0; i < place; ++i) {
        ind[i] = ' ';
    }
    ind[place] = '^';
    ind[place+1] = '\0';
    printf("\n%s",ind);
    fclose(file_a);
    fclose(file_b);
    return 0;
}
