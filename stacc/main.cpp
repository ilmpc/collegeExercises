#include <iostream>
#include <fstream>
#include "lib/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        ifstream input(argv[1], ifstream::in);
        auto parser = new class parser(&input, nullptr);
        parser->parse();
    } else {
        auto parser = new class parser(&cin, &cout); //TODO need to be tested
    }
}
//For further testing
/*
    auto myStack = new stack(10);
    auto fabric = new IOperationFactory(myStack);
    auto args = new std::list<double>();
    for (int i = 1; i < 10; ++i) {
        args->push_back(-1085. / i);
    }
    fabric->createOperation("push", args)->exec();
    for (int i = 1; i < 10; ++i) {
        fabric->createOperation("print", nullptr)->exec();
    }
    //fabric->createOperation("sqrt1", nullptr)->exec();
    std::cout << std::endl;
    return 0;

 */