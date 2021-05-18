#include <iostream>
#include "Matrix.h"
using namespace std;
int main() {
    auto a = Matrix(4, 3, {1.0, 2, 0,
                           3, 8, 1,
                           0, 7, 3});
    auto c = Matrix(4, 4, {5, 19, 14, 0, 19, 74, 59, 0, 14, 59, 58});
    auto b = a * ~a;
    std::cout << (b == c);
}