
#ifndef TREE_BINARYEXPRESSION_H
#define TREE_BINARYEXPRESSION_H

#include <functional>
#include "expression.h"
#include "variable.h"

class binaryExpression : public Expression {
private:
    const Expression &left;
    const Expression &right;
    const std::string operationSymbol;
    const std::function<double(double, double)> operation;

    static std::function<double(double, double)> getOperation(const char sym) {
        switch (sym) {
            case '+':
                return [](double a, double b) { return a + b; };
            case '-':
                return [](double a, double b) { return a - b; };
            case '*':
                return [](double a, double b) { return a * b; };
            case '/':
                return [](double a, double b) { return a / b; };
            default:
                throw std::invalid_argument("No such operation in default pull");
        }
    };

public:
    binaryExpression(const Expression &left, const Expression &right, std::string operationSymbol,
                     const std::function<double(double, double)> &operation) : left(left), right(right),
                                                                               operation(
                                                                                       operation),
                                                                               operationSymbol(
                                                                                       operationSymbol) {}

    binaryExpression(const Expression &left, const Expression &right, char operationSymbol,
                     const std::function<double(double, double)> &operation) : binaryExpression(
            left, right,std::string(1,operationSymbol), operation){}

    binaryExpression(const Expression &left, const Expression &right,
                     char operation) : left(left), right(right), operationSymbol(std::string(1, operation)),
                                       operation(getOperation(operation)) {}

    double eval(const std::map<std::string, double> *args = nullptr) const override {
        return operation(left.eval(args), right.eval(args));
    }

    [[nodiscard]] std::string toString() const override {
        return left.toString() + " " + operationSymbol + " " + right.toString();
    }

    std::unique_ptr<Expression> derivate(const Variable &x) override {
        return std::unique_ptr<Expression>();
    }
};

#endif //TREE_BINARYEXPRESSION_H
