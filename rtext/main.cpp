#include <iostream>
#include <string>
#include "rtext.h"


int main(int argc, char *argv[]) {
    if (argc == 5) {
        std::ios::sync_with_stdio(false);
        std::cout << RText::replaceStrings(argv[1], argv[2], argv[3], argv[4]) << " ocasion(s) replaced!" << std::endl;
    } else {
        std::string old = "old";
        if (argc == 6 && old == argv[5]) {
            FILE *in = fopen(argv[1], "r");
            FILE *out = fopen(argv[2], "w");
            std::cout << RText::replaceStrings(in, out, argv[3], argv[4]) << " ocasion(s) replaced!"
                      << std::endl;
            std::fclose(in);
            std::fclose(out);
        } else { std::cerr << "Wrong parametrs!\nWaiting: inp_filename out_filename source_string dst_string" << std::endl; }
    }
    return 0;
}