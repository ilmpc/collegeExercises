#include <algorithm>
#include <stdexcept>
#include <sstream>
#include "Matrix.h"

Matrix::MRow::MRow(Matrix &parent, int row) : parent(parent), row(row) {}

double &Matrix::MRow::operator[](const int &index) {
    if (index >= parent.columns) {
        throw std::out_of_range("Обращение к элементу вне матрицы");
    }
    return parent.at(row, index);
}

bool Matrix::MRow::operator==(const Matrix::MRow &right) const {
    if (parent.columns == right.parent.columns) {
        for (int i = 0; i < parent.columns; ++i) {
            if (parent.at(row, i) != right.parent.at(right.row, i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Matrix::MRowConst::MRowConst(const Matrix &parent, int row) : parent(parent), row(row) {}

const double &Matrix::MRowConst::operator[](const int &index) const {
    if (index >= parent.columns) {
        throw std::out_of_range("Обращение к элементу вне матрицы");
    }
    return parent.at(row, index);
}

bool Matrix::MRowConst::operator==(const Matrix::MRow &right) const {
    if (parent.columns == right.parent.columns) {
        for (int i = 0; i < parent.columns; ++i) {
            if (parent.at(row, i) != right.parent.at(right.row, i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

//Iterator stuff
Matrix::iterator Matrix::begin() {
    return data;
}

Matrix::iterator Matrix::end() {
    return data + rows * columns;
}


Matrix::const_iterator Matrix::begin() const {
    return data;
}

Matrix::const_iterator Matrix::end() const {
    return data + rows * columns;
}


//Matrix class

Matrix::Matrix() : Matrix(3, 3) {}

Matrix::Matrix(const Matrix &right) {
    rows = right.rows;
    columns = right.columns;
    data = new double[rows * columns];
    std::copy_n(right.data, rows * columns, data);
}

Matrix::Matrix(int rows, int columns) :
        rows(rows), columns(columns) {
    if (rows > 0 && columns > 0) {
        data = new double[rows * columns];
    } else {
        throw std::invalid_argument("Размерности матрицы не могут быть меньше нуля");
    }
}

Matrix::Matrix(int rows, int columns, std::initializer_list<double> initializerList) : Matrix(rows, columns) {
    if (initializerList.size() > rows * columns) {
        throw std::length_error("Инициализатор больше, чем размер матрицы");
    }
    int i = 0;
    for (double it : initializerList) {
        this->data[i++] = it;
    }
    for (; i < rows * columns; ++i) {
        this->data[i] = 0;
    }
}

Matrix::~Matrix() {
    delete[] data;
}

int Matrix::getRows() const {
    return this->rows;
}

int Matrix::getColumns() const {
    return this->columns;
}

Matrix &Matrix::operator=(const Matrix &right) {
    if (this == &right || right.data == this->data) {
        return *this;
    }
    delete[] this->data;
    rows = right.rows;
    columns = right.columns;
    data = new double[rows * columns];
    std::copy_n(right.data, rows * columns, data);
    return *this;
}

bool Matrix::operator==(const Matrix &right) const {
    if (&right == this) {
        return true;
    }
    if (this->columns == right.columns) {
        if (this->rows == right.rows) {
            for (int i = 0; i < rows * columns; ++i) {
                if (this->data[i] != right.data[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

Matrix Matrix::operator-() const {
    Matrix result(*this);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] = -result.data[i];
    }
    return result;
}

void Matrix::_checkCompatibility(const Matrix &right) const {
    if (this->columns != right.columns) {
        if (this->rows != right.rows) {
            throw std::invalid_argument("Несовместимые размеры матриц");
        }
    }
}

Matrix Matrix::operator+(const Matrix &right) const {
    _checkCompatibility(right);
    Matrix result(*this);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] += right.data[i];
    }
    return result;

}

Matrix Matrix::operator-(const Matrix &right) const {
    _checkCompatibility(right);
    Matrix result(*this);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] -= right.data[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &right) const {
    if (this->columns != right.rows) {
        throw std::invalid_argument("Несовместимые размеры матриц");
    }
    Matrix result(this->rows, right.columns);
    auto *thatColumn = new double[right.rows];
    for (int j = 0; j < this->rows; j++) {
        for (int k = 0; k < right.rows; k++) {
            thatColumn[k] = right.at(k, j);
        }

        for (int i = 0; i < this->rows; i++) {
            double *thisRow = &(this->data[i * this->columns]);
            double sum = 0;
            for (int k = 0; k < this->columns; k++) {
                sum += thisRow[k] * thatColumn[k];
            }
            result.at(i, j) = sum;
        }
    }
    delete[] thatColumn;
    return result;
}

Matrix Matrix::operator*(const double &right) const {
    Matrix result(*this);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] *= right;
    }
    return result;
}

Matrix Matrix::operator/(const double &right) const {
    Matrix result(*this);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] /= right;
    }
    return result;
}

Matrix::MRowConst Matrix::operator[](const int &index) const {
    return Matrix::MRowConst(*this, index);
}

Matrix::MRow Matrix::operator[](const int &index) {
    return Matrix::MRow(*this, index);
}


Matrix Matrix::operator~() const {
    Matrix result(this->columns, this->rows);
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.columns; ++j) {
            result.at(i, j) = this->at(j, i);
        }
    }
    return result;
}

double &Matrix::at(int rows, int columns) {
    return this->data[rows * this->columns + columns];
}

const double &Matrix::at(int rows, int columns) const {
    return this->data[rows * this->columns + columns];
}

/*

double Matrix::_minor(int dimension, int originR, int originC)
const {
    if (dimension == 2) {
        return this->at(originR, originC) * this->at(originR + 1, originC + 1) -
               this->at(originR + 1, originC) * this->at(originR, originC + 1);
    }
    dimension--;
    double result = 0;
    for (int i = 0; i < dimension+1; ++i) {
        result += (i % 2?1:-1) * this->at(0,i) * _minor(dimension, originR)
    }
}
*/



double Matrix::determinant() const {
    if (rows != columns) {
        throw std::invalid_argument("Матрица не квадратная.");
    }
    double result = 1;

    /*if (rows < 10) {

    } else {*/
    auto lu = this->LUDecompose();
    for (int i = 0; i < lu.columns; ++i) {
        result *= lu.at(i, i);
    }

    return result;
}

Matrix Matrix::getZero(int rows, int columns) {
    Matrix result(rows, columns);
    for (int i = 0; i < rows * columns; ++i) {
        result.data[i] = 0;
    }
    return result;
}

Matrix Matrix::getIdentity(int dimension) {
    Matrix result(dimension, dimension);
    for (int i = 0; i < dimension * dimension; ++i) {
        if (i % (dimension + 1) == 0) {
            result.data[i] = 1;
        } else {
            result.data[i] = 0;
        }
    }
    return result;
}

Matrix Matrix::LUDecompose() const {
    if (rows != columns) {
        throw std::invalid_argument("Матрица не квадратная.");
    }
    auto dimension = this->rows;
    Matrix lu(dimension, dimension);
    double sum = 0;
    for (int i = 0; i < dimension; ++i) {
        for (int j = i; j < dimension; j++) {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(i, k) * lu.at(k, j);
            lu.at(i, j) = this->at(i, j) - sum;
        }
        for (int j = i + 1; j < dimension; j++) {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(j, k) * lu.at(k, i);
            lu.at(j, i) = (1 / lu.at(i, i)) * (this->at(j, i) - sum);
        }
    }
    return lu;
}

std::string Matrix::toString(int precision) const {
    std::ostringstream result;
    if (precision != -1) {
        result.setf(std::ios_base::fixed);
        result.precision(precision);
    }
    result << "| ";
    for (int i = 0; i < rows * columns; ++i) {
        if (i % this->columns == 0 && i != 0) {
            result << "\n| ";
        }
        result << data[i] << " | ";
    }
    return result.str();
}



