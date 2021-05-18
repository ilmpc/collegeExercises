#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lib/de_base64.h"



int main(int argc, char *argv[]) {
    FILE *input, *output;
    int flag_e_d;
    if (argc == 4) {
        if (!strcmp(argv[1], "-d")) {
            flag_e_d = 2;
        } else {
            flag_e_d = -1;
        }
        if (!strcmp(argv[1], "-e")) {
            flag_e_d = 1;
        }
        if (flag_e_d > 0) {
            input = fopen(argv[2], "rb");
            output = fopen(argv[3], "wb");
            if (input == NULL || output == NULL)
                flag_e_d = -1;
        }
    } else {
        flag_e_d = 0;
    }
    switch (flag_e_d) {
        case -1:
            printf("Argument error\n");
        case 0:
            printf("Base64 decoder/encoder\nbase64 -e <input> <output>    encode input file using base64\nbase64 -d <input> <output>    decode input file using base64\n");
            exit(0);
        case 1:
            encode_file(input, output);
            break;
        case 2:
            decode_file(input, output);
            break;
    }
    fclose(output);
    fclose(input);
}