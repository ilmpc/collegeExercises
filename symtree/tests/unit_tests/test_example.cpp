#include <binaryExpression.h>
#include <number.h>
#include <variable.h>
#include "gtest/gtest.h"
class Example:public ::testing::Test{
public:
    Number a = 1.8;
    Number b = 2;
};
TEST_F(Example, Sum) {
    binaryExpression f(a, b, '+');
    std::ostringstream res;
    res << f.toString() << " = " << f.eval();
    EXPECT_EQ(res.str(),"1.8 + 2 = 3.8");
}
TEST_F(Example, Sub) {
    binaryExpression f(a, b, '-');
    std::ostringstream res;
    res << f.toString() << " = " << f.eval();
    EXPECT_EQ(res.str(),"1.8 - 2 = -0.2");
}
TEST_F(Example, Der) {
    binaryExpression f(a, b, '/');
    std::ostringstream res;
    res << f.toString() << " = " << f.eval();
    EXPECT_EQ(res.str(),"1.8 / 2 = 0.9");
}
TEST_F(Example, Mult) {
    binaryExpression f(a, b, '*');
    std::ostringstream res;
    res << f.toString() << " = " << f.eval();
    EXPECT_EQ(res.str(),"1.8 * 2 = 3.6");
}
TEST_F(Example, Custom){
    binaryExpression f(a,b, '~',[](double a,double b) -> double { return (a * 82 - 2 + (b - a)*(b + a)/18) * 17.432; });
    std::ostringstream res;
    res << f.toString() << " = " << f.eval();
    EXPECT_EQ(res.str(),"1.8 ~ 2 = 2538.84");
}
TEST_F(Example, Var){
    Variable a("var");
    Number b = 2;
    binaryExpression f(a, b, '*');
    EXPECT_EQ(f.toString(),"var * 2");
    std::map<std::string,double> def = {{"var",8}};
    EXPECT_EQ(f.eval(&def),16);
}
