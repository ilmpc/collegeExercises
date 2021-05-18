#include <Matrix.h>
#include "gtest/gtest.h"

class TestWithAB : public ::testing::Test {
protected:
    TestWithAB() {}

    ~TestWithAB() {}

    void SetUp() {
        a = new Matrix(4, 3, {1.0, 2, 0,
                              3, 8, 1,
                              0, 7, 3});
        b = new Matrix(~(*a));
        c = new Matrix(4, 3, {7, 1, 3, 3, 0, 0, -2, 8, 1, 0, 3.5, 7});
    }

    void TearDown() {
        delete a;
        delete b;
        delete c;
    }

    Matrix *a, *b, *c;
};

TEST_F(TestWithAB, Equals) {
    auto c = Matrix(4, 4, {5, 19, 14, 0, 19, 74, 59, 0, 14, 59, 58});
    auto d = (*a) * (*b);
    EXPECT_EQ(c, d);
}

TEST_F(TestWithAB, SumAndConstMultiply) {
    auto c = *a + *a;
    auto d = *a * 2;
    EXPECT_EQ(c, d);
}

TEST_F(TestWithAB, CheckCompatability) {
    EXPECT_THROW(*a + *b, std::invalid_argument);
    EXPECT_THROW(*a - *b, std::invalid_argument);
    EXPECT_THROW(*a * *a, std::invalid_argument);
}

TEST_F(TestWithAB, SumAndMinus) {
    auto d = *a - *c;
    EXPECT_EQ(d + *c, *a);
}

TEST_F(TestWithAB, DeriviateConst) {
    auto d = *a / 2;
    EXPECT_EQ(d * 2, *a);
}
TEST_F(TestWithAB, CallDetAndLUDOnNonSquareMatrix){
    EXPECT_THROW(a->determinant(), std::invalid_argument);
    EXPECT_THROW(a->LUDecompose(), std::invalid_argument);
}
TEST_F(TestWithAB, Determinant){
    EXPECT_EQ((*a * *b).determinant(), 0 );
    auto d = *a + *c;
    d = d * ~d;
    EXPECT_NEAR(d.determinant() , 0,1E-8);
}