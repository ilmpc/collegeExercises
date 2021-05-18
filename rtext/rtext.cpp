#include <fstream>
#include "rtext.h"

namespace RText {
    int replaceStrings(FILE *in, FILE *out, const char *what, const char *replacement) {
        std::string src(what);
        std::string dst(replacement);
        int replaced = 0;
        char *cbuffer = static_cast<char *>(malloc(sizeof(char) * 1024));
        while (!std::feof(in)) {
            std::fgets(cbuffer, 1023, in);
            std::string buffer(cbuffer);
            int n = buffer.find(src);
            while (n != std::string::npos) {
                buffer.replace(n, src.length(), dst);
                replaced++;
                n = buffer.find(src, n + dst.length());
            }
            fprintf(out, "%s", buffer.c_str());
        }
        free(cbuffer);
        return replaced;
    }

    int replaceStrings(const std::string &s_filename, const std::string &d_filename, const std::string &src,
                       const std::string &dst) {
        std::ifstream input;
        std::ofstream output;
        bool inplace = false;
        if (dst == src) {
            output.open(d_filename + ".temp", std::istream::out);
            inplace = true;
        } else {
            output.open(d_filename, std::istream::out);
        }
        input.open(s_filename, std::istream::in);

        if (!input.is_open()) {
            std::cerr << "Can't open input file " << std::endl;
            input.close();
            output.close();
            exit(1);
        }
        if (!output.is_open()) {
            std::cerr << "Can't open output file" << std::endl;
            input.close();
            output.close();
            exit(1);
        }
        int replaced = replaceStrings(input, output, src, dst);
        input.close();
        output.close();
        if (inplace) {
            std::remove(s_filename.c_str());
            std::rename((d_filename + ".temp").c_str(), s_filename.c_str());
        }
        return replaced;
    }

    int replaceStrings(std::ifstream &input, std::ostream &output, const std::string &src, const std::string &dst) {
        int replaced = 0;
        std::string buffer((std::istreambuf_iterator<char>(input)),
                             std::istreambuf_iterator<char>());
        int n = buffer.find(src);
        while (n != std::string::npos) {
            buffer.replace(n, src.length(), dst);
            replaced++;
            n = buffer.find(src, n + dst.length());
        }
        output << buffer;
        return replaced;
    }
}


