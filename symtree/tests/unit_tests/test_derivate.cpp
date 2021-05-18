#include <binaryExpression.h>
#include <number.h>
#include <variable.h>
#include "gtest/gtest.h"
TEST(Derivate,Number){
    Number a = 18;
    Number b = 20;
    Variable x = 'x';
    auto c = a.derivate(x);
}
