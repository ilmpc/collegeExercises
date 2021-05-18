#include "number.h"
#include "binaryExpression.h"
#include <iostream>

int main() {
    Number a = 1.8;
    Number b = 2;
    binaryExpression sum(a, b, '*');
    std::cout << sum.toString() << " = " << sum.eval();
}