#include <Matrix.h>
#include "gtest/gtest.h"
#include <iostream>

TEST(NullCases, Constructors) {
    //Default
    auto a = new Matrix();
    EXPECT_NE(nullptr, a);
    //Copy
    auto b = new Matrix(*a);
    EXPECT_NE(nullptr, b);
    //std::cout << '\n' << typeid((*a)[0]).name() << ' ' << typeid((*a)[0][0]).name();
    a->at(0, 0) = 10;
    b->at(0, 0) = 0;
    EXPECT_EQ(a->at(0, 0), 10);
    EXPECT_EQ(b->at(0, 0), 0);
    //Special size
    auto c = new Matrix(5, 8);
    EXPECT_NE(nullptr, c);
    EXPECT_EQ(c->getColumns(), 8);
    EXPECT_EQ(c->getRows(), 5);
    //Expect no out of bound exceptions
    c->at(4, 7) = 10;
    EXPECT_EQ(c->at(4, 7), 10);
    // 0,0 size
    EXPECT_THROW(new Matrix(0, 0), std::invalid_argument);
    //neg size
    EXPECT_THROW(new Matrix(-1, 5), std::invalid_argument);
    EXPECT_THROW(new Matrix(-1, -1), std::invalid_argument);
    EXPECT_THROW(new Matrix(-1, -1, {1, 2, 3}), std::invalid_argument);
    delete a;
    delete b;
    delete c;
}

TEST(NullCases, Get) {
    Matrix a(5, 8);
    EXPECT_EQ(a.getRows(), 5);
    EXPECT_EQ(a.getColumns(), 8);

}

TEST(NullCases, static_matrixes) {
    auto a = Matrix::getZero(4, 3);
    for (auto it:a) {
        EXPECT_EQ(it, 0);
    }
    auto b = Matrix::getIdentity(4);
    for (int i = 0; i < b.getRows(); ++i) {
        for (int j = 0; j < b.getColumns(); ++j) {
            EXPECT_EQ(b[i][j], i==j?1:0);
        }
    }
}
