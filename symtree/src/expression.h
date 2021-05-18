#ifndef TREE_EXPRESSION_H
#define TREE_EXPRESSION_H

#include <string>
#include <map>
#include <memory>

class Variable;

class Expression {
public:
    virtual ~Expression() {};

    //вычисляет значение выражения
    virtual double eval(const std::map<std::string,double> *args = nullptr) const = 0;

    [[nodiscard]] virtual std::string toString() const = 0;

    virtual std::unique_ptr<Expression> derivate(const Variable &x) = 0;
};

#endif //TREE_EXPRESSION_H
