#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <initializer_list>
#include <string>

class Matrix {
private:
    int rows, columns;
    double *data;
    void _checkCompatibility(const Matrix &right) const;
    //double _minor(int dimension, int originR, int originC) const;
public:
    typedef double* iterator;
    typedef const double* const_iterator;

    class MRow{
        friend class Matrix;
        private:
            Matrix &parent;
            int row;
            MRow(Matrix &parent, int row);
        public:
            double& operator[](const int &index);
            bool operator==(const MRow &right) const;
    };
    class MRowConst{
        friend class Matrix;
        private:
            const Matrix &parent;
            int row;
            MRowConst(const Matrix &parent,int row);
        public:
            const double& operator[](const int &index) const;
            bool operator==(const MRow &right) const;
    };

    iterator begin();
    iterator end();
    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;
    Matrix();
    Matrix(const Matrix &right);
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, std::initializer_list<double> initializerList);
    ~Matrix();
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getColumns() const;
    Matrix& operator=(const Matrix &right);
    bool operator==(const Matrix &right) const;
    Matrix operator-() const;
    Matrix operator+(const Matrix &right) const;
    Matrix operator-(const Matrix &right) const;
    Matrix operator*(const Matrix &right) const;
    Matrix operator*(const double &right) const;
    Matrix operator/(const double &right) const;
    MRowConst operator[](const int &index) const;
    MRow operator[](const int &index);
    Matrix operator~() const; //transpose
    double& at(int rows, int columns);
    [[nodiscard]] const double& at(int rows, int columns) const;
    [[nodiscard]] double determinant() const;
    static Matrix getZero(int rows, int columns);
    static Matrix getIdentity(int dimension);
    [[nodiscard]] Matrix LUDecompose() const;
    [[nodiscard]] std::string toString(int precision = -1) const;
};



#endif //MATRIX_MATRIX_H
