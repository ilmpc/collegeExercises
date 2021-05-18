#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "src/file_sorts.h"
void printHelp(){
    printf("qsort <data_file> <data_type> <sorting algorithm>(optionaly)\nData types:\n\ti - Integers\n\tf,d - Double\n\tc - Char\nSorting algorithms:\n\tq - quicksort\n\tm - mergesort (default)\n");
}
int main(int argc, char *argv[]) {
    if(argc <= 2){
        printHelp();
        exit(0);
    }
    FILE *input, *output;
    char file_name[256];
    strcpy(file_name, argv[1]);
    if (argc > 1)
        input = fopen(file_name, "r");
    else
        exit(1);
    output = fopen(strcat(file_name, ".sort"), "w");
    if(input == NULL || output == NULL){
        printf("Can't open file!\n");
        printHelp();
        exit(2);
    };
    if(argc == 4) set_sorting(*argv[3]);
    switch(*argv[2]){
        case 'i':
            sort_int(input,output);
            break;
        case 'f':
        case 'd':
            sort_double(input,output);
            break;
        case 'c':
            sort_char(input,output);
            break;
        default:
            printf("Possible cases: i - Integer, d(f) - Double, c - Char");
            break;
    }

    fclose(input);
    fclose(output);
}