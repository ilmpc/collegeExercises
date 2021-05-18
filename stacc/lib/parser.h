#ifndef STACC_PARSER_H
#define STACC_PARSER_H


#include <istream>
#include <string>
#include <cctype>
#include <cstring>
#include <map>
#include <list>
#include <algorithm>
#include "IOperationFactory.h"

class parser {
private:
    const unsigned int MAX_LEN = 2048;
    std::istream *mInput;
    std::ostream *mOutput;
    std::map<std::string, double> *mDefenitions;
    stack *mStack;
    IOperationFactory *mFactory;
    int getWord(const char *line, char *word, int *iter);
public:
    explicit parser(std::istream *input, std::ostream *output);

    ~parser();

    void parse();

};


#endif //STACC_PARSER_H
