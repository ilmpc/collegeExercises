
#ifndef TREE_VARIABLE_H
#define TREE_VARIABLE_H

#include "expression.h"


class Variable : public Expression{
private:
    const std::string name;
public:
    explicit Variable(std::string name);

    std::unique_ptr<Expression> derivate(const Variable &x) override;

    Variable(const char &name);

    double eval(const std::map<std::string, double> *args = nullptr) const override;

    std::string toString() const override;
};


#endif //TREE_VARIABLE_H
