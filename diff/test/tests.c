#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/compare.h"

int Test_isStringsDiff() {
    const char *str1 = "qwert\n", *str2 = "qwerty", *str3 = "qwTer";
    assert(isStringsDiff(str1, str1) == 0);
    assert(isStringsDiff(str2, str1) == 6);
    assert(isStringsDiff(str3, str1) == 3);
    assert(isStringsDiff("qwerty", "qwerty") == 0);
    return 0;
}

int Test_isFileDiffBuff(const char *file1, const char *file2) {
    FILE *file_a, *file_b;
    file_a = fopen(file1, "r");
    file_b = fopen(file2, "r");
    struct diff_info result = isFilesDiffBuff(file_a, file_b);//inline malloc
    if (result.line_number == 0 && result.abs_char == 0) { //No diff
        printf("No difference\n");
        fclose(file_a);
        fclose(file_b);
        return 0;
    }
    printf("Diff in string %lld\nColumn %lld\nPreview:\n%s\n%s\n", result.line_number, result.abs_char + 1, result.string_a, result.string_b);
    size_t place = result.rel_char;
    char ind[place + 2];
    for (int i = 0; i < place; ++i) {
        ind[i] = ' ';
    }
    ind[place] = '^';
    ind[place + 1] = '\0';
    printf("%s\n", ind);
    fclose(file_a);
    fclose(file_b);
    return 1;
}

int main() {
    printf("Hello, I'm test!\n");
    Test_isStringsDiff();
    Test_isFileDiffBuff("../one", "../one");
    printf("-------------------------\n");
    Test_isFileDiffBuff("../one", "../two");
    printf("-------------------------\n");
    printf("%d", isStringsDiff("123\n223\n", "123\n123\n"));
    return 0;
}