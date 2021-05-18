#include "parser.h"

parser::parser(std::istream *input, std::ostream *output) : mInput(input), mOutput(output),
                                                            mDefenitions(new std::map<std::string, double>()),
                                                            mStack(new stack()),
                                                            mFactory(new IOperationFactory(mStack)) {}

parser::~parser() {
    delete mFactory;
    delete mStack;
    delete mDefenitions;
}

void parser::parse() {
    char line[MAX_LEN + 1];
    char word[MAX_LEN / 4];
    int size;
    while (mInput->getline(line, MAX_LEN)) {
        if ((size = static_cast<int>(std::strlen(line))) == 0) continue;
        if (*line == '#') continue;
        for (int i = 0; i < size; ++i) {
            line[i] = tolower(line[i]);
        }
        int line_index = 0;
        getWord(line, word, &line_index); //getting name of func
        if (strcmp(word, "define") == 0) { //Define feature

            if (!getWord(line, word, &line_index)) {
                throw std::invalid_argument("Definition must have args"); //get name of definition
            }
            std::string name = word;
            mDefenitions->erase(name); //Redefining
            if (!getWord(line, word, &line_index)) {
                throw std::invalid_argument("Definition must have args"); //get number
            }
            double num;
            try {
                num = std::stod(word, nullptr);
            } catch (std::logic_error &a) {
                throw std::invalid_argument("Can't resolve number");
            }
            mDefenitions->insert(std::pair<std::string, double>(name, num));
            continue;
        }
        std::string f_name = word;
        //read arguments
        auto args = new std::list<double>();
        while (getWord(line, word, &line_index)) {
            double arg;
            try {
                arg = mDefenitions->at(std::string(word));
            } catch (std::out_of_range &a) {
                try {
                    arg = std::stod(word, nullptr);
                } catch (std::logic_error &a) {
                    throw std::invalid_argument("Can't resolve number");
                }
            }
            args->push_back(arg);
        }
        auto temp = mFactory->createOperation(f_name, args);
        temp->exec();
        *line = '\0';
    }

}

int parser::getWord(const char *line, char *word, int *iter) {
    int k;
    for (k = 0; line[k + *iter] != '\0' && line[k + *iter] != ' '; ++k) {
        word[k] = line[*iter + k];
    }
    if (line[k + *iter] == '\0') {
        word[k] = '\0';
    } else {
        word[k++] = '\0';
    }
    *iter += k;
    return k;
}
